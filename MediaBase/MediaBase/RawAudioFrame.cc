//
//  RawAudioFrame.cc
//  MediaBase
//
//  Created by tbago on 2021/1/1.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "RawAudioFrame.h"

namespace media_base {

RawAudioFrame::RawAudioFrame(ResuableSampleFormat sampleFormat, uint32_t sampleRate, uint32_t channels)
:sampleFormat(sampleFormat),
sampleRate(sampleRate),
channels(channels)
{
    timeStamp = -1;
}

RawAudioFrame::~RawAudioFrame()
{
    FreeFrameBuffer();
}

void RawAudioFrame::PushFrameData(int8_t *frameData, int32_t frameDataLength)
{
    RawAudioFrameBuffer *frameBuffer = new RawAudioFrameBuffer();
    frameBuffer->frameDataLength = frameDataLength;
    frameBuffer->frameData = (int8_t *)malloc(frameDataLength);
    memcpy(frameBuffer->frameData, frameData, frameDataLength);

    frameBufferVector.push_back(frameBuffer);
}

void RawAudioFrame::FreeFrameBuffer()
{
    for (uint32_t i = 0; i < frameBufferVector.size(); i++) {
        RawAudioFrameBuffer *frameBuffer = frameBufferVector[i];
        free(frameBuffer->frameData);
        delete frameBuffer;
        frameBufferVector[i] = NULL;
    }
    frameBufferVector.clear();
}
}   // namespace media_base

