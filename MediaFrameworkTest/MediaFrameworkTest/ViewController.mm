//
//  ViewController.m
//  MediaFrameworkTest
//
//  Created by tbago on 16/12/16.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "ViewController.h"
#include <FFMpegDemuxer/FFMpegDemuxer.h>
#include <FFMpegDecoder/FFMpegDecoder.h>
#include <MediaPlayer/IVideoDriver.h>
#include <MediaPlayer/IAudioDriver.h>

#import "OpenGLView.h"

@interface ViewController ()
{
    media_demuxer::FFMpegDemuxer             *_ffmpegDemuxer;
    media_decoder::FFMpegDecoderEnumerator   *_ffDecoderEnumerator;
    media_decoder::FFMpegDecoder             *_ffVideoDecoder;
    media_decoder::FFMpegDecoder             *_ffAudioDecoder;
    media_player::IVideoDriver                  *_videoDriver;
    media_player::IAudioDriver                  *_audioDriver;
}

@property (nonatomic) BOOL                            stopDecoder;
@property (weak, nonatomic) IBOutlet OpenGLView          *glView;
@end

media_player::AudioDriverCallbackState AudioDriverCallback(void *callbackParam, void *buffer, uint32_t bufferSize)
{
    return media_player::CallBackStateContinue;
}

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];

    _ffmpegDemuxer = media_demuxer::CreateFFMpegDemuxer();
    _ffDecoderEnumerator = new media_decoder::FFMpegDecoderEnumerator();

    media_player::VideoDriverConfig driverConfig;
    driverConfig.videoWindow = (__bridge void *)self.glView;
    driverConfig.driverType = media_player::DriverTypeOpenGLES;
    driverConfig.screenScale = [UIScreen mainScreen].scale;

    _videoDriver = media_player::CreateVideoDriver(driverConfig);

    _videoDriver->Init();

    media_player::TRect rect;
    rect.left = self.glView.bounds.origin.x;
    rect.top = self.glView.bounds.origin.y;
    rect.width = self.glView.bounds.size.width;
    rect.height = self.glView.bounds.size.height;
    _videoDriver->SetDestRect(rect);
}

- (IBAction)testButtonClick:(UIButton *)sender {
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"1" ofType:@"mp4"];
//    NSString *filePath = @"rtmp://192.168.0.103:1935/live/live1";
    bool openRet = _ffmpegDemuxer->OpenFileByPath(filePath.UTF8String);
    if (!openRet) {
        return;
    }
    
    [self openDecoderForTest];
    return;
}

- (IBAction)stopLiveButtonClick:(UIButton *)sender {
    // TODO: (tbago) not implement
}

- (void)openDecoderForTest {
    media_base::MovieInfo *sourceMovieInfo = _ffmpegDemuxer->GetMovieInfo();
    ///< ffmpeg decoder test
    _ffDecoderEnumerator->InitDecoderArray();

    media_base::StreamInfo *videoStreamInfo = NULL;
    media_base::StreamInfo *audioStreamInfo = NULL;
    for (media_base::StreamInfo *streamInfo : sourceMovieInfo->streams) {
        if (streamInfo->streamType == media_base::VideoStream) {
            videoStreamInfo = streamInfo;
        }
        else if (streamInfo->streamType == media_base::AudioStream) {
            audioStreamInfo = streamInfo;
        }
    }
    if (videoStreamInfo == NULL) {
        return;
    }
    _ffVideoDecoder = _ffDecoderEnumerator->CreateFFMpegDecoderByCodecId(videoStreamInfo->codecID);
    if (_ffVideoDecoder != NULL) {
        media_decoder::AVCodecParam codecParam;
        codecParam.width                = videoStreamInfo->width;
        codecParam.height               = videoStreamInfo->height;
        codecParam.codecTag             = videoStreamInfo->codecTag;
        codecParam.bitsPerCodedSample    = videoStreamInfo->bitsPerCodedSample;
        codecParam.numThreads           = 1;
        codecParam.extraData            = videoStreamInfo->extraData;
        codecParam.extraDataSize         = videoStreamInfo->extraDataSize;

        bool ret = _ffVideoDecoder->OpenCodec(&codecParam);
        if (!ret) {
            return;
        }
    }
    if (audioStreamInfo != NULL) {
        _ffAudioDecoder = _ffDecoderEnumerator->CreateFFMpegDecoderByCodecId(audioStreamInfo->codecID);
        if (_ffAudioDecoder != NULL) {
            media_decoder::AVCodecParam codecParam;
            codecParam.sampleFormat = audioStreamInfo->sampleFormat;
            codecParam.sampleRate   = audioStreamInfo->samplerate;
            codecParam.channels    = audioStreamInfo->channels;
            codecParam.frameSize    = audioStreamInfo->frameSize;
            codecParam.extraData    = audioStreamInfo->extraData;
            codecParam.extraDataSize = audioStreamInfo->extraDataSize;

            bool ret = _ffAudioDecoder->OpenCodec(&codecParam);
            if (!ret) {
                return;
            }
        }

        _audioDriver = media_player::CreateAudioDriver();
        _audioDriver->Open(audioStreamInfo->channels,
                           audioStreamInfo->samplerate,
                           audioStreamInfo->sampleFormat,
                           audioStreamInfo->frameSize,
                           AudioDriverCallback,
                           (__bridge void *)self);
        _audioDriver->Play();
    }

    [NSThread detachNewThreadSelector:@selector(loopReadAndDecodeStreamData) toTarget:self withObject:nil];
}

- (void)loopReadAndDecodeStreamData {
    while(!self.stopDecoder)
    {
        media_base::CompassedFrame *compassedFrame = _ffmpegDemuxer->ReadFrame();
        if (compassedFrame == nil) {
            continue;
        }
        else {
            media_base::RawVideoFrame *videoFrame = NULL;
            if (compassedFrame->streamType == media_base::VideoStream) {
                videoFrame = _ffVideoDecoder->DecodeVideoFrame(compassedFrame);
            }
            media_base::RawAudioFrame *audioFrame = NULL;
            if (compassedFrame->streamType == media_base::AudioStream) {
                audioFrame = _ffAudioDecoder->DecodeAudioFrame(compassedFrame);
            }
            delete compassedFrame;
            if (videoFrame != NULL){
                dispatch_async(dispatch_get_main_queue(), ^{
                    media_player::TRect rect;
                    rect.left = self.glView.bounds.origin.x;
                    rect.top = self.glView.bounds.origin.y;
                    rect.width = self.glView.bounds.size.width;
                    rect.height = self.glView.bounds.size.height;
                    self->_videoDriver->DrawImage(videoFrame, rect, rect);
                    delete videoFrame;
                });
            }
            else if (audioFrame != NULL) {
                
            }
        }
    }
}

@end
