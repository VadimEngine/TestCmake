#pragma once
#include "Scene.h"
#include "CameraController.h"
#include "GalaxySceneGUI.h"
#include "Entity.h"
#include "ModelRenderable.h"
#include "SunEntity.h"
#include "PlanetEntity.h"
#include "MoonEntity.h"
#include "Resource.h"

// Forward Declare App
class App;

namespace galaxy {

class GalaxyScene : public Scene {
private:
    /** GUI for this scene*/
    GalaxySceneGUI mGui_;
    /** Camera Controller */
    CameraController mCameraController_;

    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;

    SunEntity* sunEntity_ = nullptr;
    PlanetEntity* planetEntity_ = nullptr;
    MoonEntity* moonEntity_ = nullptr;

    float sunRadius = 1.0f;
    float planetRadius = 0.5f;
    float moonRadius = .25f;

    float planetOrbitRadius = 5.f;

public:
    /**  
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    GalaxyScene(App& theApp);
    
    /** Destructor */
    ~GalaxyScene();

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

    SunEntity* getSunEntity();
    PlanetEntity* getPlanetEntity();
    MoonEntity* getMoonEntity();

    Resource& getResources();

     void onMouseWheel(const InputHandler::MouseEvent& mouseEvent) override;

};

} // namespace galaxy