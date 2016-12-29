//
//  FFMpegDecoder.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <FFMpegDecoder/FFMpegDecoderEnumerator.h>

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

