//
//  FFMpegDecoderImp.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <FFMpegDecoder/FFMpegDecoder.h>
#import <MediaBase/ResuableCodecID.h>

typedef NS_ENUM(NSInteger, FFMpegDecoderType) {
    FFMpegUnknownDecoder,
    FFmpegVideoDecoder,
    FFMpegAudioDecoder,
    FFMpegSubtitleDecoder,
};

@interface FFMpegCodecInfo : NSObject

@property (nonatomic) FFMpegDecoderType     type;
@property (nonatomic) ResuableCodecID       codecID;
@property (nonatomic, copy) NSString        *name;
@property (nonatomic) uint32_t              score;

@end

@interface FFMpegDecoderImp : FFMpegDecoder

@end
