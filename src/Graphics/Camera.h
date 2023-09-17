#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 mWorldUp_;
    glm::vec3 mPosition_;
    glm::vec3 mForward_;
    glm::vec3 mUp_;
    glm::vec3 mRight_;
    float mFOV_ = 45.0f;
    glm::vec3 mRotation_ = glm::vec3(0.0, 0.0f, 0.0f);
public:
    Camera(glm::vec3 position);

    ~Camera();

    void update(float dt);

    void move(const glm::vec3 dir, const float step);

    void rotate(glm::vec3 axis, const float angle);

    void setFOV(const float newFOV);

    void zoom(const float zoomAdjust);

    glm::mat4 getProjectionMatrix() const;
    /**
     * Calculate and get the view matrix based on the camera's position and direction
     */
    glm::mat4 getViewMatrix() const;
    /**
     * Get camera rotations
     */
    glm::vec3 getRotation() const;
    /**
     * Get camera position
     */
    glm::vec3 getPosition() const;
    /**
     * Get camera forward direction
     */
    glm::vec3 getForward() const;

    glm::vec3 getRight() const;

    float getFOV() const;

private:
    void updateCameraVectors();
};