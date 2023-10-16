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
    // TODO map of loaded models?

private:
    /** Meshes this model is made up of */
    std::vector<Mesh> mMeshes_;
public:
    /** Constructor */
    Model();
    /** 
     * Add a mesh to the model
     * \param newMesh Mesh to add
     */
    void addMesh(Mesh newMesh);

    /**
     * Load and add a mesh to the model
     * \param meshPath Path to load mesh from
     */
    void loadMesh(const std::string& meshPath);

    /**
     * Draw the Model meshes
     * \param shader Shader to draw the meshes with
     */
    void render(const Shader& shader) const;

private:
    /**
     * Process a node (and child nodes recursively) in a assimp object and add to
     * \param aiNode Assimp node
     * \param aiScene Assimp scene
     */
    void processNode(aiNode *node, const aiScene *scene);
    
    /**
     * Process an Assimp Mesh and add to list of meshes
     * \param mesh Child node
     * \param scene Assimp Scene
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};