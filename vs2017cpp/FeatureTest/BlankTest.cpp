#include <atomic>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <chrono>
#include <iostream>
#include <thread>
 

extern "C" {
    char* init(const char* config_path);
    char* process(char* workers, const char* value_str, size_t len);
    void release(char* mem);
}

std::string hashTestData;
char* init(const char* config_path) { return nullptr; }
char* process(char* workers, const char* value_str, size_t len) { return hashTestData.data(); };
void release(char* mem) {};

extern "C" {
    int LoadModel(const char* fnHash, const char* fnEmbed);
    int Feature2Embedding(char* workers, char* feaConf, size_t feaConfByte,
        const char* ucFea, size_t ucFeaByte,
        const char** ppItemFeas, size_t* pItemFeaBytes, size_t itemCount,
        float** ppEmbeds, size_t embedSize);
}
 
using namespace std;
 
#pragma pack(1)
struct HashInfo {
    uint64_t id;
    uint8_t dim;
};
#pragma pack() 

const size_t dataLenHash = sizeof(HashInfo); 
const size_t dataLenEmbed = sizeof(float);

// 注意字段顺序
struct EmbedInfo {
    uint64_t length : 8;
    uint64_t offset : 56;
};

struct EmbedMap {
    ~EmbedMap() { delete pEmbed; }

    unordered_map<uint64_t, EmbedInfo> embedMap;
    float* pEmbed;
};

shared_ptr<EmbedMap> g_spEmbedMap;
 
 
auto start = chrono::steady_clock::now();
void tsInit(){
    start = chrono::steady_clock::now();
}
void tsCost(const char* step){
    auto end = chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << step << " elapsed time: " << elapsed_seconds.count() << "s\n";
}
 
/*
测试数据18M，10dim定长. 20次测试
1. vector<float>直接赋值: 加载10秒。析构6s。共计~16s。 4.3G
2. emplace: 加载9.5s,析构6s。共计~16s。

3. 使用指针，数据另外存放，加载7.5s，析构3.5s，共计~11s。内存降低明显（4g-2g)。
union EmbedInfo {
    uint64_t length : 8;
    uint64_t offset : 56;
};
*/ 

int LoadModel(const char* fnHash, const char* fnEmbed) {
    tsInit();
    if (fnHash == nullptr || fnEmbed == nullptr) {
        printf("invalid parameter\n");
        return -3;
    }
    if (!filesystem::exists(fnHash) || !filesystem::exists(fnEmbed)) {
        printf("file [%s] or [%s] not exists.\n", fnHash, fnEmbed);
        return -4;
    }
    auto nHashByte = filesystem::file_size(fnHash);
    auto nEmbedByte = filesystem::file_size(fnEmbed);
    ifstream fHash(fnHash, ios::binary | ios::in);
    if (!fHash.is_open()) {
        printf("open file %s error\n", fnHash);
        return -1;
    }
    ifstream fEmbed(fnEmbed, ios::binary | ios::in);
    if (!fHash.is_open()) {
        printf("open file %s error\n", fnEmbed);
        return -2;
    }
    auto nHash = nHashByte / dataLenHash;
    auto nEmbed = nEmbedByte / dataLenEmbed;
    // check size
    if (nHash * dataLenHash != nHashByte || nEmbed * dataLenEmbed!= nEmbedByte) {
        printf("%zd * %zd != %zd; %zd * %zd != %zd", nHash, dataLenHash, nHashByte,
            nEmbed, dataLenEmbed, nEmbedByte);
        printf("invalid file size: hash %zd embed %zd\n", nHashByte, nEmbedByte);
        return -5;
    }
    tsCost("size");

    auto pHash = new HashInfo[nHash];
    auto pEmbed = new float[nEmbed];
    unique_ptr<HashInfo> upHash(pHash);
    tsCost("new data");

    if (!fHash.read((char*)pHash, nHashByte) || fHash.gcount()!=nHashByte){
        printf("read %s %zd expect %zd\n", fnHash, fHash.gcount(), nHashByte);
        return -6;
    }
    tsCost("read hash");

    if (!fEmbed.read((char*)pEmbed, nEmbedByte) || fEmbed.gcount()!=nEmbedByte){
        printf("read %s %zd expect %zd\n", fnEmbed, fEmbed.gcount(), nEmbedByte);
        return -6;
    }
    tsCost("read embed");

    auto pMap = new EmbedMap();
    pMap->embedMap.reserve(nHash);
    pMap->pEmbed = pEmbed;
    shared_ptr<EmbedMap> spMap(pMap);
    auto& m = pMap->embedMap;
    
    uint64_t pos = 0;
    for (int i = 0; i < nHash; i++) {
        EmbedInfo info;
        info.offset = pos;
        info.length = pHash[i].dim;
        m[pHash[i].id] = info;
        pos += pHash[i].dim;
        if (i < 5) {
            printf("embed info: %lld %lld %lld+%lld:", pHash[i].id,pos, info.offset, info.length);
            for (uint64_t i = 0; i < info.length; i++) {
                printf(" %f",  *(pEmbed + info.offset + i));
            }
            puts("");
        }
    }
    tsCost("parse");
    printf("load data total: %zd\n", nHash);
    atomic_store(&g_spEmbedMap, spMap);
    tsCost("store"); 
    return 0;
}


struct FeaConf {
    int slot;
    int start;
    int dim;
};

void printFeaConf(unordered_map<string, FeaConf>& feaConfMap) {
    printf("feaConf %zd: ", feaConfMap.size());
    for (auto it = feaConfMap.begin(); it != feaConfMap.end(); it++) {
        printf("%s@%d,%d,%d||", it->first.c_str(), it->second.slot, it->second.start, it->second.dim);
    }
    puts("");
}

void printFloat(float* p, size_t len) {
    printf("float %zd: ", len);
    for (size_t i = 0; i < len; i++) {
        printf("%f ", p[i]);
    }
    puts("");
}

void parseFeaConf(char* confStr, size_t confByte, unordered_map<string, FeaConf>& feaConfMap) {
    // key@slot,start,dim||
    char* p = confStr;
    char* pLast = p;
    string key; 
    int idx=0, slot=0, start=0, dim=0;
    while (*p != 0) {
        switch (*p)
        {
        case '|':
            if (p[1] != '|') {
                p++;
                break;
            }
            *p = 0;
            {
                dim = atoi(pLast);
                if (dim > 0) {
                    FeaConf conf{ slot, start, dim };
                    feaConfMap[key] = conf;
                }
                idx = 0;
            }
            p++; *p = 0; p++;
            pLast = p;
            break;
        case '@':
            *p = 0;
            key = pLast;
            idx = 0;
            p++;
            pLast = p;
            break;
        case ',':
            *p = 0;
            {
                auto n = atoi(pLast);
                switch (idx) {
                case 0:
                    slot = n;
                    break;
                case 1:
                    start = n;
                    break; 
                default:
                    cout << "invalid feature conf: " << string(confStr, confByte) << endl;
                    break;
                }
                idx++;
            }
            p++;
            pLast = p;
            break;
        default:
            p++;
            break;
        }
    }
    // process last
    dim = atoi(pLast);
    if (dim > 0) {
        FeaConf conf{ slot, start, dim };
        feaConfMap[key] = conf;
    } 
}

void calcEmbed(char* pLast,  string& key,float* const pOutEmbed, unordered_map<string, FeaConf>& feaConfMap, EmbedMap* pEmbedMap) {
    auto hash = strtoull(pLast, nullptr, 0);
    auto& conf = feaConfMap[key];
    if (conf.dim > 0) {
        auto& info = pEmbedMap->embedMap[hash];
        auto pHashEmbed = pEmbedMap->pEmbed + info.offset;
        for (uint64_t i = 0; i < info.length; i++) {
            pOutEmbed[conf.start + i] += pHashEmbed[i];
        }
        printf("key %s hash %zd: embed",key.data(), hash);
        printFloat(pOutEmbed + conf.start, conf.dim);
    }
    else {
        printf("invalid conf key %s\n", key.data());
    }
}

void hash2Embed(char* hashStr, float* const pOutEmbed, unordered_map<string, FeaConf>& feaConfMap, EmbedMap* pEmbedMap) {
    // key@hash,hash,...||
    char* p = hashStr;
    char* pLast = p;
    string key; 
    while (*p != 0) {
        switch (*p)
        {
        case '|':
            if (p[1] != '|') {
                p++;
                break;
            }
            *p = 0;
            {
                calcEmbed(pLast, key, pOutEmbed, feaConfMap, pEmbedMap);
            }
            p++; *p = 0; p++;
            pLast = p;
            break;
        case '@':
            *p = 0;
            key = pLast; 
            p++;
            pLast = p;
            break;
        case ',':
            *p = 0;
            {
                calcEmbed(pLast, key, pOutEmbed, feaConfMap, pEmbedMap);
            }
            p++;
            pLast = p;
            break;
        default:
            p++;
            break;
        }  
    }
    calcEmbed(pLast, key, pOutEmbed, feaConfMap, pEmbedMap);
}

int Feature2Embedding(char* workers, char* feaConf, size_t feaConfByte,
    const char* ucFea, size_t ucFeaByte,
    const char** ppItemFeas, size_t* pItemFeaBytes, size_t itemCount,
    float** ppEmbeds, size_t embedSize){
    // len(itemFeas)==len(ppEmbeds)==itemCount
    // feaConf + feaConfByte -> feaConfMap
    unordered_map<string, FeaConf> feaConfMap;
    parseFeaConf(feaConf, feaConfByte, feaConfMap);
    printFeaConf(feaConfMap);

    auto spEmbedMap = atomic_load(&g_spEmbedMap);
    auto pEmbedMap = spEmbedMap.get();
    if (pEmbedMap->embedMap.size() == 0 || pEmbedMap->pEmbed == nullptr) {
        return -1;
    }

    // ucFea + ucFeaByte 
    auto pucEmbed = new float[embedSize];
    memset(pucEmbed, 0, embedSize * sizeof(float));
    unique_ptr<float> upucEmbed(pucEmbed);
    auto ucHashStr = process(workers, ucFea, ucFeaByte);
    hash2Embed(ucHashStr, pucEmbed, feaConfMap, pEmbedMap);
    release(ucHashStr);
    printFloat(pucEmbed, embedSize);
    return 0;
    for (size_t i = 0; i < itemCount; i++) {
        memcpy(ppEmbeds[i], pucEmbed, embedSize * sizeof(float));
    }
    // items
    for (size_t i = 0; i < itemCount; i++) {
        auto itemHashStr = process(workers, ppItemFeas[i], pItemFeaBytes[i]);
        hash2Embed(itemHashStr, ppEmbeds[i], feaConfMap, pEmbedMap);
        release(itemHashStr);
    }
    
    return 0;
}

void loadTest(){
    auto start = chrono::steady_clock::now();
    auto n = LoadModel("mtctr_v1a.idx", "mtctr_v1a.embed");
    printf("return %d\n", n);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    auto sp = atomic_load(&g_spEmbedMap);
    //auto spEmbed = atomic_load(&g_spEmbed);
    auto pEmbed = sp->pEmbed;
    vector<uint64_t> v{ 260604297723074114,158926864742793154,173875697360607746 };
    for (auto pid = v.begin(); pid != v.end(); pid++) {
        printf("embed %llu:", *pid);
        auto& embed = sp->embedMap[*pid]; 
        for (int i = 0; i < embed.length; i++) { 
            printf(" %f", pEmbed[embed.offset+i]);
        } 
        puts("");
    } 
}

void testParser(void) {

    //unordered_map<string, FeaConf> feaConf;
    //parseFeaConf(sConf.data(), sConf.length(), feaConf);
    //printFeaConf(feaConf);

    loadTest();
    string ucFea = "u_st_2_device_os@-1||u_bh_5_n_seq_listclick_cat2@14944,15088,10113,16785,11482,15480,10103,15896,10637,15480,15896,22473,10120,15896,10113,15407,15332,15312,15088,16189,15332,15332,10113,17119,10120,15480,10129,11043,11482,15924,11928,15312,15896,21834,15924,10120,11928,10130,15896,10130,22473,15195,15332,13533,22473,22473,10153,12118||u_bh_6_n_listpay_10@-1||u_st_2_city_id@0||u_st_6_favo_cat_2_10@15332,16230,15896,10120,15480,15924,15312,11928,10130,10113||u_bh_5_n_listclick_20@40157351,31933026,4016937,22689247,2365011,19456034,418313,40170240,40679852,1876809,26614490,40140126,16411124,1357226,40636304,40580251,12968551,12084085,31933026,40424926||u_bh_5_n_listfavorite@40157351,4016937,22689247,2365011,418313,40679852,1876809,26614490,40140126,16411124,40636304,40580251,12968551,12084085,31933026,40424926,7710778,139700,1072768,35958764,38312698,19456034,40533746,12027901,35802054,39886145,19941082,24395637,36913803,36338427,38816939,10716459,40356343,1357226,1866545,127262,40400808,116528,1917962,1672170,40421409||c_2_version_scene@2.6.8|10||u_st_2_sex@2||u_st_2_province_id@0||u_st_2_off_prf_src_city_off@-1||u_bh_5_n_seq_listpay_mall_id@-1||u_st_2_off_prf_src_province_off@山西||u_st_2_off_prf_is_member_off@-1||c_2_version_position@2.6.8|nav.1.精选.1||u_bh_5_n_listpay@-1||u_bh_5_n_seq_listpay_cat2@-1||u_st_3_off_prf_orders_count_coins_off@-1||u_bh_5_n_listclick@40157351,31933026,4016937,22689247,2365011,19456034,418313,40170240,40679852,1876809,26614490,40140126,16411124,1357226,40636304,40580251,12968551,12084085,31933026,40424926,7710778,139700,1072768,35958764,38312698,19456034,40533746,12027901,35802054,39886145,19941082,24395637,1357226,36913803,36338427,38816939,10716459,40356343,1357226,1866545,127262,40400808,116528,1917962,1672170,1672170,40421409,40334516||u_bh_5_n_seq_listclick_mall_id@105158,134573,117388,130210,114428,130711,103916,110134,120019,103836,103713,107648,103252,102862,135041,101903,113686,123474,134573,135318,105089,103284,104827,109395,103874,130711,106506,126948,136462,103712,131397,132978,102862,134447,102200,103252,119839,129896,102862,101674,102385,117348,102548,101820,102385,102385,102455,101071";
    hashTestData = "u_st_2_off_prf_src_city_off@118795289206520094||u_bh_6_n_listpay_10@122442599700481609||c_2_version_position@46555936683421268||u_st_2_sex@79062501243293965||u_bh_5_n_seq_listpay_mall_id@210357862714473155||u_st_2_off_prf_src_province_off@151062721052127069||u_bh_5_n_seq_listpay_cat2@151609508597136212||u_st_2_city_id@46257627028003804||u_st_3_off_prf_orders_count_coins_off@109937187363673703||u_bh_5_n_seq_listclick_cat2@193395728114488319,220131855993435027,200182362236798127,212569083487218952,153964268801135833,123463884677286337,123463884677286337,253852479431575875,159265151190133402,17243654802365228,270171410513982004,200182362236798127,221986263303726257,60734412951980294,185330276656109257,199555371111923054,281898876839761958,253852479431575875,159265151190133402,199555371111923054,253852479431575875,67399655798418601,137255200005932742,253852479431575875,221986263303726257,104833020103483345,190826376082664704,231159043808186848,200182362236798127,251745873113347995,190826376082664704,190826376082664704,221986263303726257,132520154825740585,137255200005932742,199555371111923054,243868450892236805,41244191640727014,185330276656109257,69432244613679284,128369147875026118,231159043808186848,253852479431575875,226451274695375891,69432244613679284,137255200005932742,128369147875026118,152759536771767924,253852479431575875,152759536771767924,67399655798418601,94702419447291899,190826376082664704,58347318808646329,67399655798418601,67399655798418601,64250502146506519,121486731072856230||u_bh_5_n_seq_listclick_mall_id@5466152184861223,262133112497187906,249305238659806661,104515475647735198,104515475647735198,14179737183473622,14179737183473622,250164199774510115,152035299983491389,120435172096732855,78994124772867377,249305238659806661,27462552805538126,173648145038632277,225937790087945343,73023683519651050,243087286445733894,39445424120754852,152035299983491389,139944015693534771,270415744892524676,148346341690688945,185603491394034721,250164199774510115,43255050461068318,112022352199512150,46454858414730959,288045502253399266,249305238659806661,66336424447992933,126591108635087447,169217778876590307,267227679630209824,143792609811639817,117509776182695364,73023683519651050,181374106662815088,116329242115863825,47990272363819379,71731953651871566,66113490328116554,165620021211927854,250164199774510115,66851128583977382,97503825239893577,185603491394034721,38003148975178642,254452755139762129,250164199774510115,73256739660808257,132622071973459106,181799683478299197,184258597453904078,222110023457882439,132622071973459106,132622071973459106,93602339739254280,110113688508012688||u_bh_5_n_listclick_20@5208777079029462,27192623611425936,187755862847238263,219449139371930640,21913620155629987,231678087191393492,231678087191393492,190253618720598465,202877935163916143,20296415528383948,286512311323843847,187755862847238263,151894816432639809,210112195895543891,241926306391663437,235998545503406452,179786210854940123,99907991367671359,202877935163916143,109181865555787971||u_bh_5_n_listfavorite@140652392377039450,241644955498269193,183899012221661053,47196663787200988,19563987478628568,78583476089673461,77229946750228386,249453188406854738,231935496944497669,100267553691945806,132236875141634445,245205512966042739,107960522324331958,7050902531670033,86412266664848083,228178622341308499,62425242569796421,276756364267559952,283191908980581971,5705339925252030,211563322438397074,250343129496243858,3656833195688228,96354392971690063,88245009442085381,45449738549390577,248005091316007264,129294830813238871,17403810732568498,176706563134862573,127135592236746191,260369975758572294,15551514731149396,229581098232457732,248612693183253238,114358570252768703,20195411063612543,184917970335932096,252455833285968414,45369859672678146,215485596074876768,275408900075793809,79324503408382018,80721279934148117,26162293357255962,70074418859739473,45011174467288415||u_st_2_province_id@71688781301437041||u_bh_5_n_listpay@248635331116441474||u_st_2_device_os@181323986436721460||u_bh_5_n_listclick@144035643630423780,270545303299938171,98921565244526306,75209287914712985,221069015705710112,241987286907566767,241987286907566767,283413466454535940,38245363938236544,113807375209714317,153765323349470213,98921565244526306,262710996663638518,16424845369522462,285396724262726332,175033614329534967,37023343684090144,28153356797519303,38245363938236544,258528169976544270,28219426168708060,198344580402797505,152442042145551594,283413466454535940,8452129709515264,229646263307094714,92234533191021918,146876961482626708,98921565244526306,208787788803195722,44910884904004140,222366741286984385,84041776678625347,82702612429244786,254486468725172433,175033614329534967,195985621572759918,243557799626833665,228091835953739425,6729478541308305,158638714094140585,134588405854802245,283413466454535940,106396981290667299,245112789832083366,150724564597080635,142568081209858744,53416493402787383,283413466454535940,225180862621084019,118671697671481953,84583957717603244,24153452383138946,33782821437057453,158705663808541330,158705663808541330,70909056901835975,285616647300455148||c_2_version_scene@239820612103555453||u_st_6_favo_cat_2_10@9986053795315550,79481267400733497,159139594048756553,234377138508395687,48029159566311462,220751358057322301,193680139331849368,39680340439667852,37487119045546262,155694586804248916||u_st_2_off_prf_is_member_off@91424602149143916";
    string sConf = "c_2_version_position@0,0,10||c_2_version_scene@1,10,10||i_dy_3_default_totalclick@2,20,10||i_dy_3_default_totalpay@3,30,10||i_st_2_cat_id_1@4,40,10||i_st_2_cat_id_2@5,50,10||i_st_2_cat_id_3@6,60,10||i_st_2_iid@7,70,10||i_st_2_is_refundable@8,80,10||i_st_2_mall_id@9,90,10||i_st_3_min_normal_price@10,100,10||i_st_5_item_title_words@11,110,10||u_bh_5_n_listclick@12,120,10||u_bh_5_n_listclick_20@13,130,10||u_bh_5_n_listfavorite@14,140,10||u_bh_5_n_listpay@15,150,10||u_bh_5_n_seq_listclick_cat2@16,160,10||u_bh_5_n_seq_listclick_mall_id@17,170,10||u_bh_5_n_seq_listpay_cat2@18,180,10||u_bh_5_n_seq_listpay_mall_id@19,190,10||u_bh_6_n_listpay_10@20,200,10||u_st_2_city_id@21,210,10||u_st_2_device_os@22,220,10||u_st_2_off_prf_is_member_off@23,230,10||u_st_2_off_prf_src_city_off@24,240,10||u_st_2_off_prf_src_province_off@25,250,10||u_st_2_province_id@26,260,10||u_st_2_sex@27,270,10||u_st_3_off_prf_orders_count_coins_off@28,280,10||u_st_6_favo_cat_2_10@29,290,10";
    auto ret = Feature2Embedding(nullptr, sConf.data(), sConf.length(),
        ucFea.data(), ucFea.length(), 0, 0, 0, 0, 300);
    cout << "Feature2Embedding ret " << ret << endl;
}

void BlankTest() {   
    testParser();
    return;
    printf("len %zd %zd\n", dataLenHash, dataLenEmbed);
    printf("ptr len %zd\n", sizeof(void*));
    for(int i=0;i<10;i++){
        loadTest();
        cout << "sleep 3 sec" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    } 
   
    //shared_ptr< unordered_map<uint64_t, vector<float>>> spMap(nullptr);
    //atomic_store(&g_spEmbedMap, spMap);
    cout << "press enter" << endl;
	getchar();
}



