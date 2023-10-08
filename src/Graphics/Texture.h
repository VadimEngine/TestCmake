#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <unordered_map>
#include <SOIL.h>
#include <stdexcept>
#include "Logger.h"

class Texture {
public:
    static unsigned int loadTexture(const std::string& texturePath);
};