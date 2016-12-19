//
//  StreamInfo.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MediaConstant.h"
#import "ResuableCodecID.h"
#import "ResuablePixelFormat.h"
#import "ResuableSampleFormat.h"
/**
 *  media stream info
 */
@interface StreamInfo : NSObject

@property (nonatomic) StreamType            streamType;
@property (nonatomic) int32_t               streamId;
@property (nonatomic, copy) NSString        *streamName;
@property (nonatomic) ResuableCodecID       codecID;
@property (nonatomic, copy) NSString        *codecName;
@property (nonatomic, copy) NSString        *language;
@property (nonatomic) int32_t               bitrate;
@property (nonatomic) int64_t               duration;   ///< stream duration in ms, -1 is unkonwn
///< video param
@property (nonatomic) int32_t               width;
@property (nonatomic) int32_t               height;
@property (nonatomic) int64_t               framerate;
@property (nonatomic) ResuablePixelFormat   pixfmt;
@property (nonatomic) int32_t               pixelAspectRatio;
///< audio param
@property (nonatomic) ResuableSampleFormat  sampleFormat;
@property (nonatomic) int32_t               samplerate;
@property (nonatomic) int32_t               channels;
@end
