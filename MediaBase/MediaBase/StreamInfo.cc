//
//  StreamInfo.m
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "StreamInfo.h"

namespace media_base {

StreamInfo::StreamInfo()
{
    streamType      = UnknownStream;
    streamId        = -1;
    bitrate         = -1;
    duration        = -1;

    width                     = -1;
    height                    = -1;
    framerate.numerator         = 1;
    framerate.denominator       = 1;
    pixelAspect.numerator       = 1;
    pixelAspect.denominator     = 1;

    sampleFormat                = R_SAMPLE_FMT_NB;
    samplerate                  = -1;
    channels                    = -1;

    extraData                   = NULL;
    extraDataSize               = 0;
}

StreamInfo::StreamInfo(const StreamInfo &streamInfo)
{
    CopyStreamInfo(streamInfo);
}

StreamInfo & StreamInfo::operator=(const StreamInfo &streamInfo)
{
    if (this == &streamInfo) {
        return *this;
    }
    CopyStreamInfo(streamInfo);
    return *this;
}

StreamInfo::~StreamInfo() {
}

void StreamInfo::CopyStreamInfo(const StreamInfo &streamInfo) {
    streamType = streamInfo.streamType;
    streamId = streamInfo.streamId;
    streamName = streamInfo.streamName;
    codecID = streamInfo.codecID;
    codecName = streamInfo.codecName;
    language = streamInfo.language;
    bitrate = streamInfo.bitrate;
    duration = streamInfo.duration;
    codecTag = streamInfo.codecTag;
    bitsPerCodedSample = streamInfo.bitsPerCodedSample;

    width = streamInfo.width;
    height = streamInfo.height;
    pixelFormat = streamInfo.pixelFormat;
    framerate = streamInfo.framerate;
    pixelAspect = streamInfo.pixelAspect;

    sampleFormat = streamInfo.sampleFormat;
    samplerate = streamInfo.samplerate;
    channels = streamInfo.channels;

    metaData.clear();
    for (auto it = streamInfo.metaData.begin(); it != streamInfo.metaData.end(); it++) {
        metaData[(*it).first] = metaData[(*it).second];
    }

    if (extraDataSize > 0 && extraData != NULL) {
        free(extraData);
    }

    if (streamInfo.extraDataSize > 0 && streamInfo.extraData != NULL) {
        extraDataSize = streamInfo.extraDataSize;
        extraData = (uint8_t *)malloc(extraDataSize);
        memcpy(extraData, streamInfo.extraData, extraDataSize);
    }
}
}   // media_base
