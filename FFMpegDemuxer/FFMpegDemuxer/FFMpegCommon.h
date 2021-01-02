//
//  FFMpegCommon.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/19.
//  Copyright © 2016年 tbago. All rights reserved.
//

#include <MediaBase/ResuableCodecID.h>
#include <MediaBase/ResuablePixelformat.h>
#include <MediaBase/ResuableSampleFormat.h>

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

namespace media_demuxer {

extern const AVRational gGloabalTimeBase;

/**
 *  Convert ffmpeg codec id to global resuable codec id
 *
 *  @param ffCodecID ffmpeg codec id
 *
 *  @return global codec id
 */
media_base::ResuableCodecID FFMpegCodecIDToMeidaCodecID(enum AVCodecID ffCodecID);

/**
 *  Convert ffmpeg pixel format to global resuable pixel format
 *
 *  @param ffPixelFormat ffmpeg pixel format
 *
 *  @return global pixel format
 */
media_base::ResuablePixelFormat FFMpegPixelFormatToMediaPixelFormat(enum AVPixelFormat ffPixelFormat);

/**
 *  Convert ffmpeg sample format to global resuable sample format
 *
 *  @param sample_fmt ffmpeg sample format
 *
 *  @return global sample format
 */
media_base::ResuableSampleFormat FFMpegSampleFormatToMediaSampleFormat(enum AVSampleFormat sample_fmt);

}   //namespace media_demuxer

