#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

class App;

class Scene {
protected:
    App* mpApp_;
public:
    Scene(App* theApp);

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
    virtual void render() = 0;

};