#pragma once
#include "Scene.h"
#include "Entity.h"
#include "PongSceneGUI.h"

// Forward Declare App
class App;

class PongScene : public Scene {
private:
        /** GUI for this Scene*/
    PongSceneGUI mGui_;

    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;
public:


    PongScene(App& theApp);

    ~PongScene();

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

    /** get the entities in this scene*/
    std::vector<Entity*>& getEntities();

};