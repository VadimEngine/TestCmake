#pragma once
#define GLEW_STATIC
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "unordered_map"
#include <optional>

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
private:
    /** Map to hold loaded Meshes */
    static std::unordered_map<std::string, const Mesh> sLoadedMeshByName_;

public:
    /** Load the preset list of Meshes */
    static void loadMeshes();
    
    /** 
     * Get a loaded mesh if it exists
     * \param meshName Name of the loaded mesh
     */
    static const std::optional<Mesh> getLoadedMesh(const std::string& meshName);

    /** Vertices of this mesh */
    std::vector<Vertex> vertices;
    /** Order to draw the vertices in*/
    std::vector<unsigned int> indices;
    /** Textures TODO use this*/
    std::vector<Texture> textures;
    /** Vertex Array Object for this mesh */
    unsigned int mVAO;

    /**
     * Constructor
     * \param vertices Vertices for this Mesh
     * \param indices Render order of the vertices
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    /**
     * Render the mesh with the given shader. TODO use textures
     * \param theShader Shader that will be used to draw. Textures will be bound to the shader before rendering
     */
    void render(Shader& theShader);

private:
    /** Vertex Buffer Object and Element Buffer Object for this Mesh*/
    unsigned int mVBO_, mEBO_;

    /** Initializes the Opengl properties for this mesh*/
    void buildOpenGLproperties();
};