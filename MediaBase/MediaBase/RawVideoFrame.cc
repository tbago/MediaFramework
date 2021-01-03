//
//  RawVideoFrame.m
//  MediaBase
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "RawVideoFrame.h"

namespace media_base {

RawVideoFrame::RawVideoFrame(ResuablePixelFormat pixelFormat, uint32_t width, uint32_t height)
: pixelFormat(pixelFormat),
width(width),
height(height)
{
    timeStamp = 0;
    duration = 0;
}

RawVideoFrame::RawVideoFrame(const RawVideoFrame &videoFrame)
{
    CopyInfo(videoFrame);
}

RawVideoFrame & RawVideoFrame::operator=(const RawVideoFrame &videoFrame)
{
    if (this == &videoFrame) {
        return *this;
    }
    CopyInfo(videoFrame);
    return *this;
}

RawVideoFrame::~RawVideoFrame()
{
    FreeFrameBuffer();
}

void RawVideoFrame::PushFrameData(uint32_t lineSize, int8_t *frameData) {
    RawVideoFrameBuffer *frameBuffer = new RawVideoFrameBuffer();
    frameBuffer->lineSize = lineSize;
    uint32_t lineIndex = (uint32_t)frameBufferVector.size();
    switch(pixelFormat) {
        case R_PIX_FMT_YUV420P:
            if (lineIndex == 0) {
                frameBuffer->lineCount = height;
            }
            else {
                frameBuffer->lineCount = height >> 1;
            }
            break;
        case R_PIX_FMT_RGB24:     // Packed pixel, 3 bytes per pixel, RGBRGB...
        case R_PIX_FMT_BGR24:
            frameBuffer->lineCount = height;
            break;
        default:
            assert(false);
            break;
    }

    uint32_t frameDataLength = frameBuffer->lineSize * frameBuffer->lineCount;
    frameBuffer->frameData = (int8_t *)malloc(frameDataLength);
    memcpy(frameBuffer->frameData, frameData, frameDataLength);
    frameBufferVector.push_back(frameBuffer);
}

void RawVideoFrame::CopyInfo(const RawVideoFrame &videoFrame) {
    pixelFormat = videoFrame.pixelFormat;
    width = videoFrame.width;
    height = videoFrame.height;
    timeStamp = videoFrame.timeStamp;
    duration = videoFrame.duration;

    FreeFrameBuffer();
    for (uint32_t i = 0; i < videoFrame.frameBufferVector.size(); i++) {
        RawVideoFrameBuffer *frameBuffer = videoFrame.frameBufferVector[i];
        PushFrameData(frameBuffer->lineSize, frameBuffer->frameData);
    }
}

void RawVideoFrame::FreeFrameBuffer()
{
    for (uint32_t i = 0; i < frameBufferVector.size(); i++) {
        RawVideoFrameBuffer *frameBuffer = frameBufferVector[i];
        free(frameBuffer->frameData);
        delete frameBuffer;
        frameBufferVector[i] = NULL;
    }
    frameBufferVector.clear();
}

}   //namespace media_base
