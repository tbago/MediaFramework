//
//  FFMpegDecoderImp.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef FFMPEG_DECODER_FFMPEG_DECODER_IMP_H_
#define FFMPEG_DECODER_FFMPEG_DECODER_IMP_H_

#include "FFMpegDecoder.h"
#include "FFMpegCommon.h"

namespace media_decoder {

class FFMpegDecoderImp : public FFMpegDecoder
{
public:
    virtual bool OpenCodec(AVCodecParam * codecParam);
    virtual media_base::RawVideoFrame * DecodeVideoFrame(media_base::CompassedFrame * compassedFrame);
    virtual media_base::RawAudioFrame * DecodeAudioFrame(media_base::CompassedFrame * compassedFrame);
public:
    FFMpegDecoderImp(FFMpegCodecInfo * codecInfo);
private:
    media_base::RawVideoFrame * InnerDecodeVideoFrame(media_base::CompassedFrame *compassedFrame);
    media_base::RawAudioFrame * InnerDecodeAudioFrame(media_base::CompassedFrame *compassedFrame);
private:
    FFMpegCodecInfo         _codecInfo;
    AVCodec                *_avcodec;
    AVCodecContext          _avcodecContext;
    uint8_t                *_innerExtraData;
    int32_t                _innerExtraDataSize;
};

}   // namespace media_decoder
#endif // FFMPEG_DECODER_FFMPEG_DECODER_IMP_H_

