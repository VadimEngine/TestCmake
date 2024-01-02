#include "Collider2.h"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "Logger.h"

Collider2::Collider2() {
    mShape_ = Collider2::Shape::RECTANGLE;
}

Collider2::~Collider2() {}

void Collider2::render(const Renderer& theRenderer, const Camera& theCamera) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition_);

    theRenderer.renderRectangleSimple(theCamera, translationMatrix, {1,1,1,1});
}

std::optional<glm::vec3> Collider2::getCollisionNormal(Collider2* otherCollider) const {
    return std::nullopt;
}

bool Collider2::rayCollides(glm::vec3 rayOrigin, glm::vec3 rayDirection) const {
    float rectWidth = mDimension_.x;
    float rectHeight = mDimension_.y;
    glm::vec3 rectCenter = mPosition_;

    // Calculate half extents
    float halfWidth = rectWidth * 0.5f;
    float halfHeight = rectHeight * 0.5f;

    // Calculate the normal of the rectangle (assuming it's aligned with the axes)
    glm::vec3 rectNormal = glm::vec3(0.0f, 0.0f, 1.0f); // Assuming the rectangle is in the XY plane

    // Calculate the vector from the ray origin to the rectangle center
    glm::vec3 toCenter = rayOrigin - rectCenter;

    // Calculate the distance from the ray origin to the plane of the rectangle
    float distanceToPlane = glm::dot(toCenter, rectNormal);

    // Check if the ray is parallel or pointing away from the plane
    if (glm::abs(distanceToPlane) > 0.001f) {
        // Calculate the point of intersection with the plane
        glm::vec3 intersectionPoint = rayOrigin + (distanceToPlane * rayDirection);

        // Check if the intersection point is within the rectangle bounds
        if (glm::abs(intersectionPoint.x - rectCenter.x) <= halfWidth &&
            glm::abs(intersectionPoint.y - rectCenter.y) <= halfHeight) {
            // The ray intersects with the rectangle
            return true;
        }
    }

    // No intersection
    return false;
}

Collider2::Shape Collider2::getShape() const {
    return mShape_;
}

void Collider2::setShape(const Collider2::Shape& theShape) {
    mShape_ = theShape;
}

void Collider2::setPosition(const glm::vec3 newPosition) {
    mPosition_ = newPosition;
}

glm::vec3 Collider2::getDimension() const {
    return mDimension_;
}

glm::vec3 Collider2::getPosition() {
    return mPosition_;
}

void Collider2::setDimension(const glm::vec3& newDimension) {
    mDimension_ = newDimension;
}