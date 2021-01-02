//
//  FFMpegDecoderEnumerator.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef FFMPEG_DECOER_FFMPEG_DECODER_ENUMERATOR_H_
#define FFMPEG_DECOER_FFMPEG_DECODER_ENUMERATOR_H_

#include <MediaBase/ResuableCodecID.h>
#include <string>
#include <vector>

namespace media_decoder {

class FFMpegDecoder;

typedef enum {
    FFMpegUnknownDecoder,
    FFMpegVideoDecoder,
    FFMpegAudioDecoder,
    FFMpegSubtitleDecoder,
} FFMpegDecoderType;

struct FFMpegCodecInfo
{
    FFMpegDecoderType                type;
    media_base::ResuableCodecID       codecID;
    std::string                     name;
    uint32_t                        score;
};

/**
 *  Enum all ffmpeg decoders
 */
class FFMpegDecoderEnumerator
{
public:
    /**
     *  init all decoder info array
     */
    void InitDecoderArray();

    /**
     *  Create ffmpeg decoder by codec info array index
     *
     *  @param index codec info array index
     *
     *  @return ffmpeg decoder
     */
    FFMpegDecoder * CreateFFMpegDecoderByCodecId(media_base::ResuableCodecID codecID);
public:
    FFMpegDecoderEnumerator();
    ~FFMpegDecoderEnumerator();
    FFMpegDecoderEnumerator(const FFMpegDecoderEnumerator &decoderEnumerator) = delete;
    FFMpegDecoderEnumerator & operator=(const FFMpegDecoderEnumerator &decoderEnumerator) = delete;
private:
    std::vector<FFMpegCodecInfo *>     _codecInfoVector;
};

}   // namespace media_decoder
#endif  // FFMPEG_DECOER_FFMPEG_DECODER_ENUMERATOR_H_


