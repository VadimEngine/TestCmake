#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Logger.h"

class Model {
public:
    std::vector<Mesh> mMeshes_;

    Model();

    void addMesh(Mesh newMesh);

    void loadMesh(std::string meshPath);

    void render(Shader& shader);

private:
    void processNode(aiNode *node, const aiScene *scene);
    
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};