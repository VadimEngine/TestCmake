#pragma once
#include "Scene.h"
#include "MenuGUI.h"

// Forward Declare App
class App;

class MenuScene : public Scene {
private:
    /** GUI for this scene*/
    MenuGUI mGui_;
public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    MenuScene(App& theApp);

    /** Destructor */
    ~MenuScene();
    
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