/***************************************************************************
                      tmMpegCodeID.h  -  description
                      -----------------------------
    begin                : 04\07\2005
    copyright            : (C) 2004 by stone
    email                : stone_0815@sina.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   本文件头定义了解，压器所用的结构和参数值，在引用解压库时必须包含本头  *
 *   文件																   *
 *                                                                         *
 ***************************************************************************/


#ifndef __TMMPEGCODEID_H__
#define __TMMPEGCODEID_H__

//Mpeg CodecID
typedef enum
{
    MPEG_CODEC_ID_NONE				= 0x00000000, 
    MPEG_CODEC_ID_MPEG1VIDEO,
    MPEG_CODEC_ID_MPEG2VIDEO, /* prefered ID for MPEG Video 1 or 2 decoding */
    MPEG_CODEC_ID_MPEG2VIDEO_XVMC,
    MPEG_CODEC_ID_H261,
    MPEG_CODEC_ID_H263,
    MPEG_CODEC_ID_RV10,
    MPEG_CODEC_ID_RV20,
    MPEG_CODEC_ID_MP2,
    MPEG_CODEC_ID_MP3, /* prefered ID for MPEG Audio layer 1, 2 or3 decoding */
    MPEG_CODEC_ID_VORBIS,
    MPEG_CODEC_ID_AC3,
    MPEG_CODEC_ID_MJPEG,
    MPEG_CODEC_ID_MJPEGB,
    MPEG_CODEC_ID_LJPEG,
    MPEG_CODEC_ID_SP5X,
    MPEG_CODEC_ID_MPEG4,
    MPEG_CODEC_ID_RAWVIDEO,
    MPEG_CODEC_ID_MSMPEG4V1,
    MPEG_CODEC_ID_MSMPEG4V2,
    MPEG_CODEC_ID_MSMPEG4V3,
    MPEG_CODEC_ID_WMV1,
    MPEG_CODEC_ID_WMV2,
    MPEG_CODEC_ID_H263P,
    MPEG_CODEC_ID_H263I,
    MPEG_CODEC_ID_FLV1,
    MPEG_CODEC_ID_SVQ1,
    MPEG_CODEC_ID_SVQ3,
    MPEG_CODEC_ID_DVVIDEO,
    MPEG_CODEC_ID_DVAUDIO,
    MPEG_CODEC_ID_WMAV1,
    MPEG_CODEC_ID_WMAV2,
    MPEG_CODEC_ID_MACE3,
    MPEG_CODEC_ID_MACE6,
    MPEG_CODEC_ID_HUFFYUV,
    MPEG_CODEC_ID_CYUV,
    MPEG_CODEC_ID_H264,
    MPEG_CODEC_ID_INDEO3,
    MPEG_CODEC_ID_VP3,
    MPEG_CODEC_ID_THEORA,
    MPEG_CODEC_ID_AAC,
    MPEG_CODEC_ID_MPEG4AAC,
    MPEG_CODEC_ID_ASV1,
    MPEG_CODEC_ID_ASV2,
    MPEG_CODEC_ID_FFV1,
    MPEG_CODEC_ID_4XM,
    MPEG_CODEC_ID_VCR1,
    MPEG_CODEC_ID_CLJR,
    MPEG_CODEC_ID_MDEC,
    MPEG_CODEC_ID_ROQ,
    MPEG_CODEC_ID_INTERPLAY_VIDEO,
    MPEG_CODEC_ID_XAN_WC3,
    MPEG_CODEC_ID_XAN_WC4,
    MPEG_CODEC_ID_RPZA,
    MPEG_CODEC_ID_CINEPAK,
    MPEG_CODEC_ID_WS_VQA,
    MPEG_CODEC_ID_MSRLE,
    MPEG_CODEC_ID_MSVIDEO1,
    MPEG_CODEC_ID_IDCIN,
    MPEG_CODEC_ID_8BPS,
    MPEG_CODEC_ID_SMC,
    MPEG_CODEC_ID_FLIC,
    MPEG_CODEC_ID_TRUEMOTION1,
    MPEG_CODEC_ID_VMDVIDEO,
    MPEG_CODEC_ID_VMDAUDIO,
    MPEG_CODEC_ID_MSZH,
    MPEG_CODEC_ID_ZLIB,
    MPEG_CODEC_ID_QTRLE,

    /* various pcm "codecs" */
    MPEG_CODEC_ID_PCM_S16LE,
    MPEG_CODEC_ID_PCM_S16BE,
    MPEG_CODEC_ID_PCM_U16LE,
    MPEG_CODEC_ID_PCM_U16BE,
    MPEG_CODEC_ID_PCM_S8,
    MPEG_CODEC_ID_PCM_U8,
    MPEG_CODEC_ID_PCM_MULAW,
    MPEG_CODEC_ID_PCM_ALAW,

    /* various adpcm codecs */
    MPEG_CODEC_ID_ADPCM_IMA_QT,
    MPEG_CODEC_ID_ADPCM_IMA_WAV,
    MPEG_CODEC_ID_ADPCM_IMA_DK3,
    MPEG_CODEC_ID_ADPCM_IMA_DK4,
    MPEG_CODEC_ID_ADPCM_IMA_WS,
    MPEG_CODEC_ID_ADPCM_IMA_SMJPEG,
    MPEG_CODEC_ID_ADPCM_MS,
    MPEG_CODEC_ID_ADPCM_4XM,
    MPEG_CODEC_ID_ADPCM_XA,
    MPEG_CODEC_ID_ADPCM_ADX,
    MPEG_CODEC_ID_ADPCM_EA,
    MPEG_CODEC_ID_ADPCM_G726,

	/* AMR */
    MPEG_CODEC_ID_AMR_NB,
    MPEG_CODEC_ID_AMR_WB,

    /* RealAudio codecs*/
    MPEG_CODEC_ID_RA_144,
    MPEG_CODEC_ID_RA_288,

    /* various DPCM codecs */
    MPEG_CODEC_ID_ROQ_DPCM,
    MPEG_CODEC_ID_INTERPLAY_DPCM,
    MPEG_CODEC_ID_XAN_DPCM,
    
    MPEG_CODEC_ID_FLAC,
    
    MPEG_CODEC_ID_MPEG2TS, /* _FAKE_ codec to indicate a raw MPEG2 transport
                         stream (only used by libavformat) */
    MPEG_CODEC_ID_DTS,
	
	MPEG_CODEC_ID_BKMPEG4,
	MPEG_CODEC_ID_MP1,
	MPEG_CODEC_ID_MP123,
	MPEG_CODEC_ID_LIBMPEG2,
	MPEG_CODEC_ID_MPEG2VIRTUALDUB,
	MPEG_CODEC_ID_A52,				//ac3decoder
	
	MPEG_CODEC_ID_G721,
	MPEG_CODEC_ID_G722,
	MPEG_CODEC_ID_G723_24,
	MPEG_CODEC_ID_G723_40,
	MPEG_CODEC_ID_G726,
	MPEG_CODEC_ID_G729,
	MPEG_CODEC_ID_MASK				= 0x00000FFF,
}MPEG_CODEC_ID;

#endif	//__TMMPEGCODEID_H__
