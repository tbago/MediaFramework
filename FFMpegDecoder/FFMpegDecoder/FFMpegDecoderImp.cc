//
//  FFMpegDecoderImp.m
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "FFMpegDecoderImp.h"
#include "FFMpegDecoderEnumerator.h"

namespace media_decoder {

FFMpegDecoderImp::FFMpegDecoderImp(FFMpegCodecInfo * codecInfo) {
    _codecInfo = *codecInfo;
    _innerExtraData = NULL;
    _innerExtraDataSize = 0;
}

static __inline bool sup_threads_dec_slice(int x)
{
    return x==AV_CODEC_ID_MPEG1VIDEO || x==AV_CODEC_ID_MPEG2VIDEO || x==AV_CODEC_ID_FFV1 || x==AV_CODEC_ID_DVVIDEO;
}

static __inline bool sup_threads_dec_frame(int x)
{
    return (x==AV_CODEC_ID_H264) || (x == AV_CODEC_ID_H265);
}

bool FFMpegDecoderImp::OpenCodec(AVCodecParam * codecParam)
{
    if (codecParam == NULL) {
        return false;
    }
    
    enum AVCodecID codecId = MediaCodecIDToFFMpegCodecID(_codecInfo.codecID);
    _avcodec = avcodec_find_decoder(codecId);
    if (_avcodec == NULL) {
        return false;
    }
    
    avcodec_get_context_defaults3(&_avcodecContext, _avcodec);
    if (codecParam->extraDataSize > 0 && codecParam->extraData != NULL) {
        _innerExtraDataSize = codecParam->extraDataSize;
        _innerExtraData = (uint8_t *)malloc(_innerExtraDataSize);
        memcpy(_innerExtraData, codecParam->extraData, codecParam->extraDataSize);
    }

    if (_innerExtraDataSize > 0 &&  _innerExtraData != NULL) {
        _avcodecContext.extradata = _innerExtraData;
        _avcodecContext.extradata_size = _innerExtraDataSize;
    }
    else {
        _avcodecContext.extradata = NULL;
        _avcodecContext.extradata_size = 0;
    }

    if (_codecInfo.type == FFMpegVideoDecoder)
    {
        _avcodecContext.width                 = codecParam->width;
        _avcodecContext.height                = codecParam->height;
        _avcodecContext.bits_per_coded_sample   = codecParam->bitsPerCodedSample;

        uint32_t    numThreads = 1;
        int         threadType = 0;
        if (codecParam->numThreads > 0) {
            numThreads = codecParam->numThreads;
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

        _avcodecContext.thread_type = threadType;
        _avcodecContext.thread_count = numThreads;

        if (_avcodec->id == AV_CODEC_ID_H264) {
            // If we do not set this, first B-frames before the IDR pictures are dropped.
            _avcodecContext.has_b_frames = 1;
        }
        _avcodecContext.codec_tag = codecParam->codecTag;

    }
    else if (_codecInfo.type == FFMpegAudioDecoder) {
        _avcodecContext.sample_fmt = MediaSampleFormatToFFMpegSampleFormat(codecParam->sampleFormat);
        _avcodecContext.sample_rate = codecParam->sampleRate;
        _avcodecContext.channels = codecParam->channels;
    }

    int ret = avcodec_open2(&_avcodecContext, _avcodec, NULL);
    if (ret < 0) {
        return false;
    }
    return true;
}

media_base::RawVideoFrame * FFMpegDecoderImp::DecodeVideoFrame(media_base::CompassedFrame *compassedFrame)
{
    assert(_codecInfo.type == FFMpegVideoDecoder);
    return InnerDecodeVideoFrame(compassedFrame);
}

media_base::RawAudioFrame * FFMpegDecoderImp::DecodeAudioFrame(media_base::CompassedFrame * compassedFrame)
{
    assert(_codecInfo.type == FFMpegAudioDecoder);
    return InnerDecodeAudioFrame(compassedFrame);
}

media_base::RawVideoFrame * FFMpegDecoderImp::InnerDecodeVideoFrame(media_base::CompassedFrame * compassedFrame)
{
    ///<ICompressedFrame to AVPacket
    uint32_t    size = 0;
    uint8_t*    pData = NULL;
    int64_t     dts = -1;
    int64_t     pts = -1;
    int         flags = 0;
    int64_t     pos = -1;

    if (compassedFrame != NULL)
    {
        size = compassedFrame->frameDataSize;
        if (size < 2) {
            printf("frame size too small");
            return NULL;
        }
        pData   = (uint8_t*)compassedFrame->frameData;
        dts     = compassedFrame->decompassTimeStamp;
        pts     = compassedFrame->presentTimeStamp;
        flags   = compassedFrame->keyFrame;
        pos     = compassedFrame->position;
        
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
    int ret = avcodec_send_packet(&_avcodecContext, &avpkt);
    if (ret != 0) {
        printf("send video packet failed\n");
        av_frame_unref(decodedVideoFrame);
        return NULL;
    }
    ret = avcodec_receive_frame(&_avcodecContext, decodedVideoFrame);
    if (ret != 0) {
        if (ret == AVERROR(EAGAIN)) {
            av_frame_unref(decodedVideoFrame);
            return NULL;
        }
        else {
            printf("cannot decoder video,%d", ret);
            av_frame_unref(decodedVideoFrame);
            return NULL;
        }
    }

    media_base::RawVideoFrame *pRawVideoFrame = new media_base::RawVideoFrame(FFMpegPixelFormatToMediaPixelFormat(_avcodecContext.pix_fmt)
                                                                       ,decodedVideoFrame->width
                                                                       ,decodedVideoFrame->height);

    for (uint32_t i = 0; i < AV_NUM_DATA_POINTERS; i++) {
        if (decodedVideoFrame->linesize[i] > 0) {
            pRawVideoFrame->PushFrameData(decodedVideoFrame->linesize[i], (int8_t *)decodedVideoFrame->data[i]);
        }
        else {
            break;
        }
    }
    av_frame_free(&decodedVideoFrame);

    return pRawVideoFrame;
}

media_base::RawAudioFrame * FFMpegDecoderImp::InnerDecodeAudioFrame(media_base::CompassedFrame * compassedFrame) {
    uint32_t    size = 0;
    uint8_t*    pData = NULL;
    int64_t     dts = -1;
    int64_t     pts = -1;
    int         flags = 0;
    int64_t     pos = -1;

    if (compassedFrame != NULL)
    {
        size     = compassedFrame->frameDataSize;
        pData   = (uint8_t*)compassedFrame->frameData;
        dts     = compassedFrame->decompassTimeStamp;
        pts     = compassedFrame->presentTimeStamp;
        flags   = compassedFrame->keyFrame;
        pos     = compassedFrame->position;

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

    AVFrame *decodedAudioFrame = av_frame_alloc();
    int ret = avcodec_send_packet(&_avcodecContext, &avpkt);
    if (ret != 0) {
        printf("send video packet failed");
        av_frame_unref(decodedAudioFrame);
        return NULL;
    }

    ret = avcodec_receive_frame(&_avcodecContext, decodedAudioFrame);
    if (ret != 0) {
        if (ret == AVERROR(EAGAIN)) {
            av_frame_unref(decodedAudioFrame);
            return NULL;
        }
        else {
            printf("cannot decoder auido,%d", ret);
            av_frame_unref(decodedAudioFrame);
            return NULL;
        }
    }

    media_base::RawAudioFrame *audioFrame = new media_base::RawAudioFrame(FFMpegSampleFormatToMediaSampleFormat(_avcodecContext.sample_fmt),
                                                                          _avcodecContext.sample_rate,
                                                                          _avcodecContext.channels);
    for (uint32_t i = 0; i < AV_NUM_DATA_POINTERS; i++) {
        if (decodedAudioFrame->linesize[i] > 0) {
            audioFrame->PushFrameData((int8_t *)decodedAudioFrame->data[i], decodedAudioFrame->linesize[i]);
        }
        else {
            break;
        }
    }
    av_frame_free(&decodedAudioFrame);
    return audioFrame;
}

}   // namespace media_decoder

