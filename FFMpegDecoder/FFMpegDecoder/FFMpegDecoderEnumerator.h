//
//  FFMpegDecoderEnumerator.h
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FFMpegDecoder;

/**
 *  Enum all ffmpeg decoders
 */
@interface FFMpegDecoderEnumerator : NSObject
/**
 *  init all decoder info array
 */
- (void)initDecoderArray;

/**
 *  Create ffmpeg decoder by codec info array index
 *
 *  @param index codec info array index
 *
 *  @return ffmpeg decoder
 */
- (FFMpegDecoder *)CreateFFMpegDecoderByIndex:(uint32_t) index;

@property (strong, nonatomic, readonly) NSArray     *codecInfoArray;
@end
