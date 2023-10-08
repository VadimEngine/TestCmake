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
    App* mpApp_;
    Camera* mFocusCamera_;
    glm::vec4 mBackgroundColor_ = {0.0f, 0.0f, 0.0f, 1.0f};

public:
    Scene(App* theApp, glm::vec3 cameraPosition = {0,0,0} );

    virtual ~Scene() = default;
    /**
     * Update scene content
     * 
     * \param dt time since last update
     */
    virtual void update(const float dt) = 0;
    /**
     * Draw this scene
     */
    virtual void render(Renderer& renderer) = 0;

    void setBackgroundColor(glm::vec4 newColor);

    glm::vec4 getBackgroundColor() const;

    App* getApp();

    Camera* getFocusCamera();

};