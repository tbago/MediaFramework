//
//  FFMpegDecoder.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef FFMPEG_DECODER_FFMPEG_DECODER_H_
#define FFMPEG_DECODER_FFMPEG_DECODER_H_

#include <FFMpegDecoder/FFMpegDecoderEnumerator.h>
#include <MediaBase/RawVideoFrame.h>
#include <MediaBase/CompassedFrame.h>

namespace media_decoder {

class FFMpegCodecInfo;

struct AVCodecParam
{
    uint32_t      numThreads;
    uint32_t      width;
    uint32_t      height;
    uint32_t      channels;
    uint32_t      sampleRate;
    uint8_t       *extraData;
    uint32_t      extraDataSize;
    /**
     * fourcc (LSB first, so "ABCD" -> ('D'<<24) + ('C'<<16) + ('B'<<8) + 'A').
     * This is used to work around some encoder bugs.
     * A demuxer should set this to what is stored in the field used to identify the codec.
     * If there are multiple such fields in a container then the demuxer should choose the one
     * which maximizes the information about the used codec.
     * If the codec tag field in a container is larger than 32 bits then the demuxer should
     * remap the longer ID to 32 bits with a table or other structure. Alternatively a new
     * extra_codec_tag + size could be added but for this a clear advantage must be demonstrated
     * first.
     * - encoding: Set by user, if not then the default based on codec_id will be used.
     * - decoding: Set by user, will be converted to uppercase by libavcodec during init.
     */
    uint32_t      codecTag;
    /**
     * bits per sample/pixel from the demuxer (needed for huffyuv).
     * - encoding: Set by libavcodec.
     * - decoding: Set by user.
     */
    int32_t       bitsPerCodedSample;
};

/**
 *  Decoder media packet by ffmpeg
 */
class FFMpegDecoder
{
public:
    virtual bool OpenCodec(AVCodecParam * codecParam) = 0;

    virtual media_base::RawVideoFrame * DecodeVideoFrame(media_base::CompassedFrame * compassedFrame) = 0;
};

/**
 *  Create Decoder instance
 *
 *  @return decoder instance
 */
FFMpegDecoder *createFFmpegDecoder();

}   // namespace media_decoder
#endif // FFMPEG_DECODER_FFMPEG_DECODER_H_

