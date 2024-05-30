#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"
#include "Texture.h"
#include "GamesSceneGUI.h"
#include "Entity.h"
#include "ModelRenderable.h"
#include "SpriteRenderable.h"

// Forward Declare App
class App;

class GamesScene : public Scene {
private:
    /** GUI for this Scene*/
    GamesSceneGUI mGui_;

public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    GamesScene(App& theApp);

    /** Destructor */
    ~GamesScene();

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
};