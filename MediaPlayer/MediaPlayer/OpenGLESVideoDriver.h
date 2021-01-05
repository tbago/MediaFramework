//
//  OpenGLESVideoDriver.h
//  MediaPlayer
//
//  Created by tbago on 2021/1/4.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef MEDIA_PLAYER_OPENGLES_VIDEO_DRIVER_H_
#define MEDIA_PLAYER_OPENGLES_VIDEO_DRIVER_H_

#include <MediaPlayer/IVideoDriver.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>

namespace media_player {

class OpenGLESVideoDriver : public IVideoDriver
{
public:
    virtual void Free();
    virtual bool Init();
    virtual void SetDestRect(const TRect &destRect);
    virtual bool Begin();
    virtual bool FillRect(const TRect &destRect, const TColor &fillColor);
    virtual bool DrawImage(media_base::RawVideoFrame * videoFrame, const TRect &srcRect, const TRect &destRect);
    virtual bool End();
public:
    OpenGLESVideoDriver(void * uiView, int32_t screenScale);
    virtual ~OpenGLESVideoDriver();
private:
    int8_t * BuildFrameData(media_base::RawVideoFrame *videoFrame);
    bool SetupYUVTexture();
    bool LoadShader();
    GLuint CompileShader(const char * shaderString, GLenum shaderType);
    bool CreateFrameAndRenderBuffer();
    void DestoryFrameAndRenderBuffer();
    void SetVideoSize(GLuint width, GLuint height);
private:
    TRect       _destRect;
    void        *_uiView;
    GLsizei     _viewScale;
    int8_t      *_frameData;     ///< frame data
    int32_t     _videoWidth;
    int32_t     _videoHeight;
private:
    EAGLContext *_glContext;     ///<  OpenGL context
    GLuint      _textureYUV[3]; ///<  YUV texture array
    GLuint      _program;       ///<  shader handle
    GLuint      _framebuffer;   ///<  frame buffer
    GLuint      _renderBuffer;  ///< render buffer
};

}   // namespace media_player
#endif  // MEDIA_PLAYER_OPENGLES_VIDEO_DRIVER_H_

