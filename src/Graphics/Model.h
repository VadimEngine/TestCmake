#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Logger.h"
#include <filesystem>

class Model {
private:
    /** Meshes this model is made up of and owns*/
    std::vector<Mesh> mMeshes_;
    /** Meshes owned by another object (likely Resource) and can be shared between mutiple objects */
    std::vector<Mesh*> mSharedMeshes_;

public:
    /** Constructor */
    Model();

    /** Destructor */
    ~Model();

    /** 
     * Add a mesh to the model
     * @param newMesh Mesh to add
     */
    void addMesh(const Mesh& newMesh);

    void addSharedMesh(Mesh* newMesh);

    void addMeshes(std::vector<Mesh>&& meshes);

    /**
     * Load and add a mesh to the model
     * @param meshPath Path to load mesh from
     */
    void loadMesh(const std::filesystem::path& meshPath);

    /**
     * Draw the Model meshes
     * @param shader Shader to render the meshes with
     */
    void render(const Shader& shader) const;
};