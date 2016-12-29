//
//  RawVideoFrame.h
//  MediaBase
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ResuablePixelFormat.h"

/**
 *  Decoder readable video frame
 */
@interface RawVideoFrame : NSObject

@property (nonatomic) ResuablePixelFormat   pixelFormat;
@property (nonatomic) uint32_t              width;
@property (nonatomic) uint32_t              height;
@property (nonatomic) uint64_t              timeStamp;
@property (nonatomic) uint32_t              duration;

@end
