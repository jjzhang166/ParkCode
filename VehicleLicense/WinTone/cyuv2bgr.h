#ifndef CYUV2BGR_H
#define CYUV2BGR_H

#include <QObject>
#include <windows.h>

const unsigned char icvSaturate8u_cv[] =
{
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
    16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
    32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
    48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
    96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255
};

#define CV_FAST_CAST_8U(t)  (icvSaturate8u_cv[(t)+256])

#define   RGB4Y 1.164
#define   B4U 2.018
#define   Y2ADD 16

#define   G4U 0.391
#define   G4V 0.813
#define   U2ADD 128

#define   R4V 1.596
#define   V2ADD 128

#define   SCALEBITS 13


//for slow
#define Rs 1.403
#define Grs 0.344
#define Gbs 0.714
#define Bs 1.773
#define  Delta 128

#define   FIX(x) ((unsigned short)   ((x)   *   (1L   <<   SCALEBITS)   +   0.5))
#define ClipColorValue CV_FAST_CAST_8U


/* BGR/RGB -> YCrCb */
#define  CV_DESCALE(x,n)     (((x) + (1 << ((n)-1))) >> (n))
#define fix(x,n)      (int)((x)*(1 << (n)) + 0.5)
#define descale       CV_DESCALE

#define yuvYr_32f cscGr_32f
#define yuvYg_32f cscGg_32f
#define yuvYb_32f cscGb_32f
#define yuvCr_32f 0.713f
#define yuvCb_32f 0.564f

#define yuv_shift 14
#define yuvYr  fix(yuvYr_32f,yuv_shift)
#define yuvYg  fix(yuvYg_32f,yuv_shift)
#define yuvYb  fix(yuvYb_32f,yuv_shift)
#define yuvCr  fix(yuvCr_32f,yuv_shift)
#define yuvCb  fix(yuvCb_32f,yuv_shift)

#define yuv_descale(x)  CV_DESCALE((x), yuv_shift)
#define yuv_prescale(x) ((x) << yuv_shift)

#define  yuvRCr_32f   1.403f
#define  yuvGCr_32f   (-0.714f)
#define  yuvGCb_32f   (-0.344f)
#define  yuvBCb_32f   1.773f

#define  yuvRCr   fix(yuvRCr_32f,yuv_shift)
#define  yuvGCr   (-fix(-yuvGCr_32f,yuv_shift))
#define  yuvGCb   (-fix(-yuvGCb_32f,yuv_shift))
#define  yuvBCb   fix(yuvBCb_32f,yuv_shift)


static int   g_RGB4Y_Tab[256];
static int   g_B4U_Tab[256];
static int   g_G4U_Tab[256];
static int   g_G4V_Tab[256];
static int   g_R4V_Tab[256];

typedef unsigned char *LPBYTE;

void   InitColorSpace();

inline   void   YUV420_RGB32_4Pixel(LPBYTE   pRGB,   LPBYTE   pY,   LPBYTE   pU,   LPBYTE   pV,   UINT   Width);
inline   void   slow_YUV420_RGB32_4Pixel(LPBYTE   pRGB,   LPBYTE   pY,   LPBYTE   pU,   LPBYTE   pV,   UINT   Width);
inline   void   YUV420_RGB24_3Pixel(LPBYTE   pRGB,   LPBYTE   pY,   LPBYTE   pU,   LPBYTE   pV,   UINT   Width);


void   YUV420_RGB32(LPBYTE   pRGB,   LPBYTE   pYUV,   UINT   Width,   UINT   Height);
void   YUV420_RGB24(LPBYTE   pRGB,   LPBYTE   pYUV,   UINT   Width,   UINT   Height);

void   YUV420_RGB24_split(LPBYTE   pRGB,   LPBYTE   pY, LPBYTE pU, LPBYTE pV, UINT   Width,   UINT   Height);
void   YUV420_RGB24_splitCV(LPBYTE   pRGB,   LPBYTE   pY, LPBYTE pU, LPBYTE pV, UINT   Width,   UINT   Height);

//void   YUV422_RGB24_split_small(LPBYTE   pRGB,   LPBYTE   pY, LPBYTE pU, LPBYTE pV);

void cvtColorYUV2RGB(LPBYTE   pRGB, LPBYTE pYUV, int width,int height);
void cvtColorYUV2RGB(LPBYTE   pRGB, LPBYTE   pY, LPBYTE pU, LPBYTE pV, int width,int height);

class CYUV2BGR : public QObject
{
    Q_OBJECT
public:
    explicit CYUV2BGR(QObject *parent = 0);
    void RGB2BGR( LPBYTE pYUV420, LPBYTE pBGR, UINT nWidth, UINT nHeight );

private:
    void InitColorSpace( );
    void YUV420_RGB24_3Pixel(LPBYTE   pRGB,   LPBYTE   pY,   LPBYTE   pU,   LPBYTE   pV,   UINT   Width) ;
    
signals:
    
public slots:
    
};

#endif // CYUV2BGR_H
