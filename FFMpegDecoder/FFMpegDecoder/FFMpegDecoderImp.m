//
//  FFMpegDecoderImp.m
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "FFMpegDecoderImp.h"
#import "FFMpegDecoder.h"
#import "FFMpegCommon.h"

@interface FFMpegDecoder()
{
    AVCodec             * _ffAVCodec;
    AVCodecContext      _ffAVCodecContext;
}
@property (nonatomic, copy) NSData          *innerExtraData;
@property (nonatomic, strong) FFMpegCodecInfo *codecInfo;
@end

@implementation FFMpegDecoder

///< default init method will return nil
- (instancetype)init {
    return nil;
}

- (instancetype)initWithCodecInfo:(FFMpegCodecInfo *) codecInfo {
    self = [super init];
    if (self) {
        self.codecInfo = codecInfo;
    }
    return self;
}

static __inline bool sup_threads_dec_slice(int x)
{
    return x==AV_CODEC_ID_MPEG1VIDEO || x==AV_CODEC_ID_MPEG2VIDEO || x==AV_CODEC_ID_FFV1 || x==AV_CODEC_ID_DVVIDEO;
}

static __inline bool sup_threads_dec_frame(int x)
{
    return (x==AV_CODEC_ID_H264) || (x == AV_CODEC_ID_H265);
}

- (BOOL)openCodec:(AVCodecParam *) codecParam {
    if (codecParam == NULL) {
        return NO;
    }
    
    enum AVCodecID codecId = MediaCodecIDToFFMpegCodecID(self.codecInfo.codecID);
    _ffAVCodec = avcodec_find_decoder(codecId);
    if (_ffAVCodec == NULL) {
        return NO;
    }
    
    avcodec_get_context_defaults3(&_ffAVCodecContext, _ffAVCodec);
    self.innerExtraData = codecParam.extraData;
    if (self.innerExtraData.length > 0) {
        _ffAVCodecContext.extradata = (uint8_t *)[self.innerExtraData bytes];
        _ffAVCodecContext.extradata_size = (int)self.innerExtraData.length;
    }
    else {
        _ffAVCodecContext.extradata = NULL;
        _ffAVCodecContext.extradata_size = 0;
    }
    
    if (self.codecInfo.type == FFMpegVideoDecoder)
    {
        _ffAVCodecContext.width                 = codecParam.width;
        _ffAVCodecContext.height                = codecParam.height;
        _ffAVCodecContext.bits_per_coded_sample = codecParam.bitsPerCodedSample;
        
        uint32_t    numThreads = 1;
        int         threadType = 0;
        if (codecParam.numThreads > 0) {
            numThreads = codecParam.numThreads;
        }
        
        if (numThreads > 1 && sup_threads_dec_frame(codecId)) {
            threadType = FF_THREAD_FRAME;
        } else if (numThreads > 1 && sup_threads_dec_slice(codecId)) {
            threadType = FF_THREAD_SLICE;
        }
        
        if (numThreads > 1 && threadType != 0) {
            numThreads = numThreads;
        } else {
            numThreads = 1;
        }
        
        _ffAVCodecContext.thread_type = threadType;
        _ffAVCodecContext.thread_count = numThreads;
        
        if (_ffAVCodec->id == AV_CODEC_ID_H264) {
            // If we do not set this, first B-frames before the IDR pictures are dropped.
            _ffAVCodecContext.has_b_frames = 1;
        }
        _ffAVCodecContext.codec_tag = codecParam.codecTag;
        
        if (codecId == AV_CODEC_ID_MJPEG) {
            _ffAVCodecContext.flags |= CODEC_FLAG_TRUNCATED;
        }
    }
    else if (self.codecInfo.type == FFMpegAudioDecoder) {
        return NO;
    }
    
    int ret = avcodec_open2(&_ffAVCodecContext, _ffAVCodec, NULL);
    if (ret < 0) {
        return NO;
    }
    return YES;
}

@end

@implementation FFMpegCodecInfo : NSObject

@end

@implementation AVCodecParam

@end
