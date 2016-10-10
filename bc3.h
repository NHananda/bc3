#define ROTR32_8(x) ( ( ( x << 24 ) & 0xFFFFFFFF ) | \
( ( x & 0xFFFFFFFF ) >> 8 ) )
#define ROTR32(x,t) ( ((x) >> (t)) + ((x) << (32 – t)) )
#define ROTL32(x,t) ( ((x) << (t)) + ((x) >> (32 – t)) )

#define ROTR16_1(x) ( ( ( x << 15 ) & 0xFFFF ) | \
( ( x & 0xFFFF ) >> 1 ) )
#define ROTL16_1(x) ( ( ( x >> 15 ) & 0xFFFF ) | \
( ( x & 0xFFFF ) << 1 ) )

#define XTIME(x) ( ( x << 1 ) ^ ( ( x & 0x80 ) ? 0x1B : 0x00 ) )
#define MUL(x,y) ( ( x && y ) ? pow[(log[x] + log[y]) % 255] : 0 )

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned int

#define C1 0xD62F59FB
#define C2 0xD597BEF1
#define C3 0xE4F92E2D
#define C4 0xFF6EC9AB
#define C5 0xF2DCE89B
#define C6 0x636CB246

u32 WK[5]; /*Whitening Key*/
u32 KFA[3]; /*kunci FA*/
u32 SK[12],XL, XR, YL, YR; /*Round Key*/
u32 gA,gB,gC;

#define BC3_FROUND(XL,XR,YL,YR,SK) \
{ \
YL = XR; \
YR = Tbl0[ ( u8 ) ( XR >> 24 ) ] ^ \
Tbl1[ ( u8 ) ( XR >> 16 ) ] ^ \
Tbl2[ ( u8 ) ( XR >> 8 ) ] ^ \
Tbl3[ ( u8 ) ( XR ) ] ^ SK ^ XL; \
} \

#define BC3_FAR(a,b,c,d) \
{ \
c=ROTL32((a & KFA[1]),1) ^ b; \
d=(ROTR32(c,1)|KFA[2])^a; \
}

#define BC3_FAinverse(a,b,c,d) \
{ \
d = (ROTR32(b,1)|KFA[2])^a; \
c = ROTL32((d&KFA[1]),1)^b; \
}