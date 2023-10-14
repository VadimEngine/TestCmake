#pragma once
#include "IRenderable.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
#include <utility>

class Entity {
private:
    /** List of all rendering components*/
    std::vector<IRenderable*> mRenderableComponents_;

    /** Entity Position */
    glm::vec3 mPosition_ = {0.0f, 0.0f, 0.0f};
    
    /** Entity Rotation */
    glm::vec3 mRotation_ = { 0.0f, 0.0f, 0.0f };
    
    /** Entity Scale */
    glm::vec3 mScale_ = { 1.0f, 1.0f, 1.0f };
public:

    /** Constructor */
    Entity();

    /** Destructor */
    ~Entity();

    /** Update this Entity*/
    void update(float dt);

    /**
     * Render all renderable components of this Entity
     * \param theRenderer Helping Object for rendering
     * \param theCamera Camera to render relative to
     */
    void render(Renderer& theRenderer, Camera& theCamera);

    /** Get the list of renderable component */
    std::vector<IRenderable*>& getRenderableComponents();

    /** Get this Entity's position */
    glm::vec3 getPosition() const;

    /** Get this Entity's rotation */
    glm::vec3 getRotation() const;

    /** Get this Entity's scale */
    glm::vec3 getScale() const;

    /**
     * Add a Renderable for this Entity
     * \param newPosition New position vector
     */
    void addRenderable(IRenderable* newRenderable); 

    /**
     * Set this Entity's position
     * \param newPosition New position vector
     */
    void setPosition(const glm::vec3& newPosition);

    /**
     * Set this Entity's rotation
     * \param newRotation New position vector
     */
    void setRotation(const glm::vec3& newRotation);

    /**
     * Set this Entity's scale
     * \param newScale New scale vector
     */
    void setScale(const glm::vec3& newScale);
};