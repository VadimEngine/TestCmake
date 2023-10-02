#include "Mesh.h"

std::unordered_map<std::string, Mesh> Mesh::loadedMeshByName;

void Mesh::loadMeshes() {
    // TODO make these const?
    loadedMeshByName.emplace("Cube", Mesh(
        std::vector<Vertex>{
            {{ -1.f, -1.f, 1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //0
            {{ 1.f, -1.f, 1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //1
            {{ 1.f, 1.f, 1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //2
            {{ -1.f, 1.f, 1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //3

            {{ -1.f, -1.f, -1.f},{0,0,0},{0,0},{-1,0,0},{0,0,0}}, //4
            {{ 1.f, -1.f, -1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //5
            {{ 1.f, 1.f, -1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //6
            {{ -1.f, 1.f, -1.f},{0,0,0},{0,0},{0,0,0},{0,0,0}}, //7

        },
        std::vector<unsigned int>{
            4,5,6,
            6,7,4,
            0,1,3,
            2,3,0,
            3,7,4,
            4,0,3,
            2,6,5,
            5,1,2,
            4,5,1,
            1,0,4,
            7,6,2,
            2,3,7
        }
    ));

    loadedMeshByName.emplace("Cube2", Mesh(
        std::vector<Vertex>{
            {{-1.f, -1.f, -1.0f}, {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f, -1.f}, {0.0f,  0.0f, -1.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, -1.f}, {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, -1.f}, {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f, -1.f}, {0.0f,  0.0f, -1.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f, -1.f}, {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},

            {{-1.f, -1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f,  1.f},  {0.0f,  0.0f,  1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},

            {{-1.f,  1.f,  1.f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f, -1.f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f, -1.f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f, -1.f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f,  1.f}, {-1.0f,  0.0f,  0.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f,  1.f}, {-1.0f,  0.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},

            {{1.f,  1.f,  1.f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, -1.f},  {1.0f,  0.0f,  0.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f, -1.f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f, -1.f},  {1.0f,  0.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f,  1.f},  {1.0f,  0.0f,  0.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f,  1.f},  {1.0f,  0.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},

            {{-1.f, -1.f, -1.f},  {0.0f, -1.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f, -1.f},  {0.0f, -1.0f,  0.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f,  1.f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f,  1.f},  {0.0f, -1.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f,  1.f},  {0.0f, -1.0f,  0.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f, -1.f},  {0.0f, -1.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},

            {{-1.f,  1.f, -1.f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, -1.f},  {0.0f,  1.0f,  0.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f,  1.f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f,  1.f},  {0.0f,  1.0f,  0.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f,  1.f},  {0.0f,  1.0f,  0.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f, -1.f},  {0.0f,  1.0f,  0.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}}
        },
        std::vector<unsigned int>{
            0,1,2,
            3,4,5,
            6,7,8,
            9,10,11,
            12,13,14,
            15,16,17,
            18,19,20,
            21,22,23,
            24,25,26,
            27,28,29,
            30,31,32,
            33,34,35
        }
    ));
    loadedMeshByName.emplace("Plane", Mesh(
        std::vector<Vertex>{
            {{-1.f, -1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f, -1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {1.0f,  0.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{1.f,  1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {1.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f,  1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {0.0f,  1.0f},{0,0,0},{0,0,0}},
            {{-1.f, -1.f, 0.0f}, {0.0f,  0.0f, -1.0f},  {0.0f,  0.0f},{0,0,0},{0,0,0}},
        },
        std::vector<unsigned int>{
            0,1,2,
            3,4,5,
        }
    ));
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;
    buildOpenGLproperties();
}

void Mesh::render(Shader& theShader) {
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::buildOpenGLproperties() {
     // create buffers/arrays
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO_);
    glGenBuffers(1, &mEBO_);

    glBindVertexArray(mVAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}
