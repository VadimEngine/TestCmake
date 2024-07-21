#pragma once
// standard lib
#include <functional>
#include <optional>
#include <unordered_set>
// third party
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
// project
#include "PhysicsComponentBase.h"
#include "Renderer.h"

class Entity;

class Collider : public PhysicsComponentBase {
public:
    using OnCollisionCB = std::function<void(Collider&, Collider&)>;
protected:
    // center position
    glm::vec3 mPosition_;

    glm::vec3 mScale_;

    std::unordered_set<Collider*> mCurrentCollides;

    // todo how to allow control to remove specific functions
    std::vector<OnCollisionCB> mOnCollisionEnterCallbacks_;

    std::vector<OnCollisionCB> mOnCollisionExitCallbacks_;

public:
    Collider(Entity& parentEntity);

    ComponentType getType() const override;

    virtual bool isColliding(const Collider& other) const = 0;

    virtual std::optional<glm::vec3> getCollisionMTV(const Collider& other) const = 0;

    void addOnCollisionEnterCallback(const OnCollisionCB& cb);

    void addOnCollisionExitCallback(const OnCollisionCB& cb);

    void onCollisionEnter(Collider& other);

    void onCollisionExit(Collider& other);

    glm::vec3 getPosition() const;

    glm::vec3 getScale() const;

};