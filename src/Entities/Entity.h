#pragma once
#include "BaseRenderable.h"
#include "PhysicsComponentBase.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
#include <utility>
#include <unordered_map>
#include "RigidBodyComponent.h"
#include "Collider2.h"

class Entity {
protected:
    /** List of all rendering components*/
    std::vector<BaseRenderable*> mRenderableComponents_;

    Collider2* mCollider_ = nullptr;

    /** Entity Position */
    glm::vec3 mPosition_ = {0.0f, 0.0f, 0.0f};
    
    /** Entity Rotation */
    glm::vec3 mRotation_ = { 0.0f, 0.0f, 0.0f };
    
    /** Entity Scale */
    glm::vec3 mScale_ = { 1.0f, 1.0f, 1.0f };

    /** Velocity*/
    glm::vec3 mVelocity_ = {0.0f, 0.0f, 0.0f};

    /** Physics components attached to this Entity*/
    std::unordered_map<PhysicsComponentBase::ComponentType, PhysicsComponentBase*> mPhysicsComponents_;

public:
    /** Constructor */
    Entity();

    /** Destructor */
    virtual ~Entity();

    /** Update this Entity*/
    virtual void update(float dt);

    /**
     * Render all renderable components of this Entity
     * \param theRenderer Helping Object for rendering
     * \param theCamera Camera to render relative to
     */
    virtual void render(const Renderer& theRenderer, const Camera& theCamera) const;

    virtual void renderHighlight(const Renderer& theRenderer, const Camera& theCamera) const;

    /** Get the list of renderable component */
    std::vector<BaseRenderable*>& getRenderableComponents();

    /** Get this Entity's position */
    glm::vec3 getPosition() const;

    /** Get this Entity's rotation */
    glm::vec3 getRotation() const;

    /** Get this Entity's scale */
    glm::vec3 getScale() const;

    /** Get the velocity of this Entity*/
    glm::vec3 getVelocity() const;

    /**
     * Add a Renderable for this Entity. Renderables are owned by the entity and deleted when the Entity is deleted
     * \param newPosition New position vector
     */
    void addRenderable(BaseRenderable* newRenderable); 

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

    /**
     * Set the velocity of this Entity
     * \param newVelocity New velocity vector
     */
    void setVelocity(const glm::vec3& newVelocity);

    void setCollider2(Collider2* newCollider);

    Collider2* getCollider() const;

    /** Add a physics component of the specified class */
    template<typename T>
    void addPhysicsComponent();

    /** Get a pointer to the physics component of the specified class if it exists */
    template<typename T>
    T* getPhysicsComponent();
};