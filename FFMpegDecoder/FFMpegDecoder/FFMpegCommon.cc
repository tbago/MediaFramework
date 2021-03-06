//
//  FFMpegCommon.m
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/19.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "FFMpegCommon.h"

using namespace media_base;
namespace media_decoder {

const AVRational gGloabalTimeBase = {1, AV_TIME_BASE};

media_base::ResuableCodecID FFMpegCodecIDToMeidaCodecID(enum AVCodecID ffCodecID)
{
    switch(ffCodecID)
    {
        /* video case CODEC */
        case AV_CODEC_ID_MPEG1VIDEO:               return R_CODEC_ID_MPEG1VIDEO;
        case AV_CODEC_ID_MPEG2VIDEO:               return R_CODEC_ID_MPEG2VIDEO;
        case AV_CODEC_ID_H261:                     return R_CODEC_ID_H261;
        case AV_CODEC_ID_H263:                     return R_CODEC_ID_H263;
        case AV_CODEC_ID_RV10:                     return R_CODEC_ID_RV10;
        case AV_CODEC_ID_RV20:                     return R_CODEC_ID_RV20;
        case AV_CODEC_ID_MJPEG:                    return R_CODEC_ID_MJPEG;
        case AV_CODEC_ID_MJPEGB:                   return R_CODEC_ID_MJPEGB;
        case AV_CODEC_ID_LJPEG:                    return R_CODEC_ID_LJPEG;
        case AV_CODEC_ID_SP5X:                     return R_CODEC_ID_SP5X;
        case AV_CODEC_ID_JPEGLS:                   return R_CODEC_ID_JPEGLS;
        case AV_CODEC_ID_MPEG4:                    return R_CODEC_ID_MPEG4;
        case AV_CODEC_ID_RAWVIDEO:                 return R_CODEC_ID_RAWVIDEO;
        case AV_CODEC_ID_MSMPEG4V1:                return R_CODEC_ID_MSMPEG4V1;
        case AV_CODEC_ID_MSMPEG4V2:                return R_CODEC_ID_MSMPEG4V2;
        case AV_CODEC_ID_MSMPEG4V3:                return R_CODEC_ID_MSMPEG4V3;
        case AV_CODEC_ID_WMV1:                     return R_CODEC_ID_WMV1;
        case AV_CODEC_ID_WMV2:                     return R_CODEC_ID_WMV2;
        case AV_CODEC_ID_H263P:                    return R_CODEC_ID_H263P;
        case AV_CODEC_ID_H263I:                    return R_CODEC_ID_H263I;
        case AV_CODEC_ID_FLV1:                     return R_CODEC_ID_FLV1;
        case AV_CODEC_ID_SVQ1:                     return R_CODEC_ID_SVQ1;
        case AV_CODEC_ID_SVQ3:                     return R_CODEC_ID_SVQ3;
        case AV_CODEC_ID_DVVIDEO:                  return R_CODEC_ID_DVVIDEO;
        case AV_CODEC_ID_HUFFYUV:                  return R_CODEC_ID_HUFFYUV;
        case AV_CODEC_ID_CYUV:                     return R_CODEC_ID_CYUV;
        case AV_CODEC_ID_H264:                     return R_CODEC_ID_H264;
        case AV_CODEC_ID_INDEO3:                   return R_CODEC_ID_INDEO3;
        case AV_CODEC_ID_VP3:                      return R_CODEC_ID_VP3;
        case AV_CODEC_ID_THEORA:                   return R_CODEC_ID_THEORA;
        case AV_CODEC_ID_ASV1:                     return R_CODEC_ID_ASV1;
        case AV_CODEC_ID_ASV2:                     return R_CODEC_ID_ASV2;
        case AV_CODEC_ID_FFV1:                     return R_CODEC_ID_FFV1;
        case AV_CODEC_ID_4XM:                      return R_CODEC_ID_4XM;
        case AV_CODEC_ID_VCR1:                     return R_CODEC_ID_VCR1;
        case AV_CODEC_ID_CLJR:                     return R_CODEC_ID_CLJR;
        case AV_CODEC_ID_MDEC:                     return R_CODEC_ID_MDEC;
        case AV_CODEC_ID_ROQ:                      return R_CODEC_ID_ROQ;
        case AV_CODEC_ID_INTERPLAY_VIDEO:          return R_CODEC_ID_INTERPLAY_VIDEO;
        case AV_CODEC_ID_XAN_WC3:                  return R_CODEC_ID_XAN_WC3;
        case AV_CODEC_ID_XAN_WC4:                  return R_CODEC_ID_XAN_WC4;
        case AV_CODEC_ID_RPZA:                     return R_CODEC_ID_RPZA;
        case AV_CODEC_ID_CINEPAK:                  return R_CODEC_ID_CINEPAK;
        case AV_CODEC_ID_WS_VQA:                   return R_CODEC_ID_WS_VQA;
        case AV_CODEC_ID_MSRLE:                    return R_CODEC_ID_MSRLE;
        case AV_CODEC_ID_MSVIDEO1:                 return R_CODEC_ID_MSVIDEO1;
        case AV_CODEC_ID_IDCIN:                    return R_CODEC_ID_IDCIN;
        case AV_CODEC_ID_8BPS:                     return R_CODEC_ID_8BPS;
        case AV_CODEC_ID_SMC:                      return R_CODEC_ID_SMC;
        case AV_CODEC_ID_FLIC:                     return R_CODEC_ID_FLIC;
        case AV_CODEC_ID_TRUEMOTION1:              return R_CODEC_ID_TRUEMOTION1;
        case AV_CODEC_ID_VMDVIDEO:                 return R_CODEC_ID_VMDVIDEO;
        case AV_CODEC_ID_MSZH:                     return R_CODEC_ID_MSZH;
        case AV_CODEC_ID_ZLIB:                     return R_CODEC_ID_ZLIB;
        case AV_CODEC_ID_QTRLE:                    return R_CODEC_ID_QTRLE;
        case AV_CODEC_ID_TSCC:                     return R_CODEC_ID_TSCC;
        case AV_CODEC_ID_ULTI:                     return R_CODEC_ID_ULTI;
        case AV_CODEC_ID_QDRAW:                    return R_CODEC_ID_QDRAW;
        case AV_CODEC_ID_VIXL:                     return R_CODEC_ID_VIXL;
        case AV_CODEC_ID_QPEG:                     return R_CODEC_ID_QPEG;
        case AV_CODEC_ID_PNG:                      return R_CODEC_ID_PNG;
        case AV_CODEC_ID_PPM:                      return R_CODEC_ID_PPM;
        case AV_CODEC_ID_PBM:                      return R_CODEC_ID_PBM;
        case AV_CODEC_ID_PGM:                      return R_CODEC_ID_PGM;
        case AV_CODEC_ID_PGMYUV:                   return R_CODEC_ID_PGMYUV;
        case AV_CODEC_ID_PAM:                      return R_CODEC_ID_PAM;
        case AV_CODEC_ID_FFVHUFF:                  return R_CODEC_ID_FFVHUFF;
        case AV_CODEC_ID_RV30:                     return R_CODEC_ID_RV30;
        case AV_CODEC_ID_RV40:                     return R_CODEC_ID_RV40;
        case AV_CODEC_ID_VC1:                      return R_CODEC_ID_VC1;
        case AV_CODEC_ID_WMV3:                     return R_CODEC_ID_WMV3;
        case AV_CODEC_ID_LOCO:                     return R_CODEC_ID_LOCO;
        case AV_CODEC_ID_WNV1:                     return R_CODEC_ID_WNV1;
        case AV_CODEC_ID_AASC:                     return R_CODEC_ID_AASC;
        case AV_CODEC_ID_INDEO2:                   return R_CODEC_ID_INDEO2;
        case AV_CODEC_ID_FRAPS:                    return R_CODEC_ID_FRAPS;
        case AV_CODEC_ID_TRUEMOTION2:              return R_CODEC_ID_TRUEMOTION2;
        case AV_CODEC_ID_BMP:                      return R_CODEC_ID_BMP;
        case AV_CODEC_ID_CSCD:                     return R_CODEC_ID_CSCD;
        case AV_CODEC_ID_MMVIDEO:                  return R_CODEC_ID_MMVIDEO;
        case AV_CODEC_ID_ZMBV:                     return R_CODEC_ID_ZMBV;
        case AV_CODEC_ID_AVS:                      return R_CODEC_ID_AVS;
        case AV_CODEC_ID_SMACKVIDEO:               return R_CODEC_ID_SMACKVIDEO;
        case AV_CODEC_ID_NUV:                      return R_CODEC_ID_NUV;
        case AV_CODEC_ID_KMVC:                     return R_CODEC_ID_KMVC;
        case AV_CODEC_ID_FLASHSV:                  return R_CODEC_ID_FLASHSV;
        case AV_CODEC_ID_CAVS:                     return R_CODEC_ID_CAVS;
        case AV_CODEC_ID_JPEG2000:                 return R_CODEC_ID_JPEG2000;
        case AV_CODEC_ID_VMNC:                     return R_CODEC_ID_VMNC;
        case AV_CODEC_ID_VP5:                      return R_CODEC_ID_VP5;
        case AV_CODEC_ID_VP6:                      return R_CODEC_ID_VP6;
        case AV_CODEC_ID_VP6F:                     return R_CODEC_ID_VP6F;
        case AV_CODEC_ID_TARGA:                    return R_CODEC_ID_TARGA;
        case AV_CODEC_ID_DSICINVIDEO:              return R_CODEC_ID_DSICINVIDEO;
        case AV_CODEC_ID_TIERTEXSEQVIDEO:          return R_CODEC_ID_TIERTEXSEQVIDEO;
        case AV_CODEC_ID_TIFF:                     return R_CODEC_ID_TIFF;
        case AV_CODEC_ID_GIF:                      return R_CODEC_ID_GIF;
        case AV_CODEC_ID_DXA:                      return R_CODEC_ID_DXA;
        case AV_CODEC_ID_DNXHD:                    return R_CODEC_ID_DNXHD;
        case AV_CODEC_ID_THP:                      return R_CODEC_ID_THP;
        case AV_CODEC_ID_SGI:                      return R_CODEC_ID_SGI;
        case AV_CODEC_ID_C93:                      return R_CODEC_ID_C93;
        case AV_CODEC_ID_BETHSOFTVID:              return R_CODEC_ID_BETHSOFTVID;
        case AV_CODEC_ID_PTX:                      return R_CODEC_ID_PTX;
        case AV_CODEC_ID_TXD:                      return R_CODEC_ID_TXD;
        case AV_CODEC_ID_VP6A:                     return R_CODEC_ID_VP6A;
        case AV_CODEC_ID_AMV:                      return R_CODEC_ID_AMV;
        case AV_CODEC_ID_VB:                       return R_CODEC_ID_VB;
        case AV_CODEC_ID_PCX:                      return R_CODEC_ID_PCX;
        case AV_CODEC_ID_SUNRAST:                  return R_CODEC_ID_SUNRAST;
        case AV_CODEC_ID_INDEO4:                   return R_CODEC_ID_INDEO4;
        case AV_CODEC_ID_INDEO5:                   return R_CODEC_ID_INDEO5;
        case AV_CODEC_ID_MIMIC:                    return R_CODEC_ID_MIMIC;
        case AV_CODEC_ID_RL2:                      return R_CODEC_ID_RL2;
        case AV_CODEC_ID_ESCAPE124:                return R_CODEC_ID_ESCAPE124;
        case AV_CODEC_ID_DIRAC:                    return R_CODEC_ID_DIRAC;
        case AV_CODEC_ID_BFI:                      return R_CODEC_ID_BFI;
        case AV_CODEC_ID_CMV:                      return R_CODEC_ID_CMV;
        case AV_CODEC_ID_MOTIONPIXELS:             return R_CODEC_ID_MOTIONPIXELS;
        case AV_CODEC_ID_TGV:                      return R_CODEC_ID_TGV;
        case AV_CODEC_ID_TGQ:                      return R_CODEC_ID_TGQ;
        case AV_CODEC_ID_TQI:                      return R_CODEC_ID_TQI;
        case AV_CODEC_ID_AURA:                     return R_CODEC_ID_AURA;
        case AV_CODEC_ID_AURA2:                    return R_CODEC_ID_AURA2;
        case AV_CODEC_ID_V210X:                    return R_CODEC_ID_V210X;
        case AV_CODEC_ID_TMV:                      return R_CODEC_ID_TMV;
        case AV_CODEC_ID_V210:                     return R_CODEC_ID_V210;
        case AV_CODEC_ID_DPX:                      return R_CODEC_ID_DPX;
        case AV_CODEC_ID_MAD:                      return R_CODEC_ID_MAD;
        case AV_CODEC_ID_FRWU:                     return R_CODEC_ID_FRWU;
        case AV_CODEC_ID_FLASHSV2:                 return R_CODEC_ID_FLASHSV2;
        case AV_CODEC_ID_CDGRAPHICS:               return R_CODEC_ID_CDGRAPHICS;
        case AV_CODEC_ID_R210:                     return R_CODEC_ID_R210;
        case AV_CODEC_ID_ANM:                      return R_CODEC_ID_ANM;
        case AV_CODEC_ID_BINKVIDEO:                return R_CODEC_ID_BINKVIDEO;
        case AV_CODEC_ID_IFF_ILBM:                 return R_CODEC_ID_IFF_ILBM;
        case AV_CODEC_ID_KGV1:                     return R_CODEC_ID_KGV1;
        case AV_CODEC_ID_YOP:                      return R_CODEC_ID_YOP;
        case AV_CODEC_ID_VP8:                      return R_CODEC_ID_VP8;
        case AV_CODEC_ID_PICTOR:                   return R_CODEC_ID_PICTOR;
        case AV_CODEC_ID_ANSI:                     return R_CODEC_ID_ANSI;
        case AV_CODEC_ID_A64_MULTI:                return R_CODEC_ID_A64_MULTI;
        case AV_CODEC_ID_A64_MULTI5:               return R_CODEC_ID_A64_MULTI5;
        case AV_CODEC_ID_R10K:                     return R_CODEC_ID_R10K;
        case AV_CODEC_ID_MXPEG:                    return R_CODEC_ID_MXPEG;
        case AV_CODEC_ID_LAGARITH:                 return R_CODEC_ID_LAGARITH;
        case AV_CODEC_ID_PRORES:                   return R_CODEC_ID_PRORES;
        case AV_CODEC_ID_JV:                       return R_CODEC_ID_JV;
        case AV_CODEC_ID_DFA:                      return R_CODEC_ID_DFA;
        case AV_CODEC_ID_WMV3IMAGE:                return R_CODEC_ID_WMV3IMAGE;
        case AV_CODEC_ID_VC1IMAGE:                 return R_CODEC_ID_VC1IMAGE;
        case AV_CODEC_ID_UTVIDEO:                  return R_CODEC_ID_UTVIDEO;
        case AV_CODEC_ID_BMV_VIDEO:                return R_CODEC_ID_BMV_VIDEO;
        case AV_CODEC_ID_VBLE:                     return R_CODEC_ID_VBLE;
        case AV_CODEC_ID_DXTORY:                   return R_CODEC_ID_DXTORY;
        case AV_CODEC_ID_V410:                     return R_CODEC_ID_V410;
        case AV_CODEC_ID_XWD:                      return R_CODEC_ID_XWD;
        case AV_CODEC_ID_CDXL:                     return R_CODEC_ID_CDXL;
        case AV_CODEC_ID_XBM:                      return R_CODEC_ID_XBM;
        case AV_CODEC_ID_ZEROCODEC:                return R_CODEC_ID_ZEROCODEC;
        case AV_CODEC_ID_MSS1:                     return R_CODEC_ID_MSS1;
        case AV_CODEC_ID_MSA1:                     return R_CODEC_ID_MSA1;
        case AV_CODEC_ID_TSCC2:                    return R_CODEC_ID_TSCC2;
        case AV_CODEC_ID_MTS2:                     return R_CODEC_ID_MTS2;
        case AV_CODEC_ID_CLLC:                     return R_CODEC_ID_CLLC;
        case AV_CODEC_ID_MSS2:                     return R_CODEC_ID_MSS2;
        case AV_CODEC_ID_VP9:                      return R_CODEC_ID_VP9;
        case AV_CODEC_ID_AIC:                      return R_CODEC_ID_AIC;
            
        case AV_CODEC_ID_BRENDER_PIX:              return R_CODEC_ID_BRENDER_PIX;
        case AV_CODEC_ID_Y41P:                     return R_CODEC_ID_Y41P;
        case AV_CODEC_ID_ESCAPE130:                return R_CODEC_ID_ESCAPE130;
        case AV_CODEC_ID_EXR:                      return R_CODEC_ID_EXR;
        case AV_CODEC_ID_AVRP:                     return R_CODEC_ID_AVRP;
            
        case AV_CODEC_ID_012V:                     return R_CODEC_ID_012V;
        case AV_CODEC_ID_G2M:                      return R_CODEC_ID_G2M;
        case AV_CODEC_ID_AVUI:                     return R_CODEC_ID_AVUI;
        case AV_CODEC_ID_AYUV:                     return R_CODEC_ID_AYUV;
        case AV_CODEC_ID_TARGA_Y216:               return R_CODEC_ID_TARGA_Y216;
        case AV_CODEC_ID_V308:                     return R_CODEC_ID_V308;
        case AV_CODEC_ID_V408:                     return R_CODEC_ID_V408;
        case AV_CODEC_ID_YUV4:                     return R_CODEC_ID_YUV4;
        case AV_CODEC_ID_SANM:                     return R_CODEC_ID_SANM;
        case AV_CODEC_ID_PAF_VIDEO:                return R_CODEC_ID_PAF_VIDEO;
        case AV_CODEC_ID_AVRN:                     return R_CODEC_ID_AVRN;
        case AV_CODEC_ID_CPIA:                     return R_CODEC_ID_CPIA;
        case AV_CODEC_ID_XFACE:                    return R_CODEC_ID_XFACE;
        case AV_CODEC_ID_SGIRLE:                   return R_CODEC_ID_SGIRLE;
        case AV_CODEC_ID_MVC1:                     return R_CODEC_ID_MVC1;
        case AV_CODEC_ID_MVC2:                     return R_CODEC_ID_MVC2;
        case AV_CODEC_ID_SNOW:                     return R_CODEC_ID_SNOW;
        case AV_CODEC_ID_WEBP:                     return R_CODEC_ID_WEBP;
        case AV_CODEC_ID_SMVJPEG:                  return R_CODEC_ID_SMVJPEG;
        case AV_CODEC_ID_HEVC:                     return R_CODEC_ID_HEVC;
            
            /* various PCM "case media_base::CODECs" */
        case AV_CODEC_ID_PCM_S16LE:                return R_CODEC_ID_PCM_S16LE;
        case AV_CODEC_ID_PCM_S16BE:                return R_CODEC_ID_PCM_S16BE;
        case AV_CODEC_ID_PCM_U16LE:                return R_CODEC_ID_PCM_U16LE;
        case AV_CODEC_ID_PCM_U16BE:                return R_CODEC_ID_PCM_U16BE;
        case AV_CODEC_ID_PCM_S8:                   return R_CODEC_ID_PCM_S8;
        case AV_CODEC_ID_PCM_U8:                   return R_CODEC_ID_PCM_U8;
        case AV_CODEC_ID_PCM_MULAW:                return R_CODEC_ID_PCM_MULAW;
        case AV_CODEC_ID_PCM_ALAW:                 return R_CODEC_ID_PCM_ALAW;
        case AV_CODEC_ID_PCM_S32LE:                return R_CODEC_ID_PCM_S32LE;
        case AV_CODEC_ID_PCM_S32BE:                return R_CODEC_ID_PCM_S32BE;
        case AV_CODEC_ID_PCM_U32LE:                return R_CODEC_ID_PCM_U32LE;
        case AV_CODEC_ID_PCM_U32BE:                return R_CODEC_ID_PCM_U32BE;
        case AV_CODEC_ID_PCM_S24LE:                return R_CODEC_ID_PCM_S24LE;
        case AV_CODEC_ID_PCM_S24BE:                return R_CODEC_ID_PCM_S24BE;
        case AV_CODEC_ID_PCM_U24LE:                return R_CODEC_ID_PCM_U24LE;
        case AV_CODEC_ID_PCM_U24BE:                return R_CODEC_ID_PCM_U24BE;
        case AV_CODEC_ID_PCM_S24DAUD:              return R_CODEC_ID_PCM_S24DAUD;
        case AV_CODEC_ID_PCM_ZORK:                 return R_CODEC_ID_PCM_ZORK;
        case AV_CODEC_ID_PCM_S16LE_PLANAR:         return R_CODEC_ID_PCM_S16LE_PLANAR;
        case AV_CODEC_ID_PCM_DVD:                  return R_CODEC_ID_PCM_DVD;
        case AV_CODEC_ID_PCM_F32BE:                return R_CODEC_ID_PCM_F32BE;
        case AV_CODEC_ID_PCM_F32LE:                return R_CODEC_ID_PCM_F32LE;
        case AV_CODEC_ID_PCM_F64BE:                return R_CODEC_ID_PCM_F64BE;
        case AV_CODEC_ID_PCM_F64LE:                return R_CODEC_ID_PCM_F64LE;
        case AV_CODEC_ID_PCM_BLURAY:               return R_CODEC_ID_PCM_BLURAY;
        case AV_CODEC_ID_PCM_LXF:                  return R_CODEC_ID_PCM_LXF;
        case AV_CODEC_ID_S302M:                    return R_CODEC_ID_S302M;
        case AV_CODEC_ID_PCM_S8_PLANAR:            return R_CODEC_ID_PCM_S8_PLANAR;
        case AV_CODEC_ID_PCM_S24LE_PLANAR:         return R_CODEC_ID_PCM_S24LE_PLANAR;
        case AV_CODEC_ID_PCM_S32LE_PLANAR:         return R_CODEC_ID_PCM_S32LE_PLANAR;
        case AV_CODEC_ID_PCM_S16BE_PLANAR:         return R_CODEC_ID_PCM_S16BE_PLANAR;
            
            /* various ADPCM case media_base::CODECs */
        case AV_CODEC_ID_ADPCM_IMA_QT:             return R_CODEC_ID_ADPCM_IMA_QT;
        case AV_CODEC_ID_ADPCM_IMA_WAV:            return R_CODEC_ID_ADPCM_IMA_WAV;
        case AV_CODEC_ID_ADPCM_IMA_DK3:            return R_CODEC_ID_ADPCM_IMA_DK3;
        case AV_CODEC_ID_ADPCM_IMA_DK4:            return R_CODEC_ID_ADPCM_IMA_DK4;
        case AV_CODEC_ID_ADPCM_IMA_WS:             return R_CODEC_ID_ADPCM_IMA_WS;
        case AV_CODEC_ID_ADPCM_IMA_SMJPEG:         return R_CODEC_ID_ADPCM_IMA_SMJPEG;
        case AV_CODEC_ID_ADPCM_MS:                 return R_CODEC_ID_ADPCM_MS;
        case AV_CODEC_ID_ADPCM_4XM:                return R_CODEC_ID_ADPCM_4XM;
        case AV_CODEC_ID_ADPCM_XA:                 return R_CODEC_ID_ADPCM_XA;
        case AV_CODEC_ID_ADPCM_ADX:                return R_CODEC_ID_ADPCM_ADX;
        case AV_CODEC_ID_ADPCM_EA:                 return R_CODEC_ID_ADPCM_EA;
        case AV_CODEC_ID_ADPCM_G726:               return R_CODEC_ID_ADPCM_G726;
        case AV_CODEC_ID_ADPCM_CT:                 return R_CODEC_ID_ADPCM_CT;
        case AV_CODEC_ID_ADPCM_SWF:                return R_CODEC_ID_ADPCM_SWF;
        case AV_CODEC_ID_ADPCM_YAMAHA:             return R_CODEC_ID_ADPCM_YAMAHA;
        case AV_CODEC_ID_ADPCM_SBPRO_4:            return R_CODEC_ID_ADPCM_SBPRO_4;
        case AV_CODEC_ID_ADPCM_SBPRO_3:            return R_CODEC_ID_ADPCM_SBPRO_3;
        case AV_CODEC_ID_ADPCM_SBPRO_2:            return R_CODEC_ID_ADPCM_SBPRO_2;
        case AV_CODEC_ID_ADPCM_THP:                return R_CODEC_ID_ADPCM_THP;
        case AV_CODEC_ID_ADPCM_IMA_AMV:            return R_CODEC_ID_ADPCM_IMA_AMV;
        case AV_CODEC_ID_ADPCM_EA_R1:              return R_CODEC_ID_ADPCM_EA_R1;
        case AV_CODEC_ID_ADPCM_EA_R3:              return R_CODEC_ID_ADPCM_EA_R3;
        case AV_CODEC_ID_ADPCM_EA_R2:              return R_CODEC_ID_ADPCM_EA_R2;
        case AV_CODEC_ID_ADPCM_IMA_EA_SEAD:        return R_CODEC_ID_ADPCM_IMA_EA_SEAD;
        case AV_CODEC_ID_ADPCM_IMA_EA_EACS:        return R_CODEC_ID_ADPCM_IMA_EA_EACS;
        case AV_CODEC_ID_ADPCM_EA_XAS:             return R_CODEC_ID_ADPCM_EA_XAS;
        case AV_CODEC_ID_ADPCM_EA_MAXIS_XA:        return R_CODEC_ID_ADPCM_EA_MAXIS_XA;
        case AV_CODEC_ID_ADPCM_IMA_ISS:            return R_CODEC_ID_ADPCM_IMA_ISS;
        case AV_CODEC_ID_ADPCM_G722:               return R_CODEC_ID_ADPCM_G722;
        case AV_CODEC_ID_ADPCM_IMA_APC:            return R_CODEC_ID_ADPCM_IMA_APC;
        case AV_CODEC_ID_ADPCM_AFC:                return R_CODEC_ID_ADPCM_AFC;
        case AV_CODEC_ID_ADPCM_IMA_OKI:            return R_CODEC_ID_ADPCM_IMA_OKI;
        case AV_CODEC_ID_ADPCM_DTK:                return R_CODEC_ID_ADPCM_DTK;
        case AV_CODEC_ID_ADPCM_IMA_RAD:            return R_CODEC_ID_ADPCM_IMA_RAD;
            
            /* AMR */
        case AV_CODEC_ID_AMR_NB:                   return R_CODEC_ID_AMR_NB;
        case AV_CODEC_ID_AMR_WB:                   return R_CODEC_ID_AMR_WB;
            
            /* RealAudio case media_base::CODECs*/
        case AV_CODEC_ID_RA_144:                   return R_CODEC_ID_RA_144;
        case AV_CODEC_ID_RA_288:                   return R_CODEC_ID_RA_288;
            
            /* various DPCM case media_base::CODECs */
        case AV_CODEC_ID_ROQ_DPCM:                 return R_CODEC_ID_ROQ_DPCM;
        case AV_CODEC_ID_INTERPLAY_DPCM:           return R_CODEC_ID_INTERPLAY_DPCM;
        case AV_CODEC_ID_XAN_DPCM:                 return R_CODEC_ID_XAN_DPCM;
        case AV_CODEC_ID_SOL_DPCM:                 return R_CODEC_ID_SOL_DPCM;
            
            /* audio case media_base::CODECs */
        case AV_CODEC_ID_MP2:                      return R_CODEC_ID_MP2;
        case AV_CODEC_ID_MP3:                      return R_CODEC_ID_MP3;
        case AV_CODEC_ID_AAC:                      return R_CODEC_ID_AAC;
        case AV_CODEC_ID_AC3:                      return R_CODEC_ID_AC3;
        case AV_CODEC_ID_DTS:                      return R_CODEC_ID_DTS;
        case AV_CODEC_ID_VORBIS:                   return R_CODEC_ID_VORBIS;
        case AV_CODEC_ID_DVAUDIO:                  return R_CODEC_ID_DVAUDIO;
        case AV_CODEC_ID_WMAV1:                    return R_CODEC_ID_WMAV1;
        case AV_CODEC_ID_WMAV2:                    return R_CODEC_ID_WMAV2;
        case AV_CODEC_ID_MACE3:                    return R_CODEC_ID_MACE3;
        case AV_CODEC_ID_MACE6:                    return R_CODEC_ID_MACE6;
        case AV_CODEC_ID_VMDAUDIO:                 return R_CODEC_ID_VMDAUDIO;
        case AV_CODEC_ID_FLAC:                     return R_CODEC_ID_FLAC;
        case AV_CODEC_ID_MP3ADU:                   return R_CODEC_ID_MP3ADU;
        case AV_CODEC_ID_MP3ON4:                   return R_CODEC_ID_MP3ON4;
        case AV_CODEC_ID_SHORTEN:                  return R_CODEC_ID_SHORTEN;
        case AV_CODEC_ID_ALAC:                     return R_CODEC_ID_ALAC;
        case AV_CODEC_ID_WESTWOOD_SND1:            return R_CODEC_ID_WESTWOOD_SND1;
        case AV_CODEC_ID_GSM:                      return R_CODEC_ID_GSM;
        case AV_CODEC_ID_QDM2:                     return R_CODEC_ID_QDM2;
        case AV_CODEC_ID_COOK:                     return R_CODEC_ID_COOK;
        case AV_CODEC_ID_TRUESPEECH:               return R_CODEC_ID_TRUESPEECH;
        case AV_CODEC_ID_TTA:                      return R_CODEC_ID_TTA;
        case AV_CODEC_ID_SMACKAUDIO:               return R_CODEC_ID_SMACKAUDIO;
        case AV_CODEC_ID_QCELP:                    return R_CODEC_ID_QCELP;
        case AV_CODEC_ID_WAVPACK:                  return R_CODEC_ID_WAVPACK;
        case AV_CODEC_ID_DSICINAUDIO:              return R_CODEC_ID_DSICINAUDIO;
        case AV_CODEC_ID_IMC:                      return R_CODEC_ID_IMC;
        case AV_CODEC_ID_MUSEPACK7:                return R_CODEC_ID_MUSEPACK7;
        case AV_CODEC_ID_MLP:                      return R_CODEC_ID_MLP;
        case AV_CODEC_ID_GSM_MS:                   return R_CODEC_ID_GSM_MS;
        case AV_CODEC_ID_ATRAC3:                   return R_CODEC_ID_ATRAC3;
        case AV_CODEC_ID_NELLYMOSER:               return R_CODEC_ID_NELLYMOSER;
        case AV_CODEC_ID_MUSEPACK8:                return R_CODEC_ID_MUSEPACK8;
        case AV_CODEC_ID_SPEEX:                    return R_CODEC_ID_SPEEX;
        case AV_CODEC_ID_WMAVOICE:                 return R_CODEC_ID_WMAVOICE;
        case AV_CODEC_ID_WMAPRO:                   return R_CODEC_ID_WMAPRO;
        case AV_CODEC_ID_WMALOSSLESS:              return R_CODEC_ID_WMALOSSLESS;
        case AV_CODEC_ID_ATRAC3P:                  return R_CODEC_ID_ATRAC3P;
        case AV_CODEC_ID_EAC3:                     return R_CODEC_ID_EAC3;
        case AV_CODEC_ID_SIPR:                     return R_CODEC_ID_SIPR;
        case AV_CODEC_ID_MP1:                      return R_CODEC_ID_MP1;
        case AV_CODEC_ID_TWINVQ:                   return R_CODEC_ID_TWINVQ;
        case AV_CODEC_ID_TRUEHD:                   return R_CODEC_ID_TRUEHD;
        case AV_CODEC_ID_MP4ALS:                   return R_CODEC_ID_MP4ALS;
        case AV_CODEC_ID_ATRAC1:                   return R_CODEC_ID_ATRAC1;
        case AV_CODEC_ID_BINKAUDIO_RDFT:           return R_CODEC_ID_BINKAUDIO_RDFT;
        case AV_CODEC_ID_BINKAUDIO_DCT:            return R_CODEC_ID_BINKAUDIO_DCT;
        case AV_CODEC_ID_AAC_LATM:                 return R_CODEC_ID_AAC_LATM;
        case AV_CODEC_ID_QDMC:                     return R_CODEC_ID_QDMC;
        case AV_CODEC_ID_CELT:                     return R_CODEC_ID_CELT;
        case AV_CODEC_ID_G723_1:                   return R_CODEC_ID_G723_1;
        case AV_CODEC_ID_G729:                     return R_CODEC_ID_G729;
        case AV_CODEC_ID_8SVX_EXP:                 return R_CODEC_ID_8SVX_EXP;
        case AV_CODEC_ID_8SVX_FIB:                 return R_CODEC_ID_8SVX_FIB;
        case AV_CODEC_ID_BMV_AUDIO:                return R_CODEC_ID_BMV_AUDIO;
        case AV_CODEC_ID_RALF:                     return R_CODEC_ID_RALF;
        case AV_CODEC_ID_IAC:                      return R_CODEC_ID_IAC;
        case AV_CODEC_ID_ILBC:                     return R_CODEC_ID_ILBC;
        case AV_CODEC_ID_COMFORT_NOISE:            return R_CODEC_ID_COMFORT_NOISE;
        case AV_CODEC_ID_FFWAVESYNTH:              return R_CODEC_ID_FFWAVESYNTH;
        case AV_CODEC_ID_SONIC:                    return R_CODEC_ID_SONIC;
        case AV_CODEC_ID_SONIC_LS:                 return R_CODEC_ID_SONIC_LS;
        case AV_CODEC_ID_PAF_AUDIO:                return R_CODEC_ID_PAF_AUDIO;
        case AV_CODEC_ID_OPUS:                     return R_CODEC_ID_OPUS;
        case AV_CODEC_ID_TAK:                      return R_CODEC_ID_TAK;
        case AV_CODEC_ID_EVRC:                     return R_CODEC_ID_EVRC;
        case AV_CODEC_ID_SMV:                      return R_CODEC_ID_SMV;
            
            /* subtitle case media_base::CODECs */
        case AV_CODEC_ID_DVD_SUBTITLE:             return R_CODEC_ID_DVD_SUBTITLE;
        case AV_CODEC_ID_DVB_SUBTITLE:             return R_CODEC_ID_DVB_SUBTITLE;
        case AV_CODEC_ID_TEXT:                     return R_CODEC_ID_TEXT;
        case AV_CODEC_ID_XSUB:                     return R_CODEC_ID_XSUB;
        case AV_CODEC_ID_SSA:                      return R_CODEC_ID_SSA;
        case AV_CODEC_ID_MOV_TEXT:                 return R_CODEC_ID_MOV_TEXT;
        case AV_CODEC_ID_HDMV_PGS_SUBTITLE:        return R_CODEC_ID_HDMV_PGS_SUBTITLE;
        case AV_CODEC_ID_DVB_TELETEXT:             return R_CODEC_ID_DVB_TELETEXT;
        case AV_CODEC_ID_SRT:                      return R_CODEC_ID_SRT;
        case AV_CODEC_ID_MICRODVD:                 return R_CODEC_ID_MICRODVD;
        case AV_CODEC_ID_EIA_608:                  return R_CODEC_ID_EIA_608;
        case AV_CODEC_ID_JACOSUB:                  return R_CODEC_ID_JACOSUB;
        case AV_CODEC_ID_SAMI:                     return R_CODEC_ID_SAMI;
        case AV_CODEC_ID_REALTEXT:                 return R_CODEC_ID_REALTEXT;
        case AV_CODEC_ID_SUBVIEWER1:               return R_CODEC_ID_SUBVIEWER1;
        case AV_CODEC_ID_SUBVIEWER:                return R_CODEC_ID_SUBVIEWER;
        case AV_CODEC_ID_SUBRIP:                   return R_CODEC_ID_SUBRIP;
        case AV_CODEC_ID_WEBVTT:                   return R_CODEC_ID_WEBVTT;
        case AV_CODEC_ID_MPL2:                     return R_CODEC_ID_MPL2;
        case AV_CODEC_ID_VPLAYER:                  return R_CODEC_ID_VPLAYER;
        case AV_CODEC_ID_PJS:                      return R_CODEC_ID_PJS;
        case AV_CODEC_ID_ASS:                      return R_CODEC_ID_ASS;
            
            /* other specific kind of case media_base::CODECs (generally used for attachments) */
        case AV_CODEC_ID_TTF:                      return R_CODEC_ID_TTF;
        case AV_CODEC_ID_BINTEXT:                  return R_CODEC_ID_BINTEXT;
        case AV_CODEC_ID_XBIN:                     return R_CODEC_ID_XBIN;
        case AV_CODEC_ID_IDF:                      return R_CODEC_ID_IDF;
        case AV_CODEC_ID_OTF:                      return R_CODEC_ID_OTF;
        case AV_CODEC_ID_SMPTE_KLV:                return R_CODEC_ID_SMPTE_KLV;
        case AV_CODEC_ID_DVD_NAV:                  return R_CODEC_ID_DVD_NAV;
            
            
        case AV_CODEC_ID_PROBE:                    return R_CODEC_ID_PROBE;
        case AV_CODEC_ID_MPEG2TS:                  return R_CODEC_ID_MPEG2TS;
        case AV_CODEC_ID_MPEG4SYSTEMS:             return R_CODEC_ID_MPEG4SYSTEMS;
        case AV_CODEC_ID_FFMETADATA:               return R_CODEC_ID_FFMETADATA;
        default:                                   return R_CODEC_ID_NONE;
    }
}

enum AVCodecID MediaCodecIDToFFMpegCodecID(media_base::ResuableCodecID resuableCodecID)
{
    switch (resuableCodecID)
    {
            /* video case CODEC */
        case R_CODEC_ID_MPEG1VIDEO:               return AV_CODEC_ID_MPEG1VIDEO;
        case R_CODEC_ID_MPEG2VIDEO:               return AV_CODEC_ID_MPEG2VIDEO;
        case R_CODEC_ID_H261:                     return AV_CODEC_ID_H261;
        case R_CODEC_ID_H263:                     return AV_CODEC_ID_H263;
        case R_CODEC_ID_RV10:                     return AV_CODEC_ID_RV10;
        case R_CODEC_ID_RV20:                     return AV_CODEC_ID_RV20;
        case R_CODEC_ID_MJPEG:                    return AV_CODEC_ID_MJPEG;
        case R_CODEC_ID_MJPEGB:                   return AV_CODEC_ID_MJPEGB;
        case R_CODEC_ID_LJPEG:                    return AV_CODEC_ID_LJPEG;
        case R_CODEC_ID_SP5X:                     return AV_CODEC_ID_SP5X;
        case R_CODEC_ID_JPEGLS:                   return AV_CODEC_ID_JPEGLS;
        case R_CODEC_ID_MPEG4:                    return AV_CODEC_ID_MPEG4;
        case R_CODEC_ID_RAWVIDEO:                 return AV_CODEC_ID_RAWVIDEO;
        case R_CODEC_ID_MSMPEG4V1:                return AV_CODEC_ID_MSMPEG4V1;
        case R_CODEC_ID_MSMPEG4V2:                return AV_CODEC_ID_MSMPEG4V2;
        case R_CODEC_ID_MSMPEG4V3:                return AV_CODEC_ID_MSMPEG4V3;
        case R_CODEC_ID_WMV1:                     return AV_CODEC_ID_WMV1;
        case R_CODEC_ID_WMV2:                     return AV_CODEC_ID_WMV2;
        case R_CODEC_ID_H263P:                    return AV_CODEC_ID_H263P;
        case R_CODEC_ID_H263I:                    return AV_CODEC_ID_H263I;
        case R_CODEC_ID_FLV1:                     return AV_CODEC_ID_FLV1;
        case R_CODEC_ID_SVQ1:                     return AV_CODEC_ID_SVQ1;
        case R_CODEC_ID_SVQ3:                     return AV_CODEC_ID_SVQ3;
        case R_CODEC_ID_DVVIDEO:                  return AV_CODEC_ID_DVVIDEO;
        case R_CODEC_ID_HUFFYUV:                  return AV_CODEC_ID_HUFFYUV;
        case R_CODEC_ID_CYUV:                     return AV_CODEC_ID_CYUV;
        case R_CODEC_ID_H264:                     return AV_CODEC_ID_H264;
        case R_CODEC_ID_INDEO3:                   return AV_CODEC_ID_INDEO3;
        case R_CODEC_ID_VP3:                      return AV_CODEC_ID_VP3;
        case R_CODEC_ID_THEORA:                   return AV_CODEC_ID_THEORA;
        case R_CODEC_ID_ASV1:                     return AV_CODEC_ID_ASV1;
        case R_CODEC_ID_ASV2:                     return AV_CODEC_ID_ASV2;
        case R_CODEC_ID_FFV1:                     return AV_CODEC_ID_FFV1;
        case R_CODEC_ID_4XM:                      return AV_CODEC_ID_4XM;
        case R_CODEC_ID_VCR1:                     return AV_CODEC_ID_VCR1;
        case R_CODEC_ID_CLJR:                     return AV_CODEC_ID_CLJR;
        case R_CODEC_ID_MDEC:                     return AV_CODEC_ID_MDEC;
        case R_CODEC_ID_ROQ:                      return AV_CODEC_ID_ROQ;
        case R_CODEC_ID_INTERPLAY_VIDEO:          return AV_CODEC_ID_INTERPLAY_VIDEO;
        case R_CODEC_ID_XAN_WC3:                  return AV_CODEC_ID_XAN_WC3;
        case R_CODEC_ID_XAN_WC4:                  return AV_CODEC_ID_XAN_WC4;
        case R_CODEC_ID_RPZA:                     return AV_CODEC_ID_RPZA;
        case R_CODEC_ID_CINEPAK:                  return AV_CODEC_ID_CINEPAK;
        case R_CODEC_ID_WS_VQA:                   return AV_CODEC_ID_WS_VQA;
        case R_CODEC_ID_MSRLE:                    return AV_CODEC_ID_MSRLE;
        case R_CODEC_ID_MSVIDEO1:                 return AV_CODEC_ID_MSVIDEO1;
        case R_CODEC_ID_IDCIN:                    return AV_CODEC_ID_IDCIN;
        case R_CODEC_ID_8BPS:                     return AV_CODEC_ID_8BPS;
        case R_CODEC_ID_SMC:                      return AV_CODEC_ID_SMC;
        case R_CODEC_ID_FLIC:                     return AV_CODEC_ID_FLIC;
        case R_CODEC_ID_TRUEMOTION1:              return AV_CODEC_ID_TRUEMOTION1;
        case R_CODEC_ID_VMDVIDEO:                 return AV_CODEC_ID_VMDVIDEO;
        case R_CODEC_ID_MSZH:                     return AV_CODEC_ID_MSZH;
        case R_CODEC_ID_ZLIB:                     return AV_CODEC_ID_ZLIB;
        case R_CODEC_ID_QTRLE:                    return AV_CODEC_ID_QTRLE;
        case R_CODEC_ID_TSCC:                     return AV_CODEC_ID_TSCC;
        case R_CODEC_ID_ULTI:                     return AV_CODEC_ID_ULTI;
        case R_CODEC_ID_QDRAW:                    return AV_CODEC_ID_QDRAW;
        case R_CODEC_ID_VIXL:                     return AV_CODEC_ID_VIXL;
        case R_CODEC_ID_QPEG:                     return AV_CODEC_ID_QPEG;
        case R_CODEC_ID_PNG:                      return AV_CODEC_ID_PNG;
        case R_CODEC_ID_PPM:                      return AV_CODEC_ID_PPM;
        case R_CODEC_ID_PBM:                      return AV_CODEC_ID_PBM;
        case R_CODEC_ID_PGM:                      return AV_CODEC_ID_PGM;
        case R_CODEC_ID_PGMYUV:                   return AV_CODEC_ID_PGMYUV;
        case R_CODEC_ID_PAM:                      return AV_CODEC_ID_PAM;
        case R_CODEC_ID_FFVHUFF:                  return AV_CODEC_ID_FFVHUFF;
        case R_CODEC_ID_RV30:                     return AV_CODEC_ID_RV30;
        case R_CODEC_ID_RV40:                     return AV_CODEC_ID_RV40;
        case R_CODEC_ID_VC1:                      return AV_CODEC_ID_VC1;
        case R_CODEC_ID_WMV3:                     return AV_CODEC_ID_WMV3;
        case R_CODEC_ID_LOCO:                     return AV_CODEC_ID_LOCO;
        case R_CODEC_ID_WNV1:                     return AV_CODEC_ID_WNV1;
        case R_CODEC_ID_AASC:                     return AV_CODEC_ID_AASC;
        case R_CODEC_ID_INDEO2:                   return AV_CODEC_ID_INDEO2;
        case R_CODEC_ID_FRAPS:                    return AV_CODEC_ID_FRAPS;
        case R_CODEC_ID_TRUEMOTION2:              return AV_CODEC_ID_TRUEMOTION2;
        case R_CODEC_ID_BMP:                      return AV_CODEC_ID_BMP;
        case R_CODEC_ID_CSCD:                     return AV_CODEC_ID_CSCD;
        case R_CODEC_ID_MMVIDEO:                  return AV_CODEC_ID_MMVIDEO;
        case R_CODEC_ID_ZMBV:                     return AV_CODEC_ID_ZMBV;
        case R_CODEC_ID_AVS:                      return AV_CODEC_ID_AVS;
        case R_CODEC_ID_SMACKVIDEO:               return AV_CODEC_ID_SMACKVIDEO;
        case R_CODEC_ID_NUV:                      return AV_CODEC_ID_NUV;
        case R_CODEC_ID_KMVC:                     return AV_CODEC_ID_KMVC;
        case R_CODEC_ID_FLASHSV:                  return AV_CODEC_ID_FLASHSV;
        case R_CODEC_ID_CAVS:                     return AV_CODEC_ID_CAVS;
        case R_CODEC_ID_JPEG2000:                 return AV_CODEC_ID_JPEG2000;
        case R_CODEC_ID_VMNC:                     return AV_CODEC_ID_VMNC;
        case R_CODEC_ID_VP5:                      return AV_CODEC_ID_VP5;
        case R_CODEC_ID_VP6:                      return AV_CODEC_ID_VP6;
        case R_CODEC_ID_VP6F:                     return AV_CODEC_ID_VP6F;
        case R_CODEC_ID_TARGA:                    return AV_CODEC_ID_TARGA;
        case R_CODEC_ID_DSICINVIDEO:              return AV_CODEC_ID_DSICINVIDEO;
        case R_CODEC_ID_TIERTEXSEQVIDEO:          return AV_CODEC_ID_TIERTEXSEQVIDEO;
        case R_CODEC_ID_TIFF:                     return AV_CODEC_ID_TIFF;
        case R_CODEC_ID_GIF:                      return AV_CODEC_ID_GIF;
        case R_CODEC_ID_DXA:                      return AV_CODEC_ID_DXA;
        case R_CODEC_ID_DNXHD:                    return AV_CODEC_ID_DNXHD;
        case R_CODEC_ID_THP:                      return AV_CODEC_ID_THP;
        case R_CODEC_ID_SGI:                      return AV_CODEC_ID_SGI;
        case R_CODEC_ID_C93:                      return AV_CODEC_ID_C93;
        case R_CODEC_ID_BETHSOFTVID:              return AV_CODEC_ID_BETHSOFTVID;
        case R_CODEC_ID_PTX:                      return AV_CODEC_ID_PTX;
        case R_CODEC_ID_TXD:                      return AV_CODEC_ID_TXD;
        case R_CODEC_ID_VP6A:                     return AV_CODEC_ID_VP6A;
        case R_CODEC_ID_AMV:                      return AV_CODEC_ID_AMV;
        case R_CODEC_ID_VB:                       return AV_CODEC_ID_VB;
        case R_CODEC_ID_PCX:                      return AV_CODEC_ID_PCX;
        case R_CODEC_ID_SUNRAST:                  return AV_CODEC_ID_SUNRAST;
        case R_CODEC_ID_INDEO4:                   return AV_CODEC_ID_INDEO4;
        case R_CODEC_ID_INDEO5:                   return AV_CODEC_ID_INDEO5;
        case R_CODEC_ID_MIMIC:                    return AV_CODEC_ID_MIMIC;
        case R_CODEC_ID_RL2:                      return AV_CODEC_ID_RL2;
        case R_CODEC_ID_ESCAPE124:                return AV_CODEC_ID_ESCAPE124;
        case R_CODEC_ID_DIRAC:                    return AV_CODEC_ID_DIRAC;
        case R_CODEC_ID_BFI:                      return AV_CODEC_ID_BFI;
        case R_CODEC_ID_CMV:                      return AV_CODEC_ID_CMV;
        case R_CODEC_ID_MOTIONPIXELS:             return AV_CODEC_ID_MOTIONPIXELS;
        case R_CODEC_ID_TGV:                      return AV_CODEC_ID_TGV;
        case R_CODEC_ID_TGQ:                      return AV_CODEC_ID_TGQ;
        case R_CODEC_ID_TQI:                      return AV_CODEC_ID_TQI;
        case R_CODEC_ID_AURA:                     return AV_CODEC_ID_AURA;
        case R_CODEC_ID_AURA2:                    return AV_CODEC_ID_AURA2;
        case R_CODEC_ID_V210X:                    return AV_CODEC_ID_V210X;
        case R_CODEC_ID_TMV:                      return AV_CODEC_ID_TMV;
        case R_CODEC_ID_V210:                     return AV_CODEC_ID_V210;
        case R_CODEC_ID_DPX:                      return AV_CODEC_ID_DPX;
        case R_CODEC_ID_MAD:                      return AV_CODEC_ID_MAD;
        case R_CODEC_ID_FRWU:                     return AV_CODEC_ID_FRWU;
        case R_CODEC_ID_FLASHSV2:                 return AV_CODEC_ID_FLASHSV2;
        case R_CODEC_ID_CDGRAPHICS:               return AV_CODEC_ID_CDGRAPHICS;
        case R_CODEC_ID_R210:                     return AV_CODEC_ID_R210;
        case R_CODEC_ID_ANM:                      return AV_CODEC_ID_ANM;
        case R_CODEC_ID_BINKVIDEO:                return AV_CODEC_ID_BINKVIDEO;
        case R_CODEC_ID_IFF_ILBM:                 return AV_CODEC_ID_IFF_ILBM;
        case R_CODEC_ID_KGV1:                     return AV_CODEC_ID_KGV1;
        case R_CODEC_ID_YOP:                      return AV_CODEC_ID_YOP;
        case R_CODEC_ID_VP8:                      return AV_CODEC_ID_VP8;
        case R_CODEC_ID_PICTOR:                   return AV_CODEC_ID_PICTOR;
        case R_CODEC_ID_ANSI:                     return AV_CODEC_ID_ANSI;
        case R_CODEC_ID_A64_MULTI:                return AV_CODEC_ID_A64_MULTI;
        case R_CODEC_ID_A64_MULTI5:               return AV_CODEC_ID_A64_MULTI5;
        case R_CODEC_ID_R10K:                     return AV_CODEC_ID_R10K;
        case R_CODEC_ID_MXPEG:                    return AV_CODEC_ID_MXPEG;
        case R_CODEC_ID_LAGARITH:                 return AV_CODEC_ID_LAGARITH;
        case R_CODEC_ID_PRORES:                   return AV_CODEC_ID_PRORES;
        case R_CODEC_ID_JV:                       return AV_CODEC_ID_JV;
        case R_CODEC_ID_DFA:                      return AV_CODEC_ID_DFA;
        case R_CODEC_ID_WMV3IMAGE:                return AV_CODEC_ID_WMV3IMAGE;
        case R_CODEC_ID_VC1IMAGE:                 return AV_CODEC_ID_VC1IMAGE;
        case R_CODEC_ID_UTVIDEO:                  return AV_CODEC_ID_UTVIDEO;
        case R_CODEC_ID_BMV_VIDEO:                return AV_CODEC_ID_BMV_VIDEO;
        case R_CODEC_ID_VBLE:                     return AV_CODEC_ID_VBLE;
        case R_CODEC_ID_DXTORY:                   return AV_CODEC_ID_DXTORY;
        case R_CODEC_ID_V410:                     return AV_CODEC_ID_V410;
        case R_CODEC_ID_XWD:                      return AV_CODEC_ID_XWD;
        case R_CODEC_ID_CDXL:                     return AV_CODEC_ID_CDXL;
        case R_CODEC_ID_XBM:                      return AV_CODEC_ID_XBM;
        case R_CODEC_ID_ZEROCODEC:                return AV_CODEC_ID_ZEROCODEC;
        case R_CODEC_ID_MSS1:                     return AV_CODEC_ID_MSS1;
        case R_CODEC_ID_MSA1:                     return AV_CODEC_ID_MSA1;
        case R_CODEC_ID_TSCC2:                    return AV_CODEC_ID_TSCC2;
        case R_CODEC_ID_MTS2:                     return AV_CODEC_ID_MTS2;
        case R_CODEC_ID_CLLC:                     return AV_CODEC_ID_CLLC;
        case R_CODEC_ID_MSS2:                     return AV_CODEC_ID_MSS2;
        case R_CODEC_ID_VP9:                      return AV_CODEC_ID_VP9;
        case R_CODEC_ID_AIC:                      return AV_CODEC_ID_AIC;
            
        case R_CODEC_ID_BRENDER_PIX:              return AV_CODEC_ID_BRENDER_PIX;
        case R_CODEC_ID_Y41P:                     return AV_CODEC_ID_Y41P;
        case R_CODEC_ID_ESCAPE130:                return AV_CODEC_ID_ESCAPE130;
        case R_CODEC_ID_EXR:                      return AV_CODEC_ID_EXR;
        case R_CODEC_ID_AVRP:                     return AV_CODEC_ID_AVRP;
            
        case R_CODEC_ID_012V:                     return AV_CODEC_ID_012V;
        case R_CODEC_ID_G2M:                      return AV_CODEC_ID_G2M;
        case R_CODEC_ID_AVUI:                     return AV_CODEC_ID_AVUI;
        case R_CODEC_ID_AYUV:                     return AV_CODEC_ID_AYUV;
        case R_CODEC_ID_TARGA_Y216:               return AV_CODEC_ID_TARGA_Y216;
        case R_CODEC_ID_V308:                     return AV_CODEC_ID_V308;
        case R_CODEC_ID_V408:                     return AV_CODEC_ID_V408;
        case R_CODEC_ID_YUV4:                     return AV_CODEC_ID_YUV4;
        case R_CODEC_ID_SANM:                     return AV_CODEC_ID_SANM;
        case R_CODEC_ID_PAF_VIDEO:                return AV_CODEC_ID_PAF_VIDEO;
        case R_CODEC_ID_AVRN:                     return AV_CODEC_ID_AVRN;
        case R_CODEC_ID_CPIA:                     return AV_CODEC_ID_CPIA;
        case R_CODEC_ID_XFACE:                    return AV_CODEC_ID_XFACE;
        case R_CODEC_ID_SGIRLE:                   return AV_CODEC_ID_SGIRLE;
        case R_CODEC_ID_MVC1:                     return AV_CODEC_ID_MVC1;
        case R_CODEC_ID_MVC2:                     return AV_CODEC_ID_MVC2;
        case R_CODEC_ID_SNOW:                     return AV_CODEC_ID_SNOW;
        case R_CODEC_ID_WEBP:                     return AV_CODEC_ID_WEBP;
        case R_CODEC_ID_SMVJPEG:                  return AV_CODEC_ID_SMVJPEG;
        case R_CODEC_ID_HEVC:                     return AV_CODEC_ID_HEVC;
            
            /* various PCM "case media_base::CODECs" */
        case R_CODEC_ID_PCM_S16LE:                return AV_CODEC_ID_PCM_S16LE;
        case R_CODEC_ID_PCM_S16BE:                return AV_CODEC_ID_PCM_S16BE;
        case R_CODEC_ID_PCM_U16LE:                return AV_CODEC_ID_PCM_U16LE;
        case R_CODEC_ID_PCM_U16BE:                return AV_CODEC_ID_PCM_U16BE;
        case R_CODEC_ID_PCM_S8:                   return AV_CODEC_ID_PCM_S8;
        case R_CODEC_ID_PCM_U8:                   return AV_CODEC_ID_PCM_U8;
        case R_CODEC_ID_PCM_MULAW:                return AV_CODEC_ID_PCM_MULAW;
        case R_CODEC_ID_PCM_ALAW:                 return AV_CODEC_ID_PCM_ALAW;
        case R_CODEC_ID_PCM_S32LE:                return AV_CODEC_ID_PCM_S32LE;
        case R_CODEC_ID_PCM_S32BE:                return AV_CODEC_ID_PCM_S32BE;
        case R_CODEC_ID_PCM_U32LE:                return AV_CODEC_ID_PCM_U32LE;
        case R_CODEC_ID_PCM_U32BE:                return AV_CODEC_ID_PCM_U32BE;
        case R_CODEC_ID_PCM_S24LE:                return AV_CODEC_ID_PCM_S24LE;
        case R_CODEC_ID_PCM_S24BE:                return AV_CODEC_ID_PCM_S24BE;
        case R_CODEC_ID_PCM_U24LE:                return AV_CODEC_ID_PCM_U24LE;
        case R_CODEC_ID_PCM_U24BE:                return AV_CODEC_ID_PCM_U24BE;
        case R_CODEC_ID_PCM_S24DAUD:              return AV_CODEC_ID_PCM_S24DAUD;
        case R_CODEC_ID_PCM_ZORK:                 return AV_CODEC_ID_PCM_ZORK;
        case R_CODEC_ID_PCM_S16LE_PLANAR:         return AV_CODEC_ID_PCM_S16LE_PLANAR;
        case R_CODEC_ID_PCM_DVD:                  return AV_CODEC_ID_PCM_DVD;
        case R_CODEC_ID_PCM_F32BE:                return AV_CODEC_ID_PCM_F32BE;
        case R_CODEC_ID_PCM_F32LE:                return AV_CODEC_ID_PCM_F32LE;
        case R_CODEC_ID_PCM_F64BE:                return AV_CODEC_ID_PCM_F64BE;
        case R_CODEC_ID_PCM_F64LE:                return AV_CODEC_ID_PCM_F64LE;
        case R_CODEC_ID_PCM_BLURAY:               return AV_CODEC_ID_PCM_BLURAY;
        case R_CODEC_ID_PCM_LXF:                  return AV_CODEC_ID_PCM_LXF;
        case R_CODEC_ID_S302M:                    return AV_CODEC_ID_S302M;
        case R_CODEC_ID_PCM_S8_PLANAR:            return AV_CODEC_ID_PCM_S8_PLANAR;
        case R_CODEC_ID_PCM_S24LE_PLANAR:         return AV_CODEC_ID_PCM_S24LE_PLANAR;
        case R_CODEC_ID_PCM_S32LE_PLANAR:         return AV_CODEC_ID_PCM_S32LE_PLANAR;
        case R_CODEC_ID_PCM_S16BE_PLANAR:         return AV_CODEC_ID_PCM_S16BE_PLANAR;
            
            /* various ADPCM case media_base::CODECs */
        case R_CODEC_ID_ADPCM_IMA_QT:             return AV_CODEC_ID_ADPCM_IMA_QT;
        case R_CODEC_ID_ADPCM_IMA_WAV:            return AV_CODEC_ID_ADPCM_IMA_WAV;
        case R_CODEC_ID_ADPCM_IMA_DK3:            return AV_CODEC_ID_ADPCM_IMA_DK3;
        case R_CODEC_ID_ADPCM_IMA_DK4:            return AV_CODEC_ID_ADPCM_IMA_DK4;
        case R_CODEC_ID_ADPCM_IMA_WS:             return AV_CODEC_ID_ADPCM_IMA_WS;
        case R_CODEC_ID_ADPCM_IMA_SMJPEG:         return AV_CODEC_ID_ADPCM_IMA_SMJPEG;
        case R_CODEC_ID_ADPCM_MS:                 return AV_CODEC_ID_ADPCM_MS;
        case R_CODEC_ID_ADPCM_4XM:                return AV_CODEC_ID_ADPCM_4XM;
        case R_CODEC_ID_ADPCM_XA:                 return AV_CODEC_ID_ADPCM_XA;
        case R_CODEC_ID_ADPCM_ADX:                return AV_CODEC_ID_ADPCM_ADX;
        case R_CODEC_ID_ADPCM_EA:                 return AV_CODEC_ID_ADPCM_EA;
        case R_CODEC_ID_ADPCM_G726:               return AV_CODEC_ID_ADPCM_G726;
        case R_CODEC_ID_ADPCM_CT:                 return AV_CODEC_ID_ADPCM_CT;
        case R_CODEC_ID_ADPCM_SWF:                return AV_CODEC_ID_ADPCM_SWF;
        case R_CODEC_ID_ADPCM_YAMAHA:             return AV_CODEC_ID_ADPCM_YAMAHA;
        case R_CODEC_ID_ADPCM_SBPRO_4:            return AV_CODEC_ID_ADPCM_SBPRO_4;
        case R_CODEC_ID_ADPCM_SBPRO_3:            return AV_CODEC_ID_ADPCM_SBPRO_3;
        case R_CODEC_ID_ADPCM_SBPRO_2:            return AV_CODEC_ID_ADPCM_SBPRO_2;
        case R_CODEC_ID_ADPCM_THP:                return AV_CODEC_ID_ADPCM_THP;
        case R_CODEC_ID_ADPCM_IMA_AMV:            return AV_CODEC_ID_ADPCM_IMA_AMV;
        case R_CODEC_ID_ADPCM_EA_R1:              return AV_CODEC_ID_ADPCM_EA_R1;
        case R_CODEC_ID_ADPCM_EA_R3:              return AV_CODEC_ID_ADPCM_EA_R3;
        case R_CODEC_ID_ADPCM_EA_R2:              return AV_CODEC_ID_ADPCM_EA_R2;
        case R_CODEC_ID_ADPCM_IMA_EA_SEAD:        return AV_CODEC_ID_ADPCM_IMA_EA_SEAD;
        case R_CODEC_ID_ADPCM_IMA_EA_EACS:        return AV_CODEC_ID_ADPCM_IMA_EA_EACS;
        case R_CODEC_ID_ADPCM_EA_XAS:             return AV_CODEC_ID_ADPCM_EA_XAS;
        case R_CODEC_ID_ADPCM_EA_MAXIS_XA:        return AV_CODEC_ID_ADPCM_EA_MAXIS_XA;
        case R_CODEC_ID_ADPCM_IMA_ISS:            return AV_CODEC_ID_ADPCM_IMA_ISS;
        case R_CODEC_ID_ADPCM_G722:               return AV_CODEC_ID_ADPCM_G722;
        case R_CODEC_ID_ADPCM_IMA_APC:            return AV_CODEC_ID_ADPCM_IMA_APC;
        case R_CODEC_ID_ADPCM_AFC:                return AV_CODEC_ID_ADPCM_AFC;
        case R_CODEC_ID_ADPCM_IMA_OKI:            return AV_CODEC_ID_ADPCM_IMA_OKI;
        case R_CODEC_ID_ADPCM_DTK:                return AV_CODEC_ID_ADPCM_DTK;
        case R_CODEC_ID_ADPCM_IMA_RAD:            return AV_CODEC_ID_ADPCM_IMA_RAD;
            
            /* AMR */
        case R_CODEC_ID_AMR_NB:                   return AV_CODEC_ID_AMR_NB;
        case R_CODEC_ID_AMR_WB:                   return AV_CODEC_ID_AMR_WB;
            
            /* RealAudio case media_base::CODECs*/
        case R_CODEC_ID_RA_144:                   return AV_CODEC_ID_RA_144;
        case R_CODEC_ID_RA_288:                   return AV_CODEC_ID_RA_288;
            
            /* various DPCM case media_base::CODECs */
        case R_CODEC_ID_ROQ_DPCM:                 return AV_CODEC_ID_ROQ_DPCM;
        case R_CODEC_ID_INTERPLAY_DPCM:           return AV_CODEC_ID_INTERPLAY_DPCM;
        case R_CODEC_ID_XAN_DPCM:                 return AV_CODEC_ID_XAN_DPCM;
        case R_CODEC_ID_SOL_DPCM:                 return AV_CODEC_ID_SOL_DPCM;
            
            /* audio case media_base::CODECs */
        case R_CODEC_ID_MP2:                      return AV_CODEC_ID_MP2;
        case R_CODEC_ID_MP3:                      return AV_CODEC_ID_MP3;
        case R_CODEC_ID_AAC:                      return AV_CODEC_ID_AAC;
        case R_CODEC_ID_AC3:                      return AV_CODEC_ID_AC3;
        case R_CODEC_ID_DTS:                      return AV_CODEC_ID_DTS;
        case R_CODEC_ID_VORBIS:                   return AV_CODEC_ID_VORBIS;
        case R_CODEC_ID_DVAUDIO:                  return AV_CODEC_ID_DVAUDIO;
        case R_CODEC_ID_WMAV1:                    return AV_CODEC_ID_WMAV1;
        case R_CODEC_ID_WMAV2:                    return AV_CODEC_ID_WMAV2;
        case R_CODEC_ID_MACE3:                    return AV_CODEC_ID_MACE3;
        case R_CODEC_ID_MACE6:                    return AV_CODEC_ID_MACE6;
        case R_CODEC_ID_VMDAUDIO:                 return AV_CODEC_ID_VMDAUDIO;
        case R_CODEC_ID_FLAC:                     return AV_CODEC_ID_FLAC;
        case R_CODEC_ID_MP3ADU:                   return AV_CODEC_ID_MP3ADU;
        case R_CODEC_ID_MP3ON4:                   return AV_CODEC_ID_MP3ON4;
        case R_CODEC_ID_SHORTEN:                  return AV_CODEC_ID_SHORTEN;
        case R_CODEC_ID_ALAC:                     return AV_CODEC_ID_ALAC;
        case R_CODEC_ID_WESTWOOD_SND1:            return AV_CODEC_ID_WESTWOOD_SND1;
        case R_CODEC_ID_GSM:                      return AV_CODEC_ID_GSM;
        case R_CODEC_ID_QDM2:                     return AV_CODEC_ID_QDM2;
        case R_CODEC_ID_COOK:                     return AV_CODEC_ID_COOK;
        case R_CODEC_ID_TRUESPEECH:               return AV_CODEC_ID_TRUESPEECH;
        case R_CODEC_ID_TTA:                      return AV_CODEC_ID_TTA;
        case R_CODEC_ID_SMACKAUDIO:               return AV_CODEC_ID_SMACKAUDIO;
        case R_CODEC_ID_QCELP:                    return AV_CODEC_ID_QCELP;
        case R_CODEC_ID_WAVPACK:                  return AV_CODEC_ID_WAVPACK;
        case R_CODEC_ID_DSICINAUDIO:              return AV_CODEC_ID_DSICINAUDIO;
        case R_CODEC_ID_IMC:                      return AV_CODEC_ID_IMC;
        case R_CODEC_ID_MUSEPACK7:                return AV_CODEC_ID_MUSEPACK7;
        case R_CODEC_ID_MLP:                      return AV_CODEC_ID_MLP;
        case R_CODEC_ID_GSM_MS:                   return AV_CODEC_ID_GSM_MS;
        case R_CODEC_ID_ATRAC3:                   return AV_CODEC_ID_ATRAC3;
        case R_CODEC_ID_APE:                      return AV_CODEC_ID_APE;
        case R_CODEC_ID_NELLYMOSER:               return AV_CODEC_ID_NELLYMOSER;
        case R_CODEC_ID_MUSEPACK8:                return AV_CODEC_ID_MUSEPACK8;
        case R_CODEC_ID_SPEEX:                    return AV_CODEC_ID_SPEEX;
        case R_CODEC_ID_WMAVOICE:                 return AV_CODEC_ID_WMAVOICE;
        case R_CODEC_ID_WMAPRO:                   return AV_CODEC_ID_WMAPRO;
        case R_CODEC_ID_WMALOSSLESS:              return AV_CODEC_ID_WMALOSSLESS;
        case R_CODEC_ID_ATRAC3P:                  return AV_CODEC_ID_ATRAC3P;
        case R_CODEC_ID_EAC3:                     return AV_CODEC_ID_EAC3;
        case R_CODEC_ID_SIPR:                     return AV_CODEC_ID_SIPR;
        case R_CODEC_ID_MP1:                      return AV_CODEC_ID_MP1;
        case R_CODEC_ID_TWINVQ:                   return AV_CODEC_ID_TWINVQ;
        case R_CODEC_ID_TRUEHD:                   return AV_CODEC_ID_TRUEHD;
        case R_CODEC_ID_MP4ALS:                   return AV_CODEC_ID_MP4ALS;
        case R_CODEC_ID_ATRAC1:                   return AV_CODEC_ID_ATRAC1;
        case R_CODEC_ID_BINKAUDIO_RDFT:           return AV_CODEC_ID_BINKAUDIO_RDFT;
        case R_CODEC_ID_BINKAUDIO_DCT:            return AV_CODEC_ID_BINKAUDIO_DCT;
        case R_CODEC_ID_AAC_LATM:                 return AV_CODEC_ID_AAC_LATM;
        case R_CODEC_ID_QDMC:                     return AV_CODEC_ID_QDMC;
        case R_CODEC_ID_CELT:                     return AV_CODEC_ID_CELT;
        case R_CODEC_ID_G723_1:                   return AV_CODEC_ID_G723_1;
        case R_CODEC_ID_G729:                     return AV_CODEC_ID_G729;
        case R_CODEC_ID_8SVX_EXP:                 return AV_CODEC_ID_8SVX_EXP;
        case R_CODEC_ID_8SVX_FIB:                 return AV_CODEC_ID_8SVX_FIB;
        case R_CODEC_ID_BMV_AUDIO:                return AV_CODEC_ID_BMV_AUDIO;
        case R_CODEC_ID_RALF:                     return AV_CODEC_ID_RALF;
        case R_CODEC_ID_IAC:                      return AV_CODEC_ID_IAC;
        case R_CODEC_ID_ILBC:                     return AV_CODEC_ID_ILBC;
        case R_CODEC_ID_COMFORT_NOISE:            return AV_CODEC_ID_COMFORT_NOISE;
        case R_CODEC_ID_FFWAVESYNTH:              return AV_CODEC_ID_FFWAVESYNTH;
        case R_CODEC_ID_SONIC:                    return AV_CODEC_ID_SONIC;
        case R_CODEC_ID_SONIC_LS:                 return AV_CODEC_ID_SONIC_LS;
        case R_CODEC_ID_PAF_AUDIO:                return AV_CODEC_ID_PAF_AUDIO;
        case R_CODEC_ID_OPUS:                     return AV_CODEC_ID_OPUS;
        case R_CODEC_ID_TAK:                      return AV_CODEC_ID_TAK;
        case R_CODEC_ID_EVRC:                     return AV_CODEC_ID_EVRC;
        case R_CODEC_ID_SMV:                      return AV_CODEC_ID_SMV;
            
        /* subtitle case media_base::CODECs */
        case R_CODEC_ID_DVD_SUBTITLE:             return AV_CODEC_ID_DVD_SUBTITLE;
        case R_CODEC_ID_DVB_SUBTITLE:             return AV_CODEC_ID_DVB_SUBTITLE;
        case R_CODEC_ID_TEXT:                     return AV_CODEC_ID_TEXT;
        case R_CODEC_ID_XSUB:                     return AV_CODEC_ID_XSUB;
        case R_CODEC_ID_SSA:                      return AV_CODEC_ID_SSA;
        case R_CODEC_ID_MOV_TEXT:                 return AV_CODEC_ID_MOV_TEXT;
        case R_CODEC_ID_HDMV_PGS_SUBTITLE:        return AV_CODEC_ID_HDMV_PGS_SUBTITLE;
        case R_CODEC_ID_DVB_TELETEXT:             return AV_CODEC_ID_DVB_TELETEXT;
        case R_CODEC_ID_SRT:                      return AV_CODEC_ID_SRT;
        case R_CODEC_ID_MICRODVD:                 return AV_CODEC_ID_MICRODVD;
        case R_CODEC_ID_EIA_608:                  return AV_CODEC_ID_EIA_608;
        case R_CODEC_ID_JACOSUB:                  return AV_CODEC_ID_JACOSUB;
        case R_CODEC_ID_SAMI:                     return AV_CODEC_ID_SAMI;
        case R_CODEC_ID_REALTEXT:                 return AV_CODEC_ID_REALTEXT;
        case R_CODEC_ID_SUBVIEWER1:               return AV_CODEC_ID_SUBVIEWER1;
        case R_CODEC_ID_SUBVIEWER:                return AV_CODEC_ID_SUBVIEWER;
        case R_CODEC_ID_SUBRIP:                   return AV_CODEC_ID_SUBRIP;
        case R_CODEC_ID_WEBVTT:                   return AV_CODEC_ID_WEBVTT;
        case R_CODEC_ID_MPL2:                     return AV_CODEC_ID_MPL2;
        case R_CODEC_ID_VPLAYER:                  return AV_CODEC_ID_VPLAYER;
        case R_CODEC_ID_PJS:                      return AV_CODEC_ID_PJS;
        case R_CODEC_ID_ASS:                      return AV_CODEC_ID_ASS;
            
            /* other specific kind of case media_base::CODECs (generally used for attachments) */
        case R_CODEC_ID_TTF:                      return AV_CODEC_ID_TTF;
        case R_CODEC_ID_BINTEXT:                  return AV_CODEC_ID_BINTEXT;
        case R_CODEC_ID_XBIN:                     return AV_CODEC_ID_XBIN;
        case R_CODEC_ID_IDF:                      return AV_CODEC_ID_IDF;
        case R_CODEC_ID_OTF:                      return AV_CODEC_ID_OTF;
        case R_CODEC_ID_SMPTE_KLV:                return AV_CODEC_ID_SMPTE_KLV;
        case R_CODEC_ID_DVD_NAV:                  return AV_CODEC_ID_DVD_NAV;
            
            
        case R_CODEC_ID_PROBE:                    return AV_CODEC_ID_PROBE;
        case R_CODEC_ID_MPEG2TS:                  return AV_CODEC_ID_MPEG2TS;
        case R_CODEC_ID_MPEG4SYSTEMS:             return AV_CODEC_ID_MPEG4SYSTEMS;
        case R_CODEC_ID_FFMETADATA:               return AV_CODEC_ID_FFMETADATA;
        default:                                   return AV_CODEC_ID_NONE;
    }
}

media_base::ResuablePixelFormat FFMpegPixelFormatToMediaPixelFormat(enum AVPixelFormat ffPixelFormat)
{
    switch (ffPixelFormat)
    {
        case AV_PIX_FMT_YUV420P:               return R_PIX_FMT_YUV420P;
        case AV_PIX_FMT_YUYV422:               return R_PIX_FMT_YUYV422;
        case AV_PIX_FMT_RGB24:                 return R_PIX_FMT_RGB24;
        case AV_PIX_FMT_BGR24:                 return R_PIX_FMT_BGR24;
        case AV_PIX_FMT_YUV422P:               return R_PIX_FMT_YUV422P;
        case AV_PIX_FMT_YUV444P:               return R_PIX_FMT_YUV444P;
        case AV_PIX_FMT_YUV410P:               return R_PIX_FMT_YUV410P;
        case AV_PIX_FMT_YUV411P:               return R_PIX_FMT_YUV411P;
        case AV_PIX_FMT_GRAY8:                 return R_PIX_FMT_GRAY8;
        case AV_PIX_FMT_MONOWHITE:             return R_PIX_FMT_MONOWHITE;
        case AV_PIX_FMT_MONOBLACK:             return R_PIX_FMT_MONOBLACK;
        case AV_PIX_FMT_PAL8:                  return R_PIX_FMT_PAL8;
        case AV_PIX_FMT_YUVJ420P:              return R_PIX_FMT_YUVJ420P;
        case AV_PIX_FMT_YUVJ422P:              return R_PIX_FMT_YUVJ422P;
        case AV_PIX_FMT_YUVJ444P:              return R_PIX_FMT_YUVJ444P;
        case AV_PIX_FMT_BGR8:                  return R_PIX_FMT_BGR8;
        case AV_PIX_FMT_BGR4:                  return R_PIX_FMT_BGR4;
        case AV_PIX_FMT_BGR4_BYTE:             return R_PIX_FMT_BGR4_BYTE;
        case AV_PIX_FMT_RGB8:                  return R_PIX_FMT_RGB8;
        case AV_PIX_FMT_RGB4:                  return R_PIX_FMT_RGB4;
        case AV_PIX_FMT_RGB4_BYTE:             return R_PIX_FMT_RGB4_BYTE;
        case AV_PIX_FMT_NV12:                  return R_PIX_FMT_NV12;
        case AV_PIX_FMT_NV21:                  return R_PIX_FMT_NV21;
        case AV_PIX_FMT_ARGB:                  return R_PIX_FMT_ARGB;
        case AV_PIX_FMT_RGBA:                  return R_PIX_FMT_RGBA;
        case AV_PIX_FMT_ABGR:                  return R_PIX_FMT_ABGR;
        case AV_PIX_FMT_BGRA:                  return R_PIX_FMT_BGRA;
        case AV_PIX_FMT_GRAY16BE:              return R_PIX_FMT_GRAY16BE;
        case AV_PIX_FMT_GRAY16LE:              return R_PIX_FMT_GRAY16LE;
        case AV_PIX_FMT_YUV440P:               return R_PIX_FMT_YUV440P;
        case AV_PIX_FMT_YUVJ440P:              return R_PIX_FMT_YUVJ440P;
        case AV_PIX_FMT_YUVA420P:              return R_PIX_FMT_YUVA420P;
        case AV_PIX_FMT_RGB48BE:               return R_PIX_FMT_RGB48BE;
        case AV_PIX_FMT_RGB48LE:               return R_PIX_FMT_RGB48LE;
        case AV_PIX_FMT_RGB565BE:              return R_PIX_FMT_RGB565BE;
        case AV_PIX_FMT_RGB565LE:              return R_PIX_FMT_RGB565LE;
        case AV_PIX_FMT_RGB555BE:              return R_PIX_FMT_RGB555BE;
        case AV_PIX_FMT_RGB555LE:              return R_PIX_FMT_RGB555LE;
        case AV_PIX_FMT_BGR565BE:              return R_PIX_FMT_BGR565BE;
        case AV_PIX_FMT_BGR565LE:              return R_PIX_FMT_BGR565LE;
        case AV_PIX_FMT_BGR555BE:              return R_PIX_FMT_BGR555BE;
        case AV_PIX_FMT_BGR555LE:              return R_PIX_FMT_BGR555LE;
        case AV_PIX_FMT_VAAPI_MOCO:            return R_PIX_FMT_VAAPI_MOCO;
        case AV_PIX_FMT_VAAPI_IDCT:            return R_PIX_FMT_VAAPI_IDCT;
        case AV_PIX_FMT_VAAPI_VLD:             return R_PIX_FMT_VAAPI_VLD;
        case AV_PIX_FMT_RGB444LE:              return R_PIX_FMT_RGB444LE;
        case AV_PIX_FMT_RGB444BE:              return R_PIX_FMT_RGB444BE;
        case AV_PIX_FMT_BGR444LE:              return R_PIX_FMT_BGR444LE;
        case AV_PIX_FMT_BGR444BE:              return R_PIX_FMT_BGR444BE;
        case AV_PIX_FMT_GRAY8A:                return R_PIX_FMT_GRAY8A;
        case AV_PIX_FMT_BGR48BE:               return R_PIX_FMT_BGR48BE;
        case AV_PIX_FMT_BGR48LE:               return R_PIX_FMT_BGR48LE;
        case AV_PIX_FMT_YUV420P9BE:            return R_PIX_FMT_YUV420P9BE;
        case AV_PIX_FMT_YUV420P9LE:            return R_PIX_FMT_YUV420P9LE;
        case AV_PIX_FMT_YUV420P10BE:           return R_PIX_FMT_YUV420P10BE;
        case AV_PIX_FMT_YUV420P10LE:           return R_PIX_FMT_YUV420P10LE;
        case AV_PIX_FMT_YUV422P10BE:           return R_PIX_FMT_YUV422P10BE;
        case AV_PIX_FMT_YUV422P10LE:           return R_PIX_FMT_YUV422P10LE;
        case AV_PIX_FMT_YUV444P9BE:            return R_PIX_FMT_YUV444P9BE;
        case AV_PIX_FMT_YUV444P9LE:            return R_PIX_FMT_YUV444P9LE;
        case AV_PIX_FMT_YUV444P10BE:           return R_PIX_FMT_YUV444P10BE;
        case AV_PIX_FMT_YUV444P10LE:           return R_PIX_FMT_YUV444P10LE;
        case AV_PIX_FMT_YUV422P9BE:            return R_PIX_FMT_YUV422P9BE;
        case AV_PIX_FMT_YUV422P9LE:            return R_PIX_FMT_YUV422P9LE;
        case AV_PIX_FMT_GBRP:                  return R_PIX_FMT_GBRP;
        case AV_PIX_FMT_GBRP9BE:               return R_PIX_FMT_GBRP9BE;
        case AV_PIX_FMT_GBRP9LE:               return R_PIX_FMT_GBRP9LE;
        case AV_PIX_FMT_GBRP10BE:              return R_PIX_FMT_GBRP10BE;
        case AV_PIX_FMT_GBRP10LE:              return R_PIX_FMT_GBRP10LE;
        case AV_PIX_FMT_GBRP16BE:              return R_PIX_FMT_GBRP16BE;
        case AV_PIX_FMT_GBRP16LE:              return R_PIX_FMT_GBRP16LE;
        case AV_PIX_FMT_RGBA64BE:              return R_PIX_FMT_RGBA64BE;
        case AV_PIX_FMT_RGBA64LE:              return R_PIX_FMT_RGBA64LE;
        case AV_PIX_FMT_BGRA64BE:              return R_PIX_FMT_BGRA64BE;
        case AV_PIX_FMT_BGRA64LE:              return R_PIX_FMT_BGRA64LE;
        case AV_PIX_FMT_0RGB:                  return R_PIX_FMT_0RGB;
        case AV_PIX_FMT_RGB0:                  return R_PIX_FMT_RGB0;
        case AV_PIX_FMT_0BGR:                  return R_PIX_FMT_0BGR;
        case AV_PIX_FMT_BGR0:                  return R_PIX_FMT_BGR0;
        default:                                return R_PIX_FMT_NONE;
    }
}

media_base::ResuableSampleFormat FFMpegSampleFormatToMediaSampleFormat(enum AVSampleFormat sampleFormat)
{
    switch(sampleFormat)
    {
        case AV_SAMPLE_FMT_U8:
            return R_SAMPLE_FMT_U8;
            break;
        case AV_SAMPLE_FMT_U8P:
            return R_SAMPLE_FMT_U8P;
            break;
        case AV_SAMPLE_FMT_S16:
            return R_SAMPLE_FMT_S16;
            break;
        case AV_SAMPLE_FMT_S16P:
            return R_SAMPLE_FMT_S16P;
            break;
        case AV_SAMPLE_FMT_S32:
            return R_SAMPLE_FMT_S32;
            break;
        case AV_SAMPLE_FMT_S32P:
            return R_SAMPLE_FMT_S32P;
        case AV_SAMPLE_FMT_FLT:
            return R_SAMPLE_FMT_FLT;
            break;
        case AV_SAMPLE_FMT_FLTP:
            return R_SAMPLE_FMT_FLTP;
            break;
        case AV_SAMPLE_FMT_DBL:
            return R_SAMPLE_FMT_DBL;
            break;
        case AV_SAMPLE_FMT_DBLP:
            return R_SAMPLE_FMT_DBLP;
            break;
        default:
            return R_SAMPLE_FMT_NONE;
            break;
    }
}

enum AVSampleFormat MediaSampleFormatToFFMpegSampleFormat(media_base::ResuableSampleFormat sampleFormat)
{
    switch(sampleFormat)
    {
        case R_SAMPLE_FMT_U8:
            return AV_SAMPLE_FMT_U8;
            break;
        case R_SAMPLE_FMT_U8P:
            return AV_SAMPLE_FMT_U8P;
            break;
        case R_SAMPLE_FMT_S16:
            return AV_SAMPLE_FMT_S16;
            break;
        case R_SAMPLE_FMT_S16P:
            return AV_SAMPLE_FMT_S16P;
            break;
        case R_SAMPLE_FMT_S32:
            return AV_SAMPLE_FMT_S32;
            break;
        case R_SAMPLE_FMT_S32P:
            return AV_SAMPLE_FMT_S32P;
        case R_SAMPLE_FMT_FLT:
            return AV_SAMPLE_FMT_FLT;
            break;
        case R_SAMPLE_FMT_FLTP:
            return AV_SAMPLE_FMT_FLTP;
            break;
        case R_SAMPLE_FMT_DBL:
            return AV_SAMPLE_FMT_DBL;
            break;
        case R_SAMPLE_FMT_DBLP:
            return AV_SAMPLE_FMT_DBLP;
            break;
        default:
            return AV_SAMPLE_FMT_NONE;
            break;
    }
}

}   // namespace media_codec

