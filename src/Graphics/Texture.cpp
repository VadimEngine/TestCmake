#include "Texture.h"

Texture::Texture(const unsigned char* textureData, int width, int height, int channels) {
    mWidth_ = width;
    mHeight_ = height;
    mChannels_ = channels;
    mTextureId_ = genGLTexture(textureData, width, height, channels);
}

Texture::Texture(const std::string& path) {
    mTextureId_ = loadTexture(path, &mWidth_, &mHeight_, &mChannels_);
}

Texture::~Texture() {
    LOG_I("Delete Texture: %d", mTextureId_);
    glDeleteTextures(1, &mTextureId_);
}

unsigned int Texture::loadTexture(const std::string& texturePath, int* width, int* height, int* channels) {
    // TODO return option if path fails
    unsigned textureId;
    // Load image file
    unsigned char* textureData = SOIL_load_image(
        texturePath.c_str(),
        (int*)(width),
        (int*)(height),
        (int*)(channels),
        SOIL_LOAD_AUTO
    );

    if (textureData == nullptr) {
        LOG_E("ERROR LOADING TEXTURE: %s", textureData);
        const char* errorMessage = SOIL_last_result();
        if (errorMessage != nullptr) {
            LOG_E("SOIL error: %s", errorMessage)
        }
        throw std::runtime_error("Texture load failed");
    }

    textureId = genGLTexture(textureData, *width, *height, *channels);

    SOIL_free_image_data(textureData);
    return textureId;
}

unsigned int Texture::getId() {
    return mTextureId_;
}

unsigned int Texture::genGLTexture(const unsigned char* textureData, int width, int height, int channels) {
    unsigned int textureId;

    if (textureData == nullptr) {
        LOG_E("Null texture data cannot be convert to a texture");
        throw std::runtime_error("Texture build failed");
    }

    // create textures
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        (channels == 3) ? GL_RGB : GL_RGBA,
        GL_UNSIGNED_BYTE, textureData
    );
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        LOG_E("genGLTexture ERROR %d", err);

    }
    return textureId;
}
