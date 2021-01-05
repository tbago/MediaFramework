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

#import "OpenGLView.h"
#import "OpenGLView20.h"

#import "rtmp.h"

#define RTMP_HEAD_SIZE   (sizeof(RTMPPacket)+RTMP_MAX_HEADER_SIZE)

@interface ViewController ()
{
    media_demuxer::FFMpegDemuxer             *_ffmpegDemuxer;
    media_decoder::FFMpegDecoderEnumerator    *_ffDecoderEnumerator;
    media_decoder::FFMpegDecoder             *_ffVideoDecoder;
    media_decoder::FFMpegDecoder             *_ffAudioDecoder;
    media_player::IVideoDriver               *_videoDriver;
    RTMP                                  *_rtmpClient;
    std::vector<media_base::CompassedFrame *> compassedFrameVector;
}

@property (nonatomic) BOOL                            stopDecoder;
@property (weak, nonatomic) IBOutlet OpenGLView          *glView;
///< rtmp live
@property (nonatomic) int64_t                           startPts;
@property (atomic)    BOOL                             stopLive;
@end

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
    
///< rtmp live test

    media_base::MovieInfo *movieInfo = _ffmpegDemuxer->GetMovieInfo();
    media_base::StreamInfo *videoStreamInfo = movieInfo->streams[0];     ///only for test

    NSAssert(videoStreamInfo->streamType == media_base::VideoStream, @"only for video test");

    self.startPts          = 0;
    self.stopLive          = NO;

    [self closeRtmpServer];
//    [self connectRtmpServer:@"rtmp://192.168.42.12:1935/anxs/room"];
    [self connectRtmpServer:@"rtmp://send3.douyu.com/live/1257373rX0RkXHys?wsSecret=ac06c9be0eade5d8a3673871a8c95ef4&wsTime=586335ff"];
    ///< write sps and pps header
    uint64_t cursor          = 0;
    uint64_t nal_unit_length = 0;
    uint8_t nal_unit_type    = 0;
    uint8_t *spsIndex        = NULL;
    uint32_t spsLength       = 0;
    uint8_t *ppsIndex        = NULL;
    uint32_t ppsLength       = 0;
    BOOL findSps             = NO;
    BOOL findPps             = NO;
    uint8_t *extraData       = videoStreamInfo->extraData;
    do {
        nal_unit_length = [self GetOneNalUnit:&nal_unit_type pBuffer:extraData+cursor bufferSize:videoStreamInfo->extraDataSize-cursor];
        switch (nal_unit_type)
        {
            case 9:     ///< aud
                break;
            case 7:     ///< sps
                spsIndex = extraData+cursor;
                spsLength = (uint32_t)nal_unit_length;
                findSps = YES;
                break;
            case 8:     ///< pps
                ppsIndex = extraData+cursor;
                ppsLength = (uint32_t)nal_unit_length;
                findPps = YES;
                break;
            case 5:
                break;
        }
        cursor += nal_unit_length;
    } while (cursor < videoStreamInfo->extraDataSize);
    if (findSps && findPps) {
        [self rtmpWriteVideoHeader:ppsIndex ppsLen:ppsLength sps:spsIndex spsLen:spsLength];
    }

    ///< begin queue to send data
    [NSThread detachNewThreadSelector:@selector(loopReadStreamData) toTarget:self withObject:nil];
    [NSThread detachNewThreadSelector:@selector(loopSendStreamData) toTarget:self withObject:nil];
}

- (IBAction)stopLiveButtonClick:(UIButton *)sender {
    self.stopLive = YES;
}

- (void)openDecoderForTest {
    media_base::MovieInfo *sourceMovieInfo = _ffmpegDemuxer->GetMovieInfo();
    ///< ffmpeg decoder test
    _ffDecoderEnumerator->InitDecoderArray();

    media_base::StreamInfo *videoStreamInfo = nil;
    media_base::StreamInfo *audioStreamInfo = nil;
    for (media_base::StreamInfo *streamInfo : sourceMovieInfo->streams) {
        if (streamInfo->streamType == media_base::VideoStream) {
            videoStreamInfo = streamInfo;
        }
        else if (streamInfo->streamType == media_base::AudioStream) {
            audioStreamInfo = streamInfo;
        }
    }
    if (videoStreamInfo == nil) {
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
    _ffAudioDecoder = _ffDecoderEnumerator->CreateFFMpegDecoderByCodecId(audioStreamInfo->codecID);
    if (_ffAudioDecoder != NULL) {
        media_decoder::AVCodecParam codecParam;
        codecParam.sampleFormat = audioStreamInfo->sampleFormat;
        codecParam.sampleRate   = audioStreamInfo->samplerate;
        codecParam.channels    = audioStreamInfo->channels;

        bool ret = _ffAudioDecoder->OpenCodec(&codecParam);
        if (!ret) {
            return;
        }
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
//            if (compassedFrame->streamType == media_base::AudioStream) {
//                audioFrame = _ffAudioDecoder->DecodeAudioFrame(compassedFrame);
//            }
            delete compassedFrame;
            if (videoFrame != NULL){
                dispatch_async(dispatch_get_main_queue(), ^{
//                    [self.glView DrawImage:videoFrame];
                    media_player::TRect rect;
                    rect.left = self.glView.bounds.origin.x;
                    rect.top = self.glView.bounds.origin.y;
                    rect.width = self.glView.bounds.size.width;
                    rect.height = self.glView.bounds.size.height;
                    self->_videoDriver->DrawImage(videoFrame, rect, rect);
//                    [self renderVideoFrame:videoFrame];
                    delete videoFrame;
                });
            }
            else if (audioFrame != NULL) {
                
            }
        }
    }
}

- (void)renderVideoFrame:(media_base::RawVideoFrame *) videoFrame {
    uint32_t bufferSize = videoFrame->width * videoFrame->height * 3 / 2 + 1;
    int8_t *buffer = (int8_t *)malloc(bufferSize);
    uint32_t bufferIndex = 0;

    ///< copy y data
    media_base::RawVideoFrameBuffer *yFrameBuffer = videoFrame->frameBufferVector[0];
    uint32_t lineSizeY = yFrameBuffer->lineSize;
    int8_t *yBuffer = yFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height; i++) {
        memcpy(buffer + bufferIndex, yBuffer + i * lineSizeY, videoFrame->width);
        bufferIndex += videoFrame->width;
    }

    ///< copy u data
    media_base::RawVideoFrameBuffer *uFrameBuffer = videoFrame->frameBufferVector[1];
    uint32_t lineSizeU = uFrameBuffer->lineSize;
    int8_t *uBuffer = uFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height/2; i++) {
        memcpy(buffer + bufferIndex, uBuffer + i * lineSizeU, videoFrame->width/2);
        bufferIndex += videoFrame->width/2;
    }
    ///< copy v data
    media_base::RawVideoFrameBuffer *vFrameBuffer = videoFrame->frameBufferVector[2];
    uint32_t lineSizeV = vFrameBuffer->lineSize;
    int8_t *vBuffer = vFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height/2; i++) {
        memcpy(buffer + bufferIndex, vBuffer + i * lineSizeV, videoFrame->width/2);
        bufferIndex += videoFrame->width/2;
    }

//    [self.glView displayYUV420pData:buffer width:videoFrame->width height:videoFrame->height];
    free(buffer);
}

#pragma mark - get & set

#pragma mark - librtmp method

- (uint64_t) GetOneNalUnit:(uint8_t *) pNaluType
                   pBuffer:(uint8_t *) pBuffer
                bufferSize:(uint64_t) bufferSize
{
    uint32_t pos = 0;
    uint32_t tempValue = 0;
    
    for (uint32_t code = 0xffffffff; pos < 4; pos++) {
        tempValue = pBuffer[pos];
        code = (code<<8)|tempValue;
    }
    
    *pNaluType = pBuffer[pos++] & 0x1F;
    for (uint32_t code=0xffffffff; pos < bufferSize; pos++) {
        tempValue = pBuffer[pos];
        if ((code=(code<<8)|tempValue) == 0x00000001) {
            break; //next start code is found
        }
    }
    if (pos == bufferSize) {
        // next start code is not found, this must be the last nalu
        return bufferSize;
    } else {
        return pos-4+1;
    }
}

- (void)loopReadStreamData
{
    while(!self.stopLive)
    {
        media_base::CompassedFrame *compassedFrame = _ffmpegDemuxer->ReadFrame();
        if (compassedFrame == nil) {
            break;
        }
        else {
            ///< max cache 20 frame
            if (compassedFrameVector.size() < 20) {
                compassedFrameVector.push_back(compassedFrame);
            }
        }
    }
}

- (void)loopSendStreamData {
    while (!self.stopLive)
    {
        if (compassedFrameVector.size() > 0) {
            media_base::CompassedFrame *compassedFrame = compassedFrameVector[0];

            int64_t convertPts = compassedFrame->presentTimeStamp * 1000 / 90000;
            compassedFrameVector.erase(compassedFrameVector.begin());
            [self sendPacket:RTMP_PACKET_TYPE_VIDEO
                    keyFrame:compassedFrame->keyFrame
                        data:compassedFrame->frameData
                        size:compassedFrame->frameDataSize
                  nTimeStamp:convertPts];
            delete compassedFrame;
        }
        else {
            sleep(0.1);
        }
    }
}

- (BOOL)connectRtmpServer:(NSString *) rtmpURL {
    /*alloc and init */
    _rtmpClient = RTMP_Alloc();
    RTMP_Init(_rtmpClient);
    
    /*设置URL*/
    if (RTMP_SetupURL(_rtmpClient, (char *)rtmpURL.UTF8String) == FALSE) {
        NSLog(@"RTMP_SetupURL() failed!");
        RTMP_Free(_rtmpClient);
        _rtmpClient = nil;
        return NO;
    }
    
    /*设置可写,即发布流,这个函数必须在连接前使用,否则无效*/
    RTMP_EnableWrite(_rtmpClient);
    
    /*连接服务器*/
    if (RTMP_Connect(_rtmpClient, NULL) == FALSE) {
        NSLog(@"RTMP_Connect() failed!");
        RTMP_Free(_rtmpClient);
        _rtmpClient = nil;
        return NO;
    }
    
    /*连接流*/
    if (RTMP_ConnectStream(_rtmpClient, 0) == FALSE) {
        NSLog(@"RTMP_ConnectStream() failed!");
        RTMP_Close(_rtmpClient);
        RTMP_Free(_rtmpClient);
        _rtmpClient = nil;
        return NO;
    }
    
    NSLog(@"open stream success");
    
    //    [self setRtmpPacketSize:1024];
    return YES;
}

- (void)closeRtmpServer {
    if (_rtmpClient != NULL) {
        RTMP_Close(_rtmpClient);
        RTMP_Free(_rtmpClient);
        _rtmpClient = NULL;
    }
}

- (int)rtmpWriteVideoHeader:(uint8_t *) pps
                     ppsLen:(uint32_t) ppsLen
                        sps:(uint8_t*) sps
                     spsLen:(uint32_t) spsLen
{
    RTMPPacket  * packet = NULL;
    uint8_t     * body = NULL;
    int i;
    packet = (RTMPPacket *)malloc(RTMP_HEAD_SIZE + 1024);
    memset(packet, 0, RTMP_HEAD_SIZE + 1024);
    packet->m_body = (char *)packet + RTMP_HEAD_SIZE;
    body = (unsigned char *)packet->m_body;
    i = 0;
    body[i++] = 0x17;
    body[i++] = 0x00;
    
    body[i++] = 0x00;
    body[i++] = 0x00;
    body[i++] = 0x00;
    
    /*AVCDecoderConfigurationRecord*/
    body[i++] = 0x01;
    body[i++] = sps[1];
    body[i++] = sps[2];
    body[i++] = sps[3];
    body[i++] = 0xff;
    
    /*sps*/
    body[i++] = 0xe1;
    body[i++] = (spsLen >> 8) & 0xff;
    body[i++] = spsLen & 0xff;
    memcpy(&body[i], sps, spsLen);
    i += spsLen;
    
    /*pps*/
    body[i++] = 0x01;
    body[i++] = (ppsLen >> 8) & 0xff;
    body[i++] = (ppsLen) & 0xff;
    memcpy(&body[i], pps, ppsLen);
    i += ppsLen;
    
    packet->m_packetType = RTMP_PACKET_TYPE_VIDEO;
    packet->m_nBodySize = i;
    packet->m_nChannel = 0x04;
    packet->m_nTimeStamp = 0;
    packet->m_hasAbsTimestamp = 0;
    packet->m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet->m_nInfoField2 = _rtmpClient->m_stream_id;
    
    int nRet = RTMP_SendPacket(_rtmpClient, packet, TRUE);
    free(packet);
    return nRet;
}

- (int32_t)rtmpWriteAudioHeader
{
    //	unsigned int audio_sample_rate[] = {96000,88200,64000,48000,44100,32000,24000,22050,16000,12000,11025,8000};
    RTMPPacket packet;
    RTMPPacket_Reset(&packet);
    RTMPPacket_Alloc(&packet, 4);
    
    packet.m_body[0] = 0xAF;  // MP3 AAC format 44100Hz
    packet.m_body[1] = 0x00;
    //	packet.m_body[2] = 0x11;
    packet.m_body[2] = 0x12;
    //	packet.m_body[3] = 0x90;//0x10ÐÞ¸ÄÎª0x90.
    packet.m_body[3] = 0x08;        //0x90ÐÞ¸ÄÎª0x10.
    
    packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    packet.m_packetType = RTMP_PACKET_TYPE_AUDIO;
    packet.m_hasAbsTimestamp = 0;
    packet.m_nChannel = 0x04;
    packet.m_nTimeStamp = 0;
    packet.m_nInfoField2 = _rtmpClient->m_stream_id;
    packet.m_nBodySize = 4;
    
    int nRet = RTMP_SendPacket(_rtmpClient, &packet, TRUE);
    RTMPPacket_Free(&packet);
    return nRet;
}

- (int)setRtmpPacketSize:(uint32_t) pkt_size
{
    RTMPPacket pack;
    int nVal = pkt_size;
    RTMPPacket_Alloc(&pack, 4);
    
    pack.m_packetType = RTMP_PACKET_TYPE_CHUNK_SIZE;
    pack.m_headerType = RTMP_PACKET_SIZE_LARGE;
    pack.m_nChannel = 0x02;
    pack.m_nTimeStamp = 0;
    pack.m_nInfoField2 = 0;
    pack.m_nBodySize = 4;
    
    pack.m_body[0] = nVal >> 24;
    pack.m_body[1] = nVal >> 16;
    pack.m_body[2] = nVal >> 8;
    pack.m_body[3] = nVal & 0xff; //大字节序
    
    _rtmpClient->m_outChunkSize = nVal;
    
    int nRet = RTMP_SendPacket(_rtmpClient, &pack, TRUE);
    RTMPPacket_Free(&pack);
    
    return nRet;
}

- (BOOL)sendPacket:(uint32_t) nPacketType
          keyFrame:(BOOL) keyFrame
              data:(int8_t *) data
              size:(uint32_t) size
        nTimeStamp:(uint64_t) nTimestamp
{
    
    if (data == NULL || size == 0) {
        return NO;
    }
    
    int pkg_size = 0;
    int i = 0;
    RTMPPacket packet;
    
    if (nPacketType == RTMP_PACKET_TYPE_AUDIO)
    {
        pkg_size = size + 2;
        RTMPPacket_Reset(&packet);
        RTMPPacket_Alloc(&packet, pkg_size);
        packet.m_body[i++] = 0xAF;
        packet.m_body[i++] = 0x01;
        memcpy(&(packet.m_body[i]), data, size);
        packet.m_headerType = RTMP_PACKET_SIZE_MEDIUM;
    }
    else if (nPacketType == RTMP_PACKET_TYPE_VIDEO)
    {
        pkg_size = size + 9;
        RTMPPacket_Reset(&packet);
        RTMPPacket_Alloc(&packet, pkg_size);
        packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
        
        if (keyFrame) {
            packet.m_body[i++] = 0x17;      // 1:Iframe  7:AVC
            packet.m_body[i++] = 0x01;      // AVC NALU
            packet.m_body[i++] = 0x00;
            packet.m_body[i++] = 0x00;
            packet.m_body[i++] = 0x00;
            
            // NALU size
            packet.m_body[i++] = size >> 24 & 0xff;
            packet.m_body[i++] = size >> 16 & 0xff;
            packet.m_body[i++] = size >> 8 & 0xff;
            packet.m_body[i++] = size & 0xff;
            // NALU data
            memcpy(&packet.m_body[i], data, size);
        }
        else {
            packet.m_body[i++] = 0x27;      // 2:Pframe  7:AVC
            packet.m_body[i++] = 0x01;      // AVC NALU
            packet.m_body[i++] = 0x00;
            packet.m_body[i++] = 0x00;
            packet.m_body[i++] = 0x00;
            
            // NALU size
            packet.m_body[i++] = size >> 24 & 0xff;
            packet.m_body[i++] = size >> 16 & 0xff;
            packet.m_body[i++] = size >> 8 & 0xff;
            packet.m_body[i++] = size & 0xff;
            // NALU data
            memcpy(&packet.m_body[i], data, size);
        }
    }
    packet.m_packetType = nPacketType;
    packet.m_nChannel = 0x04;
    packet.m_nTimeStamp = nTimestamp;
    packet.m_nInfoField2 = _rtmpClient->m_stream_id;
    packet.m_nBodySize = pkg_size;
    packet.m_hasAbsTimestamp = 0;
    
    NSLog(@"start send packet,%d,%d,%d", size, nTimestamp, keyFrame);
    int nRet = RTMP_SendPacket(_rtmpClient, &packet, TRUE);
    NSLog(@"send packet ret:%d, type:%d", nRet, nPacketType);
    RTMPPacket_Free(&packet);
    return nRet;
}
@end
