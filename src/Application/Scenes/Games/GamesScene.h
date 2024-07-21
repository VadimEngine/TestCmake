#pragma once
// project
#include "CameraController.h"
#include "Entity.h"
#include "GamesSceneGUI.h"
#include "ModelRenderable.h"
#include "Scene.h"
#include "Shader.h"
#include "SpriteRenderable.h"
#include "Texture.h"

// Forward Declare App
class App;

class GamesScene : public Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    GamesScene(App& theApp);

    /** Destructor */
    ~GamesScene();

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(Renderer& renderer) override;

private:
    /** GUI for this Scene*/
    GamesSceneGUI mGui_;
};