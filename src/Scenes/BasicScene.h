#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"
#include "Texture.h"
#include "BasicSceneGUI.h"
#include "Entity.h"
#include "ModelRenderable.h"
#include "SpriteRenderable.h"

// Forward Declare App
class App;

class BasicScene : public Scene {
private:
    /** Camera Controller */
    CameraController mCameraController_;

    /** GUI for this Scene*/
    BasicSceneGUI mGui_;

    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;
public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    BasicScene(App& theApp);

    /** Destructor */
    ~BasicScene();

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