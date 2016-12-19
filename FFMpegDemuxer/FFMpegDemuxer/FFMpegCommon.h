//
//  FFMpegCommon.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/19.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaBase/ResuableCodecID.h>
#import <MediaBase/ResuablePixfmt.h>

#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"

extern const AVRational gGloabalTimeBase;

ResuableCodecID FFMpegCodecIDToMeidaCodecID(enum AVCodecID ffCodecID);
ResuablePixelFormat FFMpegPixelFormatToMediaPixelFormat(enum AVPixelFormat ffPixelFormat);