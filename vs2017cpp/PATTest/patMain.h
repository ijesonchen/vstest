#ifndef patMain_h__
#define patMain_h__

#include <string>

void RedirCin(const std::string& fn);
void Tick(void);
void Tock(void);

// pta: pintia.cn
void StartSelfTest(void);
inline void PtaTest(void)
{
	StartSelfTest();
}

void B1003(void);

inline void Basic(void)
{
	B1003();
}

void A1002(void);
void A1003(void);
void A1004(void);
void A1005(void);
void A1006(void);
void A1007(void);

inline void Advanced(void)
{
	A1007();
}

inline void Top(void)
{

}

inline void Main(void)
{
	Advanced();
}


#endif // patMain_h__
