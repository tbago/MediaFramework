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
#include <stdint.h>

namespace media_player {

typedef enum
{
    CallBackStateContinue = 0,
    CallBackStateComplete = 1,
    CallBackStateAbort = 2
} AudioDriverCallbackState;

/*!
@brief AudioDriver callback function
@param callbackParam custom callback param
@param buffer buffer  is a pointer to the audio buffer you want to fill with information
@param bufferSize  size is the length of the audio buffer in bytes
*/
typedef AudioDriverCallbackState (*AudioDriverCallback)(void *callbackParam, void *buffer, uint32_t bufferSize);

class IAudioDriver
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
    virtual bool Close() = 0;
};

// FIXME:(tbag) for now only support one type audio driver for iOS
IAudioDriver *CreateAudioDriver();

}   // namespace media_player
#endif  // MEDIA_PLAYER_IAUDIO_DRIVER_H_
