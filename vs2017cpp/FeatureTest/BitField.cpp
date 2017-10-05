
struct HexChar
{
	unsigned char a : 4;
	unsigned char b : 4;
};

struct HexBit
{
	unsigned char a1 : 1;
	unsigned char a2 : 1;
	unsigned char a3 : 1;
	unsigned char a4 : 1;
	unsigned char a5 : 1;
	unsigned char a6 : 1;
	unsigned char a7 : 1;
	unsigned char a8 : 1;
};


void BitFieldTest(void)
{



	// ?
	char p = 0x5a;
	HexChar* phc = (HexChar*)&p;
	// .a = 10, .b = 5
	HexBit* phb = (HexBit*)&p;
	// .a1-a8:  01011010 
}