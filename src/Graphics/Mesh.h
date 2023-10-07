#pragma once
#define GLEW_STATIC
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "unordered_map"


class Mesh {
public:
    struct Vertex {
        // position
        glm::vec3 position;
        // normal
        glm::vec3 normal;
        // texCoords
        glm::vec2 texCoord;
        // tangent
        glm::vec3 tangent;
        // bitangent
        glm::vec3 bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    static std::unordered_map<std::string, Mesh> loadedMeshByName;

    static void loadMeshes();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int mVAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void render(Shader& theShader);

private:
    unsigned int mVBO_, mEBO_;

    void buildOpenGLproperties();
};