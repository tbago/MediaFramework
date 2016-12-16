//
//  MediaInfo.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "StreamInfo.h"

@interface MediaInfo : NSObject

@property (nonatomic) int32_t                       identify;
@property (nonatomic, copy) NSString                *name;
@property (nonatomic, copy) NSString                *format;            ///< media format
@property (strong, nonatomic) NSArray<StreamInfo *> *streamArray;       ///< stream info array
@end
