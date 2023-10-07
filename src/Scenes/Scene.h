#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Renderer.h"

class App;

class Scene {
protected:
    App* mpApp_;
    Camera* mFocusCamera_;
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

    App* getApp();

    Camera* getFocusCamera();

};