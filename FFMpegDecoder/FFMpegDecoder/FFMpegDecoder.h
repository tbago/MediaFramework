//
//  FFMpegDecoder.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <UIKit/UIKit.h>
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

/**
 *  Decoder media packet by ffmpeg
 *  This is only interface object,all method are implement by subclass
 *  Please call 'createFFMpegDecoder' function to create instance.
 */
@interface FFMpegDecoder : NSObject

@end

/**
 *  Create Decoder instance
 *
 *  @return decoder instance
 */
FFMpegDecoder *createFFmpegDecoder();

