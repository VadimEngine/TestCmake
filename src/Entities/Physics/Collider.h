#pragma once
#include <optional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Forward Declare RigidBody
class RigidBodyComponent;

class Collider {

// TODO maybe local position, scale and rotation?

public:
    /** Possible shapes for a collider */
    enum class Shape {CIRCLE, RECTANGLE};

private:
    /** Description of the shape of this collider */
    Shape mShape_;

    /** The rigid body this collider is tied to  */
    RigidBodyComponent& mRigidBody_;

    /** Dimensions of this Collider */
    glm::vec3 mDimension_ = {2.f, 2.f, 2.f};

public:
    /**
     * Constructor
     * \param theRigidBody Rigid body this Collider is for
    */
    Collider(RigidBodyComponent& theRigidBody);

    /** Destructor */
    ~Collider();

    /** 
     * If there is a collision, get the normal vector from the other Collider
     * \param otherCollider Other Collider that may be colliding with this Collider
     */
    std::optional<glm::vec3> getCollisionNormal(Collider* otherCollider) const;

    /** 
     * If there is a collision, get the Minimum translation vector that should be applied to this collider
     * \param otherCollider Other Collider that may be colliding with this Collider
     */
    std::optional<glm::vec3> getCollisionMVT(Collider* otherCollider) const;

    /** Get Shape type of this collider */
    Shape getShape() const;

    /** 
     * set Shape type of this collider
     * \param theShape New Shape type
     */
    void setShape(const Shape& theShape);

    /** Get The Dimensions of this Collider */
    glm::vec3 getDimension() const;

    /**
     * Replace the dimensions of this collider
     * \param newDimension New collider dimensions
     */
    void setDimension(const glm::vec3& newDimension);

    /**
     * Update of the dimensions of this collider
     * \param axis Axis to update (x=0, y=1, z=2)
     * \param newValue New value for dimension
     */
    void setDimension(int axis, float newValue);

    // TODO onEnter/onCollide/onExit?

private:
    /** Get the width / 2 that is also scaled with the related Entity */
    float getWidthDiv2() const;

    /** Get the height / 2 that is also scaled with the related Entity */
    float getHeightDiv2() const;

    /** Get the absolute Center position of this collider*/
    glm::vec3 getAbsolutePosition() const;
};