//
//  FFMpegCommon.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/19.
//  Copyright © 2021 tbago. All rights reserved.
//

#include <MediaBase/ResuableCodecID.h>
#include <MediaBase/ResuablePixelformat.h>
#include <MediaBase/ResuableSampleFormat.h>

extern "C" {
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
}

namespace media_decoder {

extern const AVRational gGloabalTimeBase;

/**
 *  Convert ffmpeg codec id to global resuable codec id
 *
 *  @param ffCodecID ffmpeg codec id
 *
 *  @return global codec id
 */
media_base::ResuableCodecID FFMpegCodecIDToMeidaCodecID(enum AVCodecID ffCodecID);

enum AVCodecID MediaCodecIDToFFMpegCodecID(media_base::ResuableCodecID resuableCodecID);

/**
 *  Convert ffmpeg pixel format to global resuable pixel format
 *
 *  @param ffPixelFormat ffmpeg pixel format
 *
 *  @return global pixel format
 */
media_base::ResuablePixelFormat FFMpegPixelFormatToMediaPixelFormat(enum AVPixelFormat ffPixelFormat);

/**
 *  Convert ffmpeg sample format to  resuable sample format
 *
 *  @param sampleFormat ffmpeg sample format
 *
 *  @return resuable sample format
 */
media_base::ResuableSampleFormat FFMpegSampleFormatToMediaSampleFormat(enum AVSampleFormat sampleFormat);

/**
*  Convert resuable sample format to ffmpeg sample format
*
*  @param sampleFormat resuable sample format
*
*  @return ffmpeg sample format
*/
enum AVSampleFormat MediaSampleFormatToFFMpegSampleFormat(media_base::ResuableSampleFormat sampleFormat);

}   // namespace media_decoder

