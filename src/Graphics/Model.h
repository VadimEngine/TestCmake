#pragma once
#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include <string>

class Model {
public:
struct AttribDetail {
    GLint elements;
    GLenum type;
    GLboolean normalized;
};
public:
    // TODO have the loaded models store more info like elementsPerVetex and attributes
    static std::unordered_map <std::string, std::vector<float>> loadedModelsByName;

    static void loadModels();

    std::vector<float> mVerticies_;

    unsigned int mElementsPerVertex_ = 0;

    const std::vector<AttribDetail>& attribs;

};