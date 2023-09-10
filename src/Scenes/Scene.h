#pragma once
#define GLEW_STATIC
#include <GL/glew.h>


class Scene {
public:
    Scene() = default;

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