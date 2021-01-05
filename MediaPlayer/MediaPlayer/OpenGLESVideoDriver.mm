//
//  OpenGLESVideoDriver.mm
//  MediaPlayer
//
//  Created by tbago on 2021/1/4.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "OpenGLESVideoDriver.h"
#import <UIKit/UIKit.h>

namespace media_player {

#define FSH "varying lowp vec2 TexCoordOut;\
\
uniform sampler2D SamplerY;\
uniform sampler2D SamplerU;\
uniform sampler2D SamplerV;\
\
void main(void)\
{\
mediump vec3 yuv;\
lowp vec3 rgb;\
\
yuv.x = texture2D(SamplerY, TexCoordOut).r;\
yuv.y = texture2D(SamplerU, TexCoordOut).r - 0.5;\
yuv.z = texture2D(SamplerV, TexCoordOut).r - 0.5;\
\
rgb = mat3( 1,       1,         1,\
0,       -0.39465,  2.03211,\
1.13983, -0.58060,  0) * yuv;\
\
gl_FragColor = vec4(rgb, 1);\
\
}"

#define VSH "attribute vec4 position;\
attribute vec2 TexCoordIn;\
varying vec2 TexCoordOut;\
\
void main(void)\
{\
gl_Position = position;\
TexCoordOut = TexCoordIn;\
}"

typedef enum
{
    TEXY = 0,
    TEXU,
    TEXV,
    TEXC
} TextureType;

enum AttribEnum
{
    ATTRIB_VERTEX,
    ATTRIB_TEXTURE,
    ATTRIB_COLOR,
};

void OpenGLESVideoDriver::Free() {
    delete this;
}

bool OpenGLESVideoDriver::Init() {
    UIView *pView = (__bridge UIView *)_uiView;

    CAEAGLLayer *eaglLayer = (CAEAGLLayer*)pView.layer;

    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking,
                                    kEAGLColorFormatRGB565, kEAGLDrawablePropertyColorFormat,
                                    nil];
    pView.contentScaleFactor = _viewScale;

    _glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!_glContext || ![EAGLContext setCurrentContext:_glContext]) {
        GLenum error = glGetError();
        printf("set context failed: %d\n", error);
        return false;
    }

    if (!SetupYUVTexture()) {
        return false;
    }
    if (!LoadShader()) {
        return false;
    }
    glUseProgram(_program);

    GLuint textureUniformY = glGetUniformLocation(_program, "SamplerY");
    GLuint textureUniformU = glGetUniformLocation(_program, "SamplerU");
    GLuint textureUniformV = glGetUniformLocation(_program, "SamplerV");
    glUniform1i(textureUniformY, 0);
    glUniform1i(textureUniformU, 1);
    glUniform1i(textureUniformV, 2);

    _videoWidth = 0;
    _videoHeight = 0;
    return true;
}

void OpenGLESVideoDriver::SetDestRect(const TRect &destRect) {
    _destRect = destRect;

    [EAGLContext setCurrentContext:_glContext];
    DestoryFrameAndRenderBuffer();
    CreateFrameAndRenderBuffer();

    glViewport(1, 1, _destRect.width*_viewScale - 2, _destRect.height*_viewScale - 2);
}

bool OpenGLESVideoDriver::Begin() {
    return true;
}

bool OpenGLESVideoDriver::FillRect(const TRect &destRect, const TColor &fillColor) {
    //TODO: (anxs) not implement only draw black
    int32_t width = destRect.width;
    int32_t height = destRect.height;
    int8_t *blackData = (int8_t*)malloc(width * height * 1.5);
    memset(blackData, 0x0, width * height * 1.5);

    [EAGLContext setCurrentContext:_glContext];
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXY]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width, height, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXU]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG_EXT, width/2, height/2, 0, GL_RG_EXT, GL_UNSIGNED_BYTE, blackData + width * height);

    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXU]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width/2, height/2, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData + width * height);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXV]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width/2, height/2, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData + width * height * 5 / 4);
    free(blackData);
    return true;
}

bool OpenGLESVideoDriver::DrawImage(media_base::RawVideoFrame *videoFrame, const TRect &srcRect, const TRect &destRect) {
    GLsizei width = videoFrame->width;
    GLsizei height = videoFrame->height;
    if (width != _videoWidth || height != _videoHeight)
    {
        SetVideoSize(width, height);
    }
    int8_t *data  = BuildFrameData(videoFrame);
    [EAGLContext setCurrentContext:_glContext];
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXY]);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_EXT, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXU]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width/2, height/2, GL_RED_EXT, GL_UNSIGNED_BYTE, data + width * height);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXV]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width/2, height/2, GL_RED_EXT, GL_UNSIGNED_BYTE, data + width * height * 5 / 4);

    [EAGLContext setCurrentContext:_glContext];
    glViewport(1, 1, destRect.width * _viewScale -2, destRect.height * _viewScale - 2);

    static const GLfloat squareVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };


    static const GLfloat coordVertices[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
    };

    // Update attribute values
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
    glEnableVertexAttribArray(ATTRIB_VERTEX);

    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, 0, 0, coordVertices);
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    // Draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    [_glContext presentRenderbuffer:GL_RENDERBUFFER];
    return true;
}

bool OpenGLESVideoDriver::End() {
    return true;
}

OpenGLESVideoDriver::OpenGLESVideoDriver(void * uiView, int32_t screenScale) {
    _uiView = uiView;
    _viewScale = screenScale;
    _frameData = NULL;
}

OpenGLESVideoDriver::~OpenGLESVideoDriver() {
    if (_frameData != NULL) {
        free(_frameData);
        _frameData = NULL;
    }
    DestoryFrameAndRenderBuffer();
}

int8_t * OpenGLESVideoDriver::BuildFrameData(media_base::RawVideoFrame *videoFrame) {
    //TODO: (anxs) not support width height change
    if (_frameData == NULL) {
        uint32_t bufferSize = videoFrame->width * videoFrame->height * 3 / 2 + 1;
        _frameData = (int8_t *)malloc(bufferSize);
    }

    uint32_t bufferIndex = 0;
    ///< copy y data
    media_base::RawVideoFrameBuffer *yFrameBuffer = videoFrame->frameBufferVector[0];
    uint32_t lineSizeY = yFrameBuffer->lineSize;
    int8_t *yBuffer = yFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height; i++) {
        memcpy(_frameData + bufferIndex, yBuffer + i * lineSizeY, videoFrame->width);
        bufferIndex += videoFrame->width;
    }

    ///< copy u data
    media_base::RawVideoFrameBuffer *uFrameBuffer = videoFrame->frameBufferVector[1];
    uint32_t lineSizeU = uFrameBuffer->lineSize;
    int8_t *uBuffer = uFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height/2; i++) {
        memcpy(_frameData + bufferIndex, uBuffer + i * lineSizeU, videoFrame->width/2);
        bufferIndex += videoFrame->width/2;
    }
    ///< copy v data
    media_base::RawVideoFrameBuffer *vFrameBuffer = videoFrame->frameBufferVector[2];
    uint32_t lineSizeV = vFrameBuffer->lineSize;
    int8_t *vBuffer = vFrameBuffer->frameData;
    for (uint32_t i = 0; i< videoFrame->height/2; i++) {
        memcpy(_frameData + bufferIndex, vBuffer + i * lineSizeV, videoFrame->width/2);
        bufferIndex += videoFrame->width/2;
    }
    return _frameData;
}

bool OpenGLESVideoDriver::SetupYUVTexture() {
    if (_textureYUV[TEXY])
    {
        glDeleteTextures(3, _textureYUV);
    }
    glGenTextures(3, _textureYUV);
    if (!_textureYUV[TEXY] || !_textureYUV[TEXU] || !_textureYUV[TEXV])
    {
        printf("create texture failed");
        return false;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXY]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXU]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXV]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return true;
}

bool OpenGLESVideoDriver::LoadShader() {
    /**
     1
     */
    GLuint vertexShader = CompileShader(VSH, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(FSH, GL_FRAGMENT_SHADER);

    /**
     2
     */
    _program = glCreateProgram();
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    /**
     * bind before link
     */
    glBindAttribLocation(_program, ATTRIB_VERTEX, "position");
    glBindAttribLocation(_program, ATTRIB_TEXTURE, "TexCoordIn");

    glLinkProgram(_program);

    /**
     3
     */
    GLint linkSuccess;
    glGetProgramiv(_program, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(_program, sizeof(messages), 0, &messages[0]);
        printf("shader link failed:%s", messages);
        return false;
    }

    if (vertexShader)
        glDeleteShader(vertexShader);
    if (fragmentShader)
        glDeleteShader(fragmentShader);
    return true;
}

GLuint OpenGLESVideoDriver::CompileShader(const char * shaderString, GLenum shaderType) {
    /**
     1
     */
    if (!shaderString) {
        printf("Error loading shader");
        return -1;
    }

    /**
     2
     */
    GLuint shaderHandle = glCreateShader(shaderType);

    /**
     3
     */
    GLint shaderStringLength = (GLint)strlen(shaderString);
    glShaderSource(shaderHandle, 1, &shaderString, &shaderStringLength);

    /**
     4
     */
    glCompileShader(shaderHandle);

    /**
     5
     */
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        printf("%s", messages);
        return -1;
    }

    return shaderHandle;
}

bool OpenGLESVideoDriver::CreateFrameAndRenderBuffer() {
    glGenFramebuffers(1, &_framebuffer);
    glGenRenderbuffers(1, &_renderBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);

    UIView *pView = (__bridge UIView *)_uiView;
    CAEAGLLayer *eaglLayer = (CAEAGLLayer*)pView.layer;
    if (![_glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)eaglLayer])
    {
        printf("attach render buffer failed");
        return false;
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _renderBuffer);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Create buffer failed 0x%x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        return false;
    }
    return true;
}

void OpenGLESVideoDriver::DestoryFrameAndRenderBuffer() {
    if (_framebuffer) {
        glDeleteFramebuffers(1, &_framebuffer);
    }

    if (_renderBuffer) {
        glDeleteRenderbuffers(1, &_renderBuffer);
    }

    _framebuffer = 0;
    _renderBuffer = 0;
}

void OpenGLESVideoDriver::SetVideoSize(GLuint width, GLuint height) {
    _videoWidth = width;
    _videoHeight = height;

    int8_t *blackData = (int8_t*)malloc(width * height * 1.5);
    if(blackData) {
        memset(blackData, 0x0, width * height * 1.5);
    }

    [EAGLContext setCurrentContext:_glContext];
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXY]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width, height, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData);
    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXU]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width/2, height/2, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData + width * height);

    glBindTexture(GL_TEXTURE_2D, _textureYUV[TEXV]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED_EXT, width/2, height/2, 0, GL_RED_EXT, GL_UNSIGNED_BYTE, blackData + width * height * 5 / 4);
    free(blackData);
}
}   // namespace media_player

