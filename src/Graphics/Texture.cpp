#include "Texture.h"

unsigned int Texture::loadTexture(const std::string& texturePath) {
    unsigned textureId;
    int width, height;
    int channels;
    // Load image file
    unsigned char* textureData = SOIL_load_image(texturePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

    if (textureData == nullptr) {
        LOG_E("ERROR LOADING TEXTURE: %s", textureData);
        throw std::runtime_error("Shader program linking failed");
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

    SOIL_free_image_data(textureData);
    return textureId;
}