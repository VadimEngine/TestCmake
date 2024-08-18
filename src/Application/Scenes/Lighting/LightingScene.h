#pragma once
// project
#include "CameraController.h"
#include "LightEntity.h"
#include "LightSource.h"
#include "LightingSceneGUI.h"
#include "Scene.h"

// Forward Declare App
class App;

namespace lighting_scene {
    class LightingScene : public Scene {
    public:
        /**
         * Constructor
         * @param theApp Parent app handling this Scene
         */
        LightingScene(App& theApp);

        /** Destructor */
        ~LightingScene();

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

        /**
         * @brief Loads and builds resources that are used for this scene
         */
        void assembleResources() override;

        /** Get the entities in this scene*/
        std::vector<std::unique_ptr<Entity>>& getEntities();

    private:
        /** Camera Controller */
        CameraController mCameraController_;
        /** GUI for this Scene*/
        LightingSceneGUI mGui_;

        // reference to the light entity in this scene
        LightEntity* mpLight_;

        /** Entities rendered in this Scene */
        std::vector<std::unique_ptr<Entity>> mEntities_;
    };
} // namespace lighting_scene