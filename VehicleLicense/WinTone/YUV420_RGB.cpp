#include "Table.h"
#include "windows.h"
//YYYYVVUU
static void YUV422ToRGB24(unsigned char *yuv422, unsigned char *rgb24, int width, int height)
{
	int R,G,B,Y,U,V;
	int x,y;
	int nWidth = width>>1; //色度信号宽度
	for (y=0;y<height;y++)
	{
		for (x=0;x<width;x++)
		{
			Y = *(yuv422 + y*width + x);
			U = *(yuv422 + width*height+(y>>1)*width + (x>>1));
			V = *(yuv422 + width*height+nWidth*height+(y>>1)*width + (x>>1));
			R = Y + 1.402*(V-128);
			G = Y - 0.34414*(U-128) - 0.71414*(V-128);
			B = Y + 1.772*(U-128);

			//防止越界
			if (R>255)R=255;
			if (R<0)R=0;
			if (G>255)G=255;
			if (G<0)G=0;
			if (B>255)B=255;
			if (B<0)B=0;

			*(rgb24 + ((height-y-1)*width + x)*3) = B;
			*(rgb24 + ((height-y-1)*width + x)*3 + 1) = G;
			*(rgb24 + ((height-y-1)*width + x)*3 + 2) = R;  
		}
	}
}

//YYYYYYYYUUVV
void YUV420ToRGB24_1(unsigned char *yuv420, unsigned char *rgb24, int width, int height) 
{
	int R,G,B,Y,U,V;
	int x,y;
	int nWidth = width>>1; //色度信号宽度
	int nHeight= height>>1;
	unsigned char *pRGB;
	for (y=0;y<height;y++)
	{
		pRGB = rgb24 + (height-y-1)*width*3;
		for (x=0;x<width;x++)
		{
			Y = *(yuv420 + y*width + x);
			U = *(yuv420 +width*height+((y>>2)*width) + (x>>2));
			V = *(yuv420 +width*height+nWidth*nHeight+((y>>2)*width) + (x>>2));

			//查表法
			R = Table_MaxMin[int(Y +  Table_17790[V]+128)];
			G = Table_MaxMin[int(Y -  Table_3454[V]-Table_7168[U]+128)]; 
			B = Table_MaxMin[int(Y+Table_14075[U]+128)];

			//防止越界
			if (R>255)R=255;
			if (R<0)R=0;
			if (G>255)G=255;
			if (G<0)G=0;
			if (B>255)B=255;
			if (B<0)B=0;

			*pRGB++ = B;
			*pRGB++ = G;
			*pRGB++ = R;	
		}
	}	

    for ( int nIndex = 0; nIndex < width * height * 3 - 2; nIndex += 2 ) {
        BYTE R = rgb24[ nIndex ];
        BYTE B = rgb24[ nIndex + 2 ];

        rgb24[ nIndex ] = B;
        rgb24[ nIndex + 2 ] = R;
    }
}

//YYYYYYYYUVUV
void YUV420ToRGB24_2(unsigned char *yuv420, unsigned char *rgb24, int width, int height) 
{
	int R,G,B,Y,U,V;
	int x,y;
	int nWidth = width>>1; //色度信号宽度
	int nHeight= height>>1;
	unsigned char *pRGB;
	for (y=0;y<height;y++)
	{
		pRGB = rgb24 + (height-y-1)*width*3;
		for (x=0;x<width;x++)
		{
			Y = *(yuv420 + y*width + x);
			U = *(yuv420 +width*height+((y>>2)*width) + (x>>2));
			V = *(yuv420 +width*height+((y>>2)*width) + (x>>2)+1);

			//查表法
			R = Table_MaxMin[int(Y +  Table_17790[V]+128)];
			G = Table_MaxMin[int(Y -  Table_3454[V]-Table_7168[U]+128)]; 
			B = Table_MaxMin[int(Y+Table_14075[U]+128)];

			//防止越界
			if (R>255)R=255;
			if (R<0)R=0;
			if (G>255)G=255;
			if (G<0)G=0;
			if (B>255)B=255;
			if (B<0)B=0;

			*pRGB++ = B;
			*pRGB++ = G;
			*pRGB++ = R;	
		}
	}	
}
