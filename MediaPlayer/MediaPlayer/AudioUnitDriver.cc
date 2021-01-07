//
//  AudioUnitDriver.cc
//  MediaPlayer
//
//  Created by tbago on 2021/1/6.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "AudioUnitDriver.h"

namespace media_player {

IAudioDriver *CreateAudioDriver() {
    return new AudioUnitDriver();
}

static OSStatus AudioPlayBack(void *inRefCon,
                          AudioUnitRenderActionFlags *ioActionFlags,
                          const AudioTimeStamp *inTimeStamp,
                          uint32_t inBusNumber,
                          uint32_t inNumberFrames,
                          AudioBufferList *ioData)
{
    AudioUnitDriver *driver = (AudioUnitDriver *)inRefCon;

    for (int i=0; i < ioData->mNumberBuffers; i++) {
        AudioBuffer buffer = ioData->mBuffers[i];
        /*----------------------------------------------------------------------
         |   1.根据buffer.mDataByteSize大小需求，给buffer.mData赋值相应大小的数据内容;|
         |   2.若无数据，则把数据填写为0，默认正在播放无声音频；                        |
         |       UInt16 *frameBuffer = buffer.mData;                            |
         |       for (int j = 0; j < inNumberFrames; j++) {                     |
         |           frameBuffer[j] = 0;                                        |
         |       }                                                              |
         ----------------------------------------------------------------------*/
        uint16_t *frameBuffer = (uint16_t *)buffer.mData;
        printf("require data %d length:%d\n", i, buffer.mDataByteSize);
        driver->_callback(driver->_callbackParam, frameBuffer, buffer.mDataByteSize);
    }
    return noErr;
}

bool AudioUnitDriver::Open(uint32_t channels,
                        uint32_t sampleRate,
                        media_base::ResuableSampleFormat sampleFormat,
                        int32_t frameSize,
                        AudioDriverCallback callback, void *callbackParam)
{
    AudioComponentDescription  desc;
    desc.componentType         = kAudioUnitType_Output;         //audio output
    desc.componentSubType      = kAudioUnitSubType_RemoteIO;    //audio channels
    desc.componentFlags        = 0;                             //default is “0”
    desc.componentFlagsMask    = 0;                             //default is “0”
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;  // manufacturer info

    // Get component
    AudioComponent inputComponent = AudioComponentFindNext(NULL, &desc);
    // Get audio units

    OSStatus status = AudioComponentInstanceNew(inputComponent, &_audioPlayer);
    if (status != 0) {
        printf("Create audio instance failed:%d\n", status);
        return false;
    }

    // Enable IO for playing（kAudioUnitScope_Input ==> recording）
    uint32_t flag = 1;
    status = AudioUnitSetProperty(_audioPlayer,
                               kAudioOutputUnitProperty_EnableIO,
                               kAudioUnitScope_Output,
                               0,
                               &flag,
                               sizeof(flag));
    if (status != 0) {
        printf("enable io for playing failed:%d\n", status);
        return false;
    }

    //set describtion format
    AudioStreamBasicDescription audioFormat;
    memset(&audioFormat, 0, sizeof(audioFormat));
    audioFormat.mSampleRate       = sampleRate;
    audioFormat.mBitsPerChannel   = GetBitPerChannel(sampleFormat);
    audioFormat.mChannelsPerFrame = 1;
    audioFormat.mFormatID         = kAudioFormatLinearPCM;
    // TODO: (tbago) need support more format
    if (sampleFormat == media_base::R_SAMPLE_FMT_S16) {
        audioFormat.mFormatFlags      = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
        audioFormat.mBytesPerFrame    = 2;
    }
    else if (sampleFormat == media_base::R_SAMPLE_FMT_S16P) {
        audioFormat.mFormatFlags      = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
        audioFormat.mBytesPerFrame    = 2;
    }
    else if (sampleFormat == media_base::R_SAMPLE_FMT_FLTP) {
        audioFormat.mFormatFlags      = kAudioFormatFlagIsFloat;
        audioFormat.mBytesPerFrame    = 4;
    }
    else if (sampleFormat == media_base::R_SAMPLE_FMT_FLT) {
        audioFormat.mFormatFlags      = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked;
        audioFormat.mBytesPerFrame    = 4;
    }
    else {
        assert(false);
    }
    audioFormat.mFramesPerPacket  = 1;
    audioFormat.mBytesPerPacket   = audioFormat.mChannelsPerFrame * audioFormat.mBytesPerFrame * audioFormat.mFramesPerPacket;

    status = AudioUnitSetProperty(_audioPlayer,
                               kAudioUnitProperty_StreamFormat,
                               kAudioUnitScope_Input,
                               0,
                               &audioFormat,
                               sizeof(audioFormat));
    if (status != 0) {
        printf("set audio param failed:%d\n", status);
        return false;
    }

    // set callback function and param
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = (AURenderCallback)AudioPlayBack;
    callbackStruct.inputProcRefCon = this;
    status = AudioUnitSetProperty(_audioPlayer,
                               kAudioUnitProperty_SetRenderCallback,
                               kAudioUnitScope_Global,
                               0,
                               &callbackStruct,
                               sizeof(callbackStruct));
    if (status != 0) {
        printf("Set audio callback failed:%d", status);
        return false;
    }

       //init audio component
    status = AudioUnitInitialize(_audioPlayer);
    if (status != 0) {
        printf("Init audio component failed:%d\n", status);
        return false;
    }

    _callback = callback;
    _callbackParam = callbackParam;
    return true;
}

bool AudioUnitDriver::Play() {
    OSStatus status = AudioOutputUnitStart(_audioPlayer);
    if (status != 0) {
        printf("Play audio failed:%d", status);
        return false;
    }
    return true;
}

bool AudioUnitDriver::Close() {
    OSStatus status = AudioOutputUnitStop(_audioPlayer);
    if (status != 0) {
        printf("Close audio failed:%d", status);
        return false;
    }
    status = AudioUnitUninitialize(_audioPlayer);
    if (status != 0) {
        printf("Uninitialize audio unit failed:%d", status);
        return false;
    }
    status = AudioComponentInstanceDispose(_audioPlayer);
    if (status != 0) {
        printf("Audio Component Instance dispose failed:%d", status);
        return false;
    }
    return true;
}

AudioUnitDriver::AudioUnitDriver() {

}

AudioUnitDriver::~AudioUnitDriver() {

}

int AudioUnitDriver::GetBitPerChannel(media_base::ResuableSampleFormat sampleFormat) {
    switch (sampleFormat) {
        case media_base::R_SAMPLE_FMT_U8:
        case media_base::R_SAMPLE_FMT_U8P:
            return 8;
            break;
        case media_base::R_SAMPLE_FMT_S16:
        case media_base::R_SAMPLE_FMT_S16P:
            return 16;
            break;
        case media_base::R_SAMPLE_FMT_S32:
        case media_base::R_SAMPLE_FMT_S32P:
            return 32;
            break;
        case media_base::R_SAMPLE_FMT_FLT:
        case media_base::R_SAMPLE_FMT_FLTP:
            return 32;
            break;
        case media_base::R_SAMPLE_FMT_DBL:
        case media_base::R_SAMPLE_FMT_DBLP:
            return 64;
            break;
        case media_base::R_SAMPLE_FMT_S64:
        case media_base::R_SAMPLE_FMT_S64P:
            return 64;
            break;
        default:
            return 16;
            break;
    }
}

}   // namespace media_player

