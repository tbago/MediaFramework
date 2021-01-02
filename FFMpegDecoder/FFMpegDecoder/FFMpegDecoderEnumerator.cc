//
//  FFMpegDecoderEnumerator.m
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "FFMpegDecoderEnumerator.h"
#include "FFMpegCommon.h"
#include "FFMpegDecoderImp.h"

extern "C" {
    #include "libavcodec/avcodec.h"
}

namespace media_decoder {

FFMpegDecoderEnumerator::FFMpegDecoderEnumerator()
{

}

FFMpegDecoderEnumerator::~FFMpegDecoderEnumerator()
{
    for (uint32_t i = 0; i < _codecInfoVector.size(); i++) {
        FFMpegCodecInfo *codecInfo = _codecInfoVector[i];
        delete codecInfo;
        _codecInfoVector[i] = NULL;
    }
    _codecInfoVector.clear();
}

void FFMpegDecoderEnumerator::InitDecoderArray()
{
    avcodec_register_all();
    AVCodec *pAVCodec = NULL;
    do {
        pAVCodec = av_codec_next(pAVCodec);
        if (pAVCodec != NULL && av_codec_is_decoder(pAVCodec) != 0)
        {
            enum AVMediaType mediaType = avcodec_get_type(pAVCodec->id);
            FFMpegDecoderType decoderType = FFMpegUnknownDecoder;
            switch (mediaType)
            {
                case AVMEDIA_TYPE_VIDEO:
                    decoderType = FFMpegVideoDecoder;
                    break;
                case AVMEDIA_TYPE_AUDIO:
                    decoderType = FFMpegAudioDecoder;
                    break;
                case AVMEDIA_TYPE_SUBTITLE:
                    decoderType = FFMpegSubtitleDecoder;
                    break;
                default:
                    break;
            }
            if (decoderType == FFMpegUnknownDecoder) {
                continue;
            }

            FFMpegCodecInfo *newCodecInfo = new FFMpegCodecInfo();
            newCodecInfo->type    = decoderType;
            newCodecInfo->codecID = FFMpegCodecIDToMeidaCodecID(pAVCodec->id);
            newCodecInfo->name    = pAVCodec->name;
            newCodecInfo->score   = 100;

            _codecInfoVector.push_back(newCodecInfo);
        }
    } while(pAVCodec != NULL);
}

FFMpegDecoder *FFMpegDecoderEnumerator::CreateFFMpegDecoderByCodecId(media_base::ResuableCodecID codecID)
{
    for (FFMpegCodecInfo * codecInfo : _codecInfoVector)
    {
        if (codecInfo->codecID == codecID) {
            FFMpegDecoder *ffmpegDecoder = new FFMpegDecoderImp(codecInfo);
            return ffmpegDecoder;
        }
    }
    return NULL;
}

}   // namespace media_demuxer

