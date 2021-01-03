//
//  RawVideoFrame.h
//  MediaBase
//
//  Created by tbago on 16/12/29.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_BASE_RAW_VIDEO_FRAME_H_
#define MEDIA_BASE_RAW_VIDEO_FRAME_H_

#include <vector>
#include <MediaBase/ResuablePixelformat.h>

namespace media_base {

struct RawVideoFrameBuffer {
    int8_t      *frameData;     // frame data with length lineSize * lineCount
    int32_t     lineSize;       // line byte count
    int32_t     lineCount;      // number of lines
};
/**
 *  decoded raw video frame
 */
struct RawVideoFrame
{
    ResuablePixelFormat       pixelFormat;
    uint32_t                width;
    uint32_t                height;
    int64_t                 timeStamp;
    int32_t                 duration;

    std::vector<RawVideoFrameBuffer *> frameBufferVector;
public:
    /**
    *  must use this method to init object,
    *
    *  @param pixelFormat video pixel format
    *  @param width       video width
    *  @param height      video height
    *
    *  @return new raw video frame instance
    */
    RawVideoFrame(ResuablePixelFormat pixelFormat, uint32_t width, uint32_t height);
    RawVideoFrame(const RawVideoFrame &videoFrame);
    RawVideoFrame & operator=(const RawVideoFrame &videoFrame);
    virtual ~RawVideoFrame();
public:
    void PushFrameData(uint32_t lineSize, int8_t * frameData);
private:
    void CopyInfo(const RawVideoFrame &videoFrame);
    void FreeFrameBuffer();

};

}   //namespace media_base
#endif  // MEDIA_BASE_RAW_VIDEO_FRAME_H_

