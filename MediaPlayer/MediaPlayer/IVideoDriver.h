//
//  IVideoDriver.h
//  MediaPlayer
//
//  Created by tbago on 2021/1/3.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_PLAYER_I_VIDEO_DRIVER_H_
#define MEDIA_PLAYER_I_VIDEO_DRIVER_H_

#include "MediaBase/RawVideoFrame.h"

namespace media_player
{

typedef enum
{
    DriverTypeNone,
    DriverTypeOpenGLES,

}VideoDriverType;

typedef struct
{
    void                             *videoWindow;   ///< driver container, for iOS we use NSView, for windows use Hwnd
    media_base::ResuablePixelFormat     pixelFormat;    ///< driver pixel format
    VideoDriverType                   driverType;     ///< driver type
    int32_t                          screenScale;   ///< screen scale
    int32_t                          reserve;       ///< reserved for future use
} VideoDriverConfig;

///< Rect and color are very common name, so I add T prefix.
///<  player special rect struct
typedef struct
{
    int32_t left;
    int32_t top;
    int32_t width;
    int32_t height;
} TRect;

///< player special color struct
typedef struct
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} TColor;

class IVideoDriver {
public:
    /*!
    @brief free current object
    */
    virtual void Free() = 0;
    /*!
    @brief set dest rect size
    @param destRect dest rect size
    @note use as memory cache
    */
    virtual void SetDestRect(const TRect &destRect) = 0;
    /*!
    @brief Begin for render
    */
    virtual bool Begin() = 0;
    /*!
    @brief Fill dest rect with speical color
    @param destRect dest rect
    @param fillColor fill color
    */
    virtual bool FillRect(const TRect &destRect, const TColor &fillColor) = 0;
    /*!
    @brief draw one frame
    @param videoFrame the source video frame
    @param srcRect the source video special rect, NULL for all rect
    @param destRect the dest draw rect
    */
    virtual bool DrawImage(media_base::RawVideoFrame * videoFrame, const TRect &srcRect, const TRect &destRect) = 0;
    /*!
    @brief end draw, it is useful for double  buffering draw
    */
    virtual bool End() = 0;
};

IVideoDriver* CreateVideoDriver(VideoDriverConfig & videoDriverConfig);

}   //namespace media_player
#endif  // MEDIA_PLAYER_I_VIDEO_DRIVER_H_

