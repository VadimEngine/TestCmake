#pragma once
// project
#include "BasicSceneGUI.h"
#include "CameraController.h"
#include "ModelRenderable.h"
#include "Scene.h"
#include "Shader.h"
#include "SpriteRenderable.h"
#include "TextRenderable.h"
#include "Texture.h"

// Forward Declare App
class App;

namespace basic_scene {
    class BasicScene : public Scene {
    public:
        /**
         * Constructor
         * @param theApp Parent app handling this Scene
         */
        BasicScene(App& theApp);

        /** Destructor */
        ~BasicScene();

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
        BasicSceneGUI mGui_;
        /** Entities rendered in this Scene */
        std::vector<std::unique_ptr<Entity>> mEntities_;
        /** First Sprite used in this Scene*/
        SpriteSheet::Sprite mSprite_;
    };
} // namespace basic_scene