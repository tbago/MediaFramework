//
//  FFMpegDemuxerImp.m
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "FFMpegDemuxerImp.h"
#include "FFMpegCommon.h"

#define FMT_PROB_DATA_SIZE 1*1024*1024 //1M

void ffmpeg_log(void* avcl, int level, const char *fmt, va_list vl);

FFMpegDemuxer *createFFMpegDemuxer() {
    FFMpegDemuxer *demuxer = [[FFMpegDemuxerImp alloc] init];
    return demuxer;
}

@interface FFMpegDemuxerImp()
{
    AVFormatContext* _formatContext;
}
@property (strong, nonatomic) MovieInfo     *movieInfo;     ///< current file movie info

@end
@implementation FFMpegDemuxerImp

- (instancetype)init {
    self = [super init];
    if (self) {
        _formatContext = NULL;
        [self innerInitFFMpeg];
    }
    return self;
}

- (BOOL)openFileByPath:(NSString *)filePath {
    
    av_log_set_callback(ffmpeg_log);
    
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

    int ret = avformat_open_input(&_formatContext, [filePath UTF8String], format, NULL);
    if (ret != 0) {
        NSLog(@"Open input failed");
        return NO;
    }
    
    avformat_find_stream_info(_formatContext, NULL);
    
    [self buildMovieInfo:filePath];
    return YES;
}

#pragma mark - private method

- (void)innerInitFFMpeg {
    av_register_all();
    avformat_network_init();
}

- (void)buildMovieInfo:(NSString *) filePath {
    self.movieInfo.name = [[filePath lastPathComponent] stringByDeletingPathExtension];
    self.movieInfo.format = [NSString stringWithUTF8String:_formatContext->iformat->name];
    
    ///< store movie meta data
    if (_formatContext->metadata != NULL) {
        AVDictionaryEntry *t = NULL;
        t = av_dict_get(_formatContext->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
        while (t != NULL)
        {
            if (t->key != NULL && t->value != NULL)
            {
                NSString *keyString = [NSString stringWithUTF8String:t->key];
                NSString *valueString = [NSString stringWithUTF8String:t->value];
                [self.movieInfo addMetaDataToStreamInfo:keyString value:valueString];
            }
            t = av_dict_get(_formatContext->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
        }
    }
    
    ///< build stream info
    for (uint32_t i = 0; i < _formatContext->nb_streams; i++) {
        AVStream* avStream = _formatContext->streams[i];
        StreamInfo *streamInfo = [[StreamInfo alloc] init];
        streamInfo.streamId = avStream->id;
        
        AVDictionaryEntry *tag = av_dict_get(avStream->metadata, "language", NULL, 0);
        if (tag != NULL && tag->value != NULL) {
            streamInfo.language = [NSString stringWithUTF8String:tag->value];
        }
        else {
            streamInfo.language = @"eng";
        }
        
        if (avStream->duration != AV_NOPTS_VALUE) {
            int64_t duration = av_rescale_q(avStream->duration, avStream->time_base, gGloabalTimeBase);
            if (duration > 0) {
                avStream->duration = duration/1000;
            }
        }
        
//        AVCodecContext *pCodecContext = _formatContext->streams[i]->codec;
        AVCodecParameters *codecParam = _formatContext->streams[i]->codecpar;
        if (codecParam == NULL) {
            streamInfo.streamType = UnknownStream;
            streamInfo.codecID = R_CODEC_ID_NONE;
            [self.movieInfo addStreamInfoToMovieInfo:streamInfo];
            continue;
        }
        
        else if (codecParam->codec_type == AVMEDIA_TYPE_VIDEO) {
            streamInfo.streamType = VideoStream;
            streamInfo.width      = codecParam->width;
            streamInfo.height     = codecParam->height;
            
            streamInfo.
        }
        else if (codecParam->codec_type == AVMEDIA_TYPE_AUDIO) {
            streamInfo.streamType = AudioStream;
        }
        else if (codecParam->codec_type == AVMEDIA_TYPE_SUBTITLE) {
            streamInfo.streamType == SubtitleStream;
        }
        else {
            streamInfo.streamType = UnknownStream;
        }
        streamInfo.bitrate = codecParam->bit_rate;
        [self.movieInfo addStreamInfoToMovieInfo:streamInfo];
    }
}

#pragma mark - get & set

- (MovieInfo *)movieInfo {
    if (_movieInfo == nil) {
        _movieInfo = [[MovieInfo alloc] init];
    }
    return _movieInfo;
}
@end

//////////////////////////////////////////////////////////////////////////
//ffmepg log call back
void ffmpeg_log(void* avcl, int level, const char *fmt, va_list vl)
{
    char buffer[256];
    if (level == AV_LOG_WARNING) {
        vsnprintf(buffer, 256, fmt, vl);
        NSLog(@"ffmpeg demuxer warning:%s", buffer);
    }
    else if (level == AV_LOG_ERROR) {
        vsnprintf(buffer, 256, fmt, vl);
        NSLog(@"ffmpeg demuxer error:%s", buffer);
    }
    else if (level == AV_LOG_FATAL) {
        vsnprintf(buffer, 256, fmt, vl);
        NSLog(@"ffmpeg demuxer fatal:%s", buffer);
    }
    else if (level == AV_LOG_TRACE) {
        vsnprintf(buffer, 256, fmt, vl);
        NSLog(@"ffmpeg demuxer trace:%s", buffer);
    }
}
