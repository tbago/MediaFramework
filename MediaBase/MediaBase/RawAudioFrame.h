//
//  RawAudioFrame.h
//  MediaBase
//
//  Created by tbago on 2021/1/1.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_BASE_RAW_AUDIO_FRAME_H_
#define MEDIA_BASE_RAW_AUDIO_FRAME_H_

#include <stdint.h>
#include <vector>
#include <MediaBase/ResuableSampleFormat.h>

namespace media_base
{

struct RawAudioFrameBuffer {
    int8_t  *frameData;
    int32_t frameDataLength;
};

struct RawAudioFrame
{
    ResuableSampleFormat    sampleFormat;
    uint32_t              sampleRate;
    uint32_t              channels;
    int64_t               timeStamp;

    std::vector<RawAudioFrameBuffer *>  frameBufferVector;
public:
    RawAudioFrame(ResuableSampleFormat sampleFormat, uint32_t sampleRate, uint32_t channels);
    // TODO: (tbago) not implement for now
    RawAudioFrame(const RawAudioFrame &audioFrame) = delete;
    RawAudioFrame & operator=(const RawAudioFrame &audioFrame) = delete;
    virtual ~RawAudioFrame();
public:
    void PushFrameData(int8_t *frameData, int32_t frameDataLength);
private:
    void FreeFrameBuffer();
};

}   //namespace media_base
#endif // MEDIA_BASE_RAW_AUDIO_FRAME_H_

