//
//  CompassedFrame.m
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "CompassedFrame.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

namespace media_base {

CompassedFrame::CompassedFrame()
{
    streamType = UnknownStream;
    codecID = R_CODEC_ID_NONE;
    decompassTimeStamp = -1;
    presentTimeStamp = -1;
    duration = -1;
    position = -1;
    frameData = NULL;
    frameDataSize = 0;
}

CompassedFrame::CompassedFrame(const CompassedFrame &compassedFrame)
{
    CopyInfo(compassedFrame);
}

CompassedFrame & CompassedFrame::operator=(const CompassedFrame &compassedFrame)
{
    if (this == &compassedFrame) {
        return *this;
    }
    CopyInfo(compassedFrame);
    return *this;
}

CompassedFrame::~CompassedFrame()
{
    if (frameDataSize > 0 && frameData != NULL) {
        free(frameData);
        frameData = NULL;
        frameDataSize = 0;
    }
}

void CompassedFrame::CopyInfo(const CompassedFrame &compassedFrame)
{
    streamType = compassedFrame.streamType;
    codecID = compassedFrame.codecID;
    keyFrame = compassedFrame.keyFrame;
    decompassTimeStamp = compassedFrame.decompassTimeStamp;
    presentTimeStamp = compassedFrame.presentTimeStamp;
    duration = compassedFrame.duration;
    position = compassedFrame.duration;
    if (frameDataSize > 0 && frameData != NULL) {
        free(frameData);
        frameData = NULL;
        frameDataSize = 0;
    }

    if (compassedFrame.frameDataSize > 0 && compassedFrame.frameData != NULL) {
        frameDataSize = compassedFrame.frameDataSize;
        frameData = (int8_t *)malloc(frameDataSize);
        memcpy(frameData, compassedFrame.frameData, frameDataSize);
    }
}

}   // namespace media_base
