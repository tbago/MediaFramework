//
//  FFMpegDemuxer.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#include <Foundation/Foundation.h>
#import "MovieInfo.h"

/**
 *  Demuxer media file by ffmpeg
 */
@interface FFMpegDemuxer : NSObject

/**
 *  Open file by path
 *
 *  @param filePath input file path
 *
 *  @return success or failed
 */
- (BOOL)openFileByPath:(NSString *) filePath;

/**
 *  Get file movie count
 *
 *  @return movie count
 */
- (uint32_t)getMovieCount;

- (MovieInfo *)getMovieInfoByIndex:(uint32_t) index;

- (
@end

/**
 *  Create Demuxer instance
 *
 *  @return demuxer instance
 */
FFMpegDemuxer *createFFMpegDemuxer();

