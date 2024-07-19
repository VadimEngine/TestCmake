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

    /** Get the Sun Entity of this scene*/
    SunEntity* getSunEntity();
    /** Get the Planet Entity of this scene */
    PlanetEntity* getPlanetEntity();
    /** Get the Moon Entity of this scene */
    MoonEntity* getMoonEntity();

    /** Build/load the resources for this scene*/
    void assembleResources() override;

    /** Get this scene resources */
    Resource& getResources();

    /**
     * @brief Respond to mouse wheel events
     *
     * @param mouseEvent Mouse Wheel event
     */
    void onMouseWheel(const InputHandler::MouseEvent& mouseEvent) override;

private:
    /** GUI for this scene*/
    GalaxySceneGUI mGui_;
    /** Camera Controller */
    CameraController mCameraController_;
    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;
    /** Pointer to the Sun Entity of this Scene */
    SunEntity* sunEntity_ = nullptr;
    /** Pointer to the planet Entity of this Scene*/
    PlanetEntity* planetEntity_ = nullptr;
    /** Pointer to the moon Entity of this Scene*/
    MoonEntity* moonEntity_ = nullptr;
};

} // namespace galaxy