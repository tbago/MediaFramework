//
//  FFMpegDemuxerImp.m
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "FFMpegDemuxerImp.h"
#include "avformat.h"

#define FMT_PROB_DATA_SIZE 1*1024*1024 //1M

FFMpegDemuxer *createFFMpegDemuxer() {
    FFMpegDemuxer *demuxer = [[FFMpegDemuxerImp alloc] init];
    return demuxer;
}

@implementation FFMpegDemuxerImp

- (instancetype)init {
    self = [super init];
    if (self) {
        [self innerInitFFMpeg];
    }
    return self;
}

- (BOOL)openFileByPath:(NSString *)filePath {
    AVInputFormat* format = NULL;
    
    if ([filePath hasPrefix:@"rtsp://"]) {
        format = av_find_input_format("rtsp");
    }
    
    ///< check file format by probe data
    if (format == NULL)
    {
        AVProbeData probeData;
        memset(&probeData, 0, sizeof(probeData));
        uint32_t bufferSize = FMT_PROB_DATA_SIZE+AVPROBE_PADDING_SIZE;

        NSFileHandle          *readFileHandle = NULL;
        readFileHandle = [NSFileHandle fileHandleForReadingAtPath:filePath];
        if (readFileHandle == NULL) {
            NSLog(@"cannot create file handle by file:%@", filePath);
            return NO;
        }
        NSData *fileData = [readFileHandle readDataOfLength:bufferSize];
        if (fileData.length == 0) {
            NSLog(@"file or stream is not have enough data");
            return NO;
        }
        
        probeData.buf      = (uint8_t *)fileData.bytes;
        probeData.buf_size = (uint32_t)fileData.length;
        probeData.filename = [[filePath lastPathComponent] UTF8String];
        format = av_probe_input_format(&probeData, 1);
    }

    if (format == NULL) {
        NSString *fileExt = [filePath pathExtension];
        if ([fileExt isEqualToString:@"mod"] || [fileExt isEqualToString:@"vob"]) {
            format = av_find_input_format("mpeg");
        }
        else if ([fileExt isEqualToString:@"mp3"]) {
            format = av_find_input_format("mp3");
        }
        else if ([fileExt isEqualToString:@"tod"]
                 ||[fileExt isEqualToString:@"mts"]
                 || [fileExt isEqualToString:@"m2ts"]
                 || [fileExt isEqualToString:@"tp"]
                 || [fileExt isEqualToString:@"ts"]
                 || [fileExt isEqualToString:@"trp"]
                 || [fileExt isEqualToString:@"m2t"])
        {
            format = av_find_input_format("mpegts");
        }
        else if([fileExt isEqualToString:@"png"]
                || [fileExt isEqualToString:@"tiff"]
                || [fileExt isEqualToString:@"tif"]
                || [fileExt isEqualToString:@"ppm"])
        {
            format = av_find_input_format("image2");
        }
        if ([fileExt isEqualToString:@"mpeg"]
            || [fileExt isEqualToString:@"mpg"]
            || [fileExt isEqualToString:@"evo"]
            || [fileExt isEqualToString:@"vdr"])
        {
            format = av_find_input_format("mpeg");
        }
        else if ([fileExt isEqualToString:@"264"]
                 || [fileExt isEqualToString:@"h264"]) {
            format = av_find_input_format("h264");
        }
        else if ([fileExt isEqualToString:@"mxf"]
                 || [fileExt isEqualToString:@"MXF"]) {
            format = av_find_input_format("mxf");
        }
    }
    
    if (format == NULL) {
        NSLog(@"Cannot find input stream format");
        return NO;
    }
    
    AVFormatContext* formatContext = NULL;
    int ret = avformat_open_input(&formatContext, [filePath UTF8String], formatContext, NULL);
    if (!ret) {
        NSLog(@"Open input failed");
        return NO;
    }
    
    return YES;
}

#pragma mark - private method

- (void)innerInitFFMpeg {
    av_register_all();
    avformat_network_init();
}
@end
