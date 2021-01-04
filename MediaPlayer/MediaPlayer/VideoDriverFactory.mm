//
//  VideoDriverFactory.mm
//  MediaPlayer
//
//  Created by tbago on 2021/1/4.
//  Copyright © 2021 tbago. All rights reserved.
//

#include <MediaPlayer/IVideoDriver.h>
#include "OpenGLESVideoDriver.h"

namespace media_player {

IVideoDriver* CreateVideoDriver(VideoDriverConfig & videoDriverConfig) {
    if (videoDriverConfig.driverType == DriverTypeOpenGLES) {
        OpenGLESVideoDriver *openglVideoDriver = new OpenGLESVideoDriver(videoDriverConfig.videoWindow, videoDriverConfig.screenScale);
        return openglVideoDriver;
    }
    assert(false);
}

}   // namespace media_player
