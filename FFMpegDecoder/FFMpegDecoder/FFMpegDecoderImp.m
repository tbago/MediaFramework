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

- (RawVideoFrame *)decodeVideoFrame:(CompassedFrame *) compassedFrame {
    if (compassedFrame == NULL) {   ///< flush decoder
        if (_codecInfo.type == FFMpegVideoDecoder) {
            return [self innerDecodeVideo:NULL];
        }
        else if (_codecInfo.type == FFMpegAudioDecoder) {
            return NULL;
//            return DecodeAudio(NULL);
        }
    }
    if (_codecInfo.type == FFMpegVideoDecoder) {
        return [self innerDecodeVideo:compassedFrame];
    }
    
    return NULL;
}

- (RawVideoFrame *)innerDecodeVideo:(CompassedFrame *) compassedFrame {
    ///<ICompressedFrame to AVPacket
    uint32_t    size = 0;
    uint8_t*    pData = NULL;
    int64_t     dts = -1;
    int64_t     pts = -1;
    int         flags = 0;
    int64_t     pos = -1;
    
    if (compassedFrame != NULL)
    {
        size = (uint32_t)compassedFrame.frameData.length;
        if (size < 2) {
            NSLog(@"frame size too small");
            return NULL;
        }
        pData   = (uint8_t*)compassedFrame.frameData.bytes;
        dts     = compassedFrame.decompassTimeStamp;
        pts     = compassedFrame.presentTimeStamp;
        flags   = compassedFrame.keyFrame;
        pos     = compassedFrame.position;
        
    } else { //Flush decoder
        
    }
    AVPacket avpkt;
    memset(&avpkt, 0, sizeof(avpkt));
    avpkt.data  = pData;
    avpkt.size  = size;
    avpkt.dts   = dts;
    avpkt.pts   = pts;
    avpkt.flags = flags;
    avpkt.pos   = pos;
    
    AVFrame *decodedVideoFrame = av_frame_alloc();
    int ret = avcodec_send_packet(&_ffAVCodecContext, &avpkt);
    if (ret != 0) {
        NSLog(@"send packet failed");
        return NULL;
    }
    ret = avcodec_receive_frame(&_ffAVCodecContext, decodedVideoFrame);
    if (ret != 0) {
        if (ret == AVERROR(EAGAIN)) {
            NSLog(@"Buffer video frame");
            return NULL;
        }
        else {
            NSLog(@"cannot decoder video,%d", ret);
            return NULL;
        }
    }
    
    RawVideoFrame *pRawVideoFrame = [[RawVideoFrame alloc] initWithPixFormat:FFMpegPixelFormatToMediaPixelFormat(_ffAVCodecContext.pix_fmt)
                                                                       width:decodedVideoFrame->width
                                                                      height:decodedVideoFrame->height];
    
    for (uint32_t i = 0; i < AV_NUM_DATA_POINTERS; i++) {
        if (decodedVideoFrame->linesize[i] > 0) {
            [pRawVideoFrame pushFrameData:decodedVideoFrame->linesize[i]
                                frameByte:decodedVideoFrame->data[i]];
        }
        else {
            break;
        }
    }
    av_frame_free(&decodedVideoFrame);
    
    return pRawVideoFrame;
}

@end

@implementation FFMpegCodecInfo : NSObject

@end

@implementation AVCodecParam

@end
