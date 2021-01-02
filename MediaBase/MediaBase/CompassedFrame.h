//
//  CompassedFrame.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_BASE_COMPASS_FRAME_H_
#define MEDIA_BASE_COMPASS_FRAME_H_

#include "MediaConstant.h"
#include "ResuableCodecID.h"

namespace media_base {

struct CompassedFrame
{
    StreamType        streamType;
    ResuableCodecID    codecID;
    bool              keyFrame;                   ///<  weather is key frame
    int64_t           decompassTimeStamp;          ///<  dts value
    int64_t           presentTimeStamp;           ///<  pts value
    int64_t           duration;                  ///<  frame duration
    int64_t           position;                  ///<  frame position
    int8_t            *frameData;                ///<  frame  data in memory
    int32_t           frameDataSize;              ///< frame data size
public:
    CompassedFrame();
    CompassedFrame(const CompassedFrame & compassedFrame);
    CompassedFrame & operator=(const CompassedFrame &compassedFrame);
    ~CompassedFrame();
private:
    void CopyInfo(const CompassedFrame & compassedFrame);
};

}   //namespace media_base
#endif  // MEDIA_BASE_COMPASS_FRAME_H_
