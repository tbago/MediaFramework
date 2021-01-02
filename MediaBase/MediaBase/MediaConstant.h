//
//  MediaConstant.h
//  MediaBase
//
//  Created by tbago on 16/12/16.
//  Copyright © 2021 tbago. All rights reserved.

#ifndef MEDIA_BASE_MEDIA_CONSTANT_H_
#define MEDIA_BASE_MEDIA_CONSTANT_H_

#include <stdint.h>

namespace media_base {

/**
 *  Stream type enumeration
 */
typedef enum {
    UnknownStream,          ///< unknown stream type
    VideoStream,            ///< video stream
    AudioStream,            ///< audio stream
    SubtitleStream,         ///< subtitle stream
} StreamType;

/**
 * Media rational type
 */
struct MediaRational {
    int32_t numerator;
    int32_t denominator;
};

}   //namespace media_base
#endif // MEDIA_BASE_MEDIA_CONSTANT_H_

