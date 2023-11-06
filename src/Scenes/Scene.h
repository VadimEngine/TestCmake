#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Renderer.h"
#include <glm/vec4.hpp>

// Forward declare App
class App;

class Scene {
protected:
    /** Parent app handling this Scene*/
    App& mApp_;
    /** The current focused camera the scene is rendered through*/
    Camera* mpFocusCamera_;
    /** Background color when rendering this scene */
    glm::vec4 mBackgroundColor_ = {0.0f, 0.0f, 0.0f, 1.0f};
    /** If this scene should be deleted */
    bool mIsRemove_ = false;

public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    Scene(App& theApp);

    /** Destructor */
    virtual ~Scene() = default;
    
    /**
     * Update scene content
     * \param dt time since last update in seconds
     */
    virtual void update(const float dt) = 0;
    
    /**
     * Render this scene
     * \param renderer Rendering helper
     */
    virtual void render(Renderer& renderer) = 0;

    /**
     * Set the Scene background color
     * \param newColor background color
     */
    void setBackgroundColor(glm::vec4 newColor);

    /**
     * Get this Scene background color 
     */
    glm::vec4 getBackgroundColor() const;

    /** Get this Scene's parent App */
    App& getApp();

    /** Get the current focused Camera */
    Camera* getFocusCamera();

    /** Set this Scene to be deleted */
    void setRemove(const bool remove);

    /** If this scene is set for removal */
    bool isRemove() const;

    /** 
     * On keyboard key press handler
     * \param code key code for pressed key
     */
    virtual void onKeyPress(unsigned int code);

    /** 
     * On keyboard key release handler
     * \param code key code for released key
     */
    virtual void onKeyRelease(unsigned int code);
};