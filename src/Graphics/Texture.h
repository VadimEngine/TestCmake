#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL.h>
#include <stdexcept>
#include "Logger.h"
#include <optional>
#include <vector>

class Texture {
private:
    unsigned int mTextureId_;
    //TODO hold texture properties such as rgb/rgba/with,height
    int mWidth_;
    int mHeight_;
    int mChannels_;

public:
    Texture(const unsigned char* textureData, int width, int height, int channels);

    // TODO use path
    explicit Texture(const std::string& path);

    ~Texture();

    // TODO use path
    /** Load a texture from a file and return the OpenGL Texture Id */
    static unsigned int loadTexture(const std::string& texturePath, int* width, int* height, int* channels);

    unsigned int getId();

    unsigned int getWidth();

    unsigned int getHeight();

    unsigned int getChannels();

private:
    static unsigned int genGLTexture(const unsigned char* textureData, int width, int height, int channels);
};