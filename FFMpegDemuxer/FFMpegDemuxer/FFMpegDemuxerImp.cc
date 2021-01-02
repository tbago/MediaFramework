//
//  FFMpegDemuxerImp.m
//  FFMpegDemuxer
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "FFMpegDemuxerImp.h"
#include <Base/BaseUtils.h>
#include "FFMpegCommon.h"

namespace media_demuxer {

#define FMT_PROB_DATA_SIZE 1*1024*1024 //1M

void ffmpeg_log(void* avcl, int level, const char *fmt, va_list vl);


FFMpegDemuxer *createFFMpegDemuxer() {
    FFMpegDemuxerImp *demuxer = new FFMpegDemuxerImp();
    return demuxer;
}

FFMpegDemuxerImp::FFMpegDemuxerImp()
{
    _formatContext = NULL;
    InnerInitFFmpeg();
}

bool FFMpegDemuxerImp::OpenFileByPath(const std::string &filePath)
{
    CloseInputFile();

    av_log_set_callback(ffmpeg_log);

    AVInputFormat* format = NULL;
    if (filePath.find("rtsp://") == 0) {
        format = av_find_input_format("rtsp");
    }
    else if (filePath.find("rtmp://") == 0) {
        format = av_find_input_format("live_flv");
    }
    
    ///< check file format by probe data
    if (format == NULL)
    {
        AVProbeData probeData;
        memset(&probeData, 0, sizeof(probeData));
        uint32_t bufferSize = FMT_PROB_DATA_SIZE+AVPROBE_PADDING_SIZE;

        FILE *file = fopen(filePath.c_str(), "rb");
        if (file == NULL) {
            printf("cannot create file handle by file:%s", filePath.c_str());
            return false;
        }
        uint8_t *buffer = (uint8_t *)malloc(bufferSize);
        size_t readSize = fread(buffer, bufferSize, 0, file);
        if (readSize < bufferSize) {
            printf("file or stream is not have enough data");
            return false;
        }
        
        probeData.buf      = (uint8_t *)buffer;
        probeData.buf_size = (uint32_t)readSize;
        probeData.filename = extract_file_name(filePath).c_str();
        format = av_probe_input_format(&probeData, 1);
    }

    if (format == NULL) {
        std::string fileExt = extract_file_ext(filePath);
        if (fileExt == "mod" || filePath == "vob") {
            format = av_find_input_format("mpeg");
        }
        else if (fileExt == "mp3") {
            format = av_find_input_format("mp3");
        }
        else if (filePath == "tod"
                 || filePath == "mts"
                 || fileExt == "m2ts"
                 || fileExt == "tp"
                 || fileExt == "ts"
                 || fileExt == "trp"
                 || fileExt == "m2t")
        {
            format = av_find_input_format("mpegts");
        }
        else if(fileExt == "png"
                || fileExt == "tiff"
                || fileExt == "tif"
                || fileExt == "ppm")
        {
            format = av_find_input_format("image2");
        }
        if (fileExt == "mpeg"
            || fileExt =="mpg"
            || fileExt == "evo"
            || fileExt == "vdr")
        {
            format = av_find_input_format("mpeg");
        }
        else if (fileExt =="264"
                 || fileExt == "h264") {
            format = av_find_input_format("h264");
        }
        else if (fileExt =="mxf"
                 || fileExt =="MXF") {
            format = av_find_input_format("mxf");
        }
    }
    
    if (format == NULL) {
        printf("Cannot find input stream format");
        return false;
    }

    int ret = avformat_open_input(&_formatContext, filePath.c_str(), format, NULL);
    if (ret != 0) {
        printf("Open input failed");
        return false;
    }

    avformat_find_stream_info(_formatContext, NULL);

    BuildMovieInfo(filePath);

    _eof = false;
    return true;
}

void FFMpegDemuxerImp::CloseInputFile() {
    if (_formatContext != NULL) {
        avformat_close_input(&_formatContext);
        _formatContext = NULL;
    }
}

media_base::MovieInfo * FFMpegDemuxerImp::GetMovieInfo() {
    return &_movieInfo;
}

media_base::CompassedFrame * FFMpegDemuxerImp::ReadFrame() {
    AVPacket pkt;
    int ret = 0;
    bool bHasPkt = false;
    media_base::StreamType readStramType = media_base::UnknownStream;
    
    do{
        ret = av_read_frame(_formatContext, &pkt);
        if (ret < 0)
        {
            if (AVERROR(EAGAIN) == ret) {
                continue;
            }
            else {
                _eof = true;
                break;
            }
        }
        else {
            ///< check is video frame or audio frame
            ///< for now only support video and audio frame, also not support multi video audio stream
            AVCodecParameters *codecParam = _formatContext->streams[pkt.stream_index]->codecpar;
            if (codecParam->codec_type == AVMEDIA_TYPE_VIDEO) {
                readStramType = media_base::VideoStream;
                bHasPkt = true;
                break;
            }
            else if (codecParam->codec_type == AVMEDIA_TYPE_AUDIO) {
                readStramType = media_base::AudioStream;
                bHasPkt = true;
                break;
            }
            else {
                continue;
            }
        }
    } while(true);
    
    if (bHasPkt && readStramType != media_base::UnknownStream)
    {
        media_base::CompassedFrame *compassedFrame    = new media_base::CompassedFrame();
        compassedFrame->streamType         = readStramType;
        compassedFrame->keyFrame           = pkt.flags & AV_PKT_FLAG_KEY;
        compassedFrame->presentTimeStamp    = pkt.pts;
        compassedFrame->decompassTimeStamp  = pkt.dts;
        compassedFrame->position           = pkt.pos;
        compassedFrame->duration           = pkt.duration;
        compassedFrame->frameDataSize       = pkt.size;
        compassedFrame->frameData           = (int8_t *)malloc(pkt.size);
        memcpy(compassedFrame->frameData, pkt.buf, pkt.size);
        av_packet_unref(&pkt);

        return compassedFrame;
    }
    return NULL;
}

int64_t FFMpegDemuxerImp::GetCurrentTime()
{
    return 0;
}

bool FFMpegDemuxerImp::Eof() {
    return _eof;
}

void FFMpegDemuxerImp::InnerInitFFmpeg() {
    avformat_network_init();
}

void FFMpegDemuxerImp::BuildMovieInfo(const std::string &filePath)
{
    _movieInfo.name = extract_file_name(filePath);
    _movieInfo.format = _formatContext->iformat->name;
    
    ///< store movie meta data
    if (_formatContext->metadata != NULL) {
        AVDictionaryEntry *t = NULL;
        t = av_dict_get(_formatContext->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
        while (t != NULL)
        {
            if (t->key != NULL && t->value != NULL)
            {
                _movieInfo.metaData[std::string(t->key)] = std::string(t->value);
            }
            t = av_dict_get(_formatContext->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
        }
    }
    
    ///< build stream info
    for (uint32_t i = 0; i < _formatContext->nb_streams; i++) {
        AVStream* avStream = _formatContext->streams[i];
        media_base::StreamInfo *streamInfo = new media_base::StreamInfo();
        streamInfo->streamId = avStream->id;
        
        AVDictionaryEntry *tag = av_dict_get(avStream->metadata, "language", NULL, 0);
        if (tag != NULL && tag->value != NULL) {
            streamInfo->language = tag->value;
        }
        else {
            streamInfo->language = "eng";
        }
        
        if (avStream->duration != AV_NOPTS_VALUE) {
            int64_t duration = av_rescale_q(avStream->duration, avStream->time_base, gGloabalTimeBase);
            if (duration > 0) {
                streamInfo->duration = duration/1000;
            }
        }
        
        AVCodecParameters *codecParam = avStream->codecpar;
        if (codecParam == NULL) {
            streamInfo->streamType = media_base::UnknownStream;
            streamInfo->codecID = media_base::R_CODEC_ID_NONE;
            _movieInfo.streams.push_back(streamInfo);
            continue;
        }
        
        else if (codecParam->codec_type == AVMEDIA_TYPE_VIDEO) {
            streamInfo->streamType  = media_base::VideoStream;
            streamInfo->width       = codecParam->width;
            streamInfo->height      = codecParam->height;
            streamInfo->pixelFormat = FFMpegPixelFormatToMediaPixelFormat((AVPixelFormat)codecParam->format);
            
            ///< get video frame rate
            streamInfo->framerate.numerator = avStream->time_base.num;
            streamInfo->framerate.denominator = avStream->time_base.den;
            if (!IsValidFramerate(streamInfo->framerate.numerator, streamInfo->framerate.denominator)) {
                ///< use 30 as framerate
                streamInfo->framerate.numerator = 30;
                streamInfo->framerate.denominator = 1;
            }
            
            if (codecParam->sample_aspect_ratio.num == 0) {
                streamInfo->pixelAspect.numerator = 1;
                streamInfo->pixelAspect.denominator = 1;
            }
            else {
                streamInfo->pixelAspect.numerator = codecParam->sample_aspect_ratio.num;
                streamInfo->pixelAspect.denominator = codecParam->sample_aspect_ratio.den;
            }
            
            streamInfo->codecTag = codecParam->codec_tag;
            streamInfo->bitsPerCodedSample = codecParam->bits_per_coded_sample;
        }
        else if (codecParam->codec_type == AVMEDIA_TYPE_AUDIO) {
            streamInfo->streamType = media_base::AudioStream;

            streamInfo->channels = codecParam->channels;
            streamInfo->samplerate = codecParam->sample_rate;
            streamInfo->sampleFormat = FFMpegSampleFormatToMediaSampleFormat((AVSampleFormat)codecParam->format);
        }
        else if (codecParam->codec_type == AVMEDIA_TYPE_SUBTITLE) {
            streamInfo->streamType = media_base::SubtitleStream;
        }
        else {
            streamInfo->streamType = media_base::UnknownStream;
        }
        
        ///< common set media value
        streamInfo->bitrate = codecParam->bit_rate;
        if (codecParam->codec_id != AV_CODEC_ID_NONE && codecParam->codec_id != AV_CODEC_ID_PROBE) {
            AVCodec *pCodec = avcodec_find_decoder(codecParam->codec_id);
            if (pCodec != NULL) {
                streamInfo->codecName  = pCodec->name;
            }
        }
        else {
            streamInfo->streamType = media_base::UnknownStream;
        }
        
        ///< stream metadata
        if (avStream->metadata != NULL) {
            AVDictionaryEntry *t = NULL;
            t = av_dict_get(avStream->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
            while (t != NULL)
            {
                if (t->key != NULL && t->value != NULL)
                {
                    streamInfo->metaData[t->key] = t->value;
                }
                t = av_dict_get(avStream->metadata, "", t, AV_DICT_IGNORE_SUFFIX);
            }
        }
        
        ///< stream extra data
        if (codecParam->extradata != NULL && codecParam->extradata_size > 0) {
            streamInfo->extraDataSize = codecParam->extradata_size;
            streamInfo->extraData = (int8_t *)malloc(codecParam->extradata_size);
            memcpy(streamInfo->extraData, codecParam->extradata, codecParam->extradata_size);
        }

        streamInfo->codecID = FFMpegCodecIDToMeidaCodecID(codecParam->codec_id);
        _movieInfo.streams.push_back(streamInfo);
    }
}

bool FFMpegDemuxerImp::IsValidFramerate(int32_t numerator, int32_t denominator)
{
    double framerateValue = 1.0 * numerator / denominator;
    if (framerateValue >= 121 || framerateValue < 1) {
        return false;
    } else {
        return true;
    }
}

//////////////////////////////////////////////////////////////////////////
//ffmepg log call back
void ffmpeg_log(void* avcl, int level, const char *fmt, va_list vl)
{
    char buffer[256];
    if (level == AV_LOG_WARNING) {
        vsnprintf(buffer, 256, fmt, vl);
        printf("ffmpeg demuxer warning:%s", buffer);
    }
    else if (level == AV_LOG_ERROR) {
        vsnprintf(buffer, 256, fmt, vl);
        printf("ffmpeg demuxer error:%s", buffer);
    }
    else if (level == AV_LOG_FATAL) {
        vsnprintf(buffer, 256, fmt, vl);
        printf("ffmpeg demuxer fatal:%s", buffer);
    }
//    else if (level == AV_LOG_TRACE) {
//        vsnprintf(buffer, 256, fmt, vl);
//        NSLog(@"ffmpeg demuxer trace:%s", buffer);
//    }
//    else if (level == AV_LOG_DEBUG) {
//        vsnprintf(buffer, 256, fmt, vl);
//        NSLog(@"ffmpeg demuxer debug:%s", buffer);
//    }
}

}   //namespace media_demuxer

