#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene.h"
#include "Camera.h"
#include "CameraController.h"
#include "AssimpGUI.h"
#include "Mesh.h"
#include "Model.h"
#include "Entity.h"
#include "ModelRenderable.h"

// Forward Declare App
class App;

class AssimpScene : public Scene {
private:
    /** The shader to draw the model in this scene */
    Shader* mpShader_ = nullptr;

    /** Assimp model in this Scene*/
    Model mModel_;

    /** Camera Controller */
    CameraController mCameraController_;
    
    /** GUI for this Scene*/
    AssimpGUI mGui_;
    
    /** Entities this Scene is Rendering*/
    std::vector<Entity*> mEntities_;

public:
    /**
     * Constructor
     * \param theApp The App holding this Scene
     */
    AssimpScene(App& theApp);

    /** Destructor */
    ~AssimpScene();

    /** 
     * Update the Scene
     * \param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * \param renderer Rendering helper
     */
    void render(Renderer& renderer) override;

    std::vector<Entity*>& getEntities();
};