//
//  FFMpegDemuxer.m
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "FFMpegDemuxer.h"
#import "FFMpegDemuxerImp.h"

@implementation FFMpegDemuxer

@end

FFMpegDemuxer *createFFMpegDemuxer() {
    FFMpegDemuxer *demuxer = [[FFMpegDemuxerImp alloc] init];
    return demuxer;
}
