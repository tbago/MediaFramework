//
//  IAudioDriver.h
//  MediaPlayer
//
//  Created by tbago on 2021/1/4.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_PLAYER_IAUDIO_DRIVER_H_
#define MEDIA_PLAYER_IAUDIO_DRIVER_H_

#include <MediaBase/ResuableSampleFormat.h>

namespace media_player {

class IVideoDriver
{
public:
    /*!
    @brief open Audio Driver
    @return bool result
    */
    virtual bool Open(uint32_t channels,
                    uint32_t sampleRate,
                    media_base::ResuableSampleFormat sampleFormat,
                    AudioDriverCallback callback, void *callbackParam) = 0;
    /*!
    @brief begin audio player
    @return bool result
    */
    virtual bool Play() = 0;
    /*!
    @brief close Audio Driver
    */
    virtual void Close() = 0;
};

}   // namespace media_player
#endif  // MEDIA_PLAYER_IAUDIO_DRIVER_H_
