package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
)

type feaConf struct {
	Group_list []struct {
		FeaName  string
		SlotSit  int
		EmbedDim int
	}
}

func xxxtest() {
	s := "{\"group_list\":[{\"FeaName\":\"c_2_version_position\",\"EmbedDim\":10},{\"FeaName\":\"c_2_version_scene\",\"SlotSit\":1,\"EmbedDim\":10},{\"FeaName\":\"i_dy_3_default_totalclick\",\"SlotSit\":2,\"EmbedDim\":10},{\"FeaName\":\"i_dy_3_default_totalpay\",\"SlotSit\":3,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_cat_id_1\",\"SlotSit\":4,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_cat_id_2\",\"SlotSit\":5,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_cat_id_3\",\"SlotSit\":6,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_iid\",\"SlotSit\":7,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_is_refundable\",\"SlotSit\":8,\"EmbedDim\":10},{\"FeaName\":\"i_st_2_mall_id\",\"SlotSit\":9,\"EmbedDim\":10},{\"FeaName\":\"i_st_3_min_normal_price\",\"SlotSit\":10,\"EmbedDim\":10},{\"FeaName\":\"i_st_5_item_title_words\",\"SlotSit\":11,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_listclick\",\"SlotSit\":12,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_listclick_20\",\"SlotSit\":13,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_listfavorite\",\"SlotSit\":14,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_listpay\",\"SlotSit\":15,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_seq_listclick_cat2\",\"SlotSit\":16,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_seq_listclick_mall_id\",\"SlotSit\":17,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_seq_listpay_cat2\",\"SlotSit\":18,\"EmbedDim\":10},{\"FeaName\":\"u_bh_5_n_seq_listpay_mall_id\",\"SlotSit\":19,\"EmbedDim\":10},{\"FeaName\":\"u_bh_6_n_listpay_10\",\"SlotSit\":20,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_city_id\",\"SlotSit\":21,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_device_os\",\"SlotSit\":22,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_off_prf_is_member_off\",\"SlotSit\":23,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_off_prf_src_city_off\",\"SlotSit\":24,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_off_prf_src_province_off\",\"SlotSit\":25,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_province_id\",\"SlotSit\":26,\"EmbedDim\":10},{\"FeaName\":\"u_st_2_sex\",\"SlotSit\":27,\"EmbedDim\":10},{\"FeaName\":\"u_st_3_off_prf_orders_count_coins_off\",\"SlotSit\":28,\"EmbedDim\":10},{\"FeaName\":\"u_st_6_favo_cat_2_10\",\"SlotSit\":29,\"EmbedDim\":10}]}"
	var fc feaConf
	err := json.Unmarshal([]byte(s), &fc)
	log.Printf("%v %+v", err, fc)

	var buf bytes.Buffer
	var start int
	for i, fea := range fc.Group_list {
		if i > 0 {
			buf.WriteString("||")
		}
		buf.WriteString(fmt.Sprintf("%s@%d,%d,%d", fea.FeaName, fea.SlotSit, start, fea.EmbedDim))
		start += fea.EmbedDim
	}
	log.Println(buf.String())
}
