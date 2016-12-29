//
//  FFMpegDecoderEnumerator.m
//  FFMpegDecoder
//
//  Created by tbago on 16/12/29.
//  Copyright © 2016年 tbago. All rights reserved.
//

#import "FFMpegDecoderEnumerator.h"
#import "FFMpegCommon.h"

#include "libavcodec/avcodec.h"

@interface FFMpegDecoderEnumerator()

@property (strong, nonatomic) NSMutableArray    *innerCodecInfoArray;

@end

@implementation FFMpegDecoderEnumerator

- (void)initDecoderArray {
    avcodec_register_all();
    AVCodec *pAVCodec = NULL;
    do {
        pAVCodec = av_codec_next(pAVCodec);
        if (pAVCodec != NULL && av_codec_is_decoder(pAVCodec) != 0)
        {
            enum AVMediaType mediaType = avcodec_get_type(pAVCodec->id);
            FFMpegDecoderType decoderType = FFMpegUnknownDecoder;
            switch (mediaType)
            {
                case AVMEDIA_TYPE_VIDEO:
                    decoderType = FFmpegVideoDecoder;
                    break;
                case AVMEDIA_TYPE_AUDIO:
                    decoderType = FFMpegAudioDecoder;
                    break;
                case AVMEDIA_TYPE_SUBTITLE:
                    decoderType = FFMpegSubtitleDecoder;
                    break;
                default:
                    break;
            }
            if (decoderType == FFMpegUnknownDecoder) {
                continue;
            }
            
            FFMpegCodecInfo *newCodecInfo = [[FFMpegCodecInfo alloc] init];
            newCodecInfo.type    = decoderType;
            newCodecInfo.codecID = FFMpegCodecIDToMeidaCodecID(pAVCodec->id);
            newCodecInfo.name    = [NSString stringWithUTF8String:pAVCodec->name];
            newCodecInfo.score   = 100;
            
            [self.innerCodecInfoArray addObject:newCodecInfo];
        }
    } while(pAVCodec != NULL);
}

- (FFMpegDecoder *)CreateFFMpegDecoderByIndex:(uint32_t) index {
    return NULL;
}

#pragma mark - get & set

- (NSMutableArray *)innerCodecInfoArray {
    if (_innerCodecInfoArray == nil) {
        _innerCodecInfoArray = [[NSMutableArray alloc] init];
    }
    return _innerCodecInfoArray;
}

- (NSArray *)codecInfoArray {
    return self.innerCodecInfoArray;
}

@end
