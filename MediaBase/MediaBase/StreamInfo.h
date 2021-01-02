//
//  StreamInfo.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_BASE_STREAM_INFO_H_
#define MEDIA_BASE_STREAM_INFO_H_

#include <string>
#include <map>

#include "MediaConstant.h"
#include "ResuableCodecID.h"
#include "ResuablePixelFormat.h"
#include "ResuableSampleFormat.h"

namespace media_base {
/**
 * media stream info
 */
struct StreamInfo
{
    StreamType              streamType;
    int32_t                streamId;
    std::string            streamName;
    ResuableCodecID         codecID;
    std::string            codecName;
    std::string            language;
    int64_t                bitrate;    ///< The average bitrate of the encoded data (in bits per second)
    int64_t                duration;   ///< stream duration in ms, -1 is unkonwn
    uint32_t               codecTag;
    int32_t                bitsPerCodedSample;

    ///< video param
    int32_t                width;
    int32_t                height;
    ResuablePixelFormat      pixelFormat;
    MediaRational           framerate;
    MediaRational           pixelAspect;

    ///< audio param
    ResuableSampleFormat     sampleFormat;
    int32_t                samplerate;
    int32_t                channels;

    std::map<std::string, std::string>  metaData;       // stream metata map
    int8_t                           *extraData;     // stream extra data
    int32_t                          extraDataSize;  // stream extra data size
public:
    StreamInfo();
    StreamInfo(const StreamInfo &streamInfo);
    StreamInfo & operator=(const StreamInfo &streamInfo);
    ~StreamInfo();
private:
    void CopyStreamInfo(const StreamInfo &streamInfo);
};   //StreamInfo

}   // namespace media_base
#endif  // MEDIA_BASE_STREAM_INFO_H_

