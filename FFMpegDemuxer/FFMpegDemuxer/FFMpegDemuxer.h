//
//  FFMpegDemuxer.h
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#include <Foundation/Foundation.h>
#import <MediaBase/MediaBase.h>

/**
 *  Demuxer media file by ffmpeg
 *  This is only interface object,all method are implement by subclass
 *  Please call 'createFFMpegDemuxer' function to create instance.
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

- (CompassedFrame *)readFrame;

- (BOOL)seekToPosition:(int64_t) position
          realPosition:(int64_t *) realPosition;

- (int64_t)getCurrentTime;

- (int64_t)getCurrentPosition;
/**
 *  Whether read end of the file
 *
 *  @return
 */
- (BOOL)eof;

- (void)closeInputFile;
@end

/**
 *  Create Demuxer instance
 *
 *  @return demuxer instance
 */
FFMpegDemuxer *createFFMpegDemuxer();

