// class
#include "Utils.h"

namespace utils {
    size_t Vec2Hash::operator()(const glm::ivec2& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }

    void saveTextureAsBMP(GLuint textureID, const std::filesystem::path& filepath) {
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        // Get the texture width, height, and internal format
        int width, height, internalFormat;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

        // Determine the format and the number of channels
        GLenum format;
        int channels;
        if (internalFormat == GL_RGB || internalFormat == GL_SRGB) {
            format = GL_RGB;
            channels = 3;
        } else if (internalFormat == GL_RGBA || internalFormat == GL_SRGB_ALPHA) {
            format = GL_RGBA;
            channels = 4;
        } else {
            // Handle other formats if necessary
            LOG_E("Unsupported texture format: %d", internalFormat);
            glBindTexture(GL_TEXTURE_2D, 0);
            return;
        }

        // Allocate memory to hold the texture data
        std::vector<unsigned char> textureData(width * height * channels);
        // Download the texture data
        glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, textureData.data());
        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Save the texture data as a BMP file using SOIL
        int saveResult = SOIL_save_image(
            filepath.string().c_str(),
            SOIL_SAVE_TYPE_BMP,
            width, height, channels,
            textureData.data()
        );
    }

} // namespace utils
