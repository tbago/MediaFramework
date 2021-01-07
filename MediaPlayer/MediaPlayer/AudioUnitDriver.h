//
//  AudioUnitDriver.h
//  MediaPlayer
//
//  Created by tbago on 2021/1/6.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_PLAYER_AUDIO_UNIT_DRIVER_H_
#define MEDIA_PLAYER_AUDIO_UNIT_DRIVER_H_

#include <MediaPlayer/IAudioDriver.h>
#include <AudioToolbox/AudioToolbox.h>

namespace media_player {

class AudioUnitDriver : public IAudioDriver {
public:
    virtual bool Open(uint32_t channels,
                    uint32_t sampleRate,
                    media_base::ResuableSampleFormat sampleFormat,
                    int32_t frameSize,
                    AudioDriverCallback callback, void *callbackParam);
    virtual bool Play();
    virtual bool Close();
public:
    AudioUnitDriver();
    ~AudioUnitDriver();
private:
    int32_t GetBitPerChannel(media_base::ResuableSampleFormat sampleFormat);
public:
    AudioDriverCallback     _callback;
    void                  *_callbackParam;
    AudioComponentInstance   _audioPlayer;

};

}   // namespace media_player
#endif  // MEDIA_PLAYER_AUDIO_UNIT_DRIVER_H_

