#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    enum class CameraMode {PERSPECTIVE=0, ORTHOGONAL};
private:
    glm::vec3 mWorldUp_;
    glm::vec3 mPosition_;
    glm::vec3 mForward_;
    glm::vec3 mUp_;
    glm::vec3 mRight_;
    float mFOV_ = 45.0f;
    glm::vec3 mRotation_ = glm::vec3(0.0, 0.0f, 0.0f);
    CameraMode mMode_ = CameraMode::PERSPECTIVE;

public:
    Camera(glm::vec3 position);

    ~Camera();

    void update(float dt);

    // TODO Set positions, rotation
    void move(const glm::vec3 dir, const float step);

    void rotate(glm::vec3 axis, const float angle);

    void setFOV(const float newFOV);

    void zoom(const float zoomAdjust);

    /**
     * Set the Camera mode
     */
    void setMode(const CameraMode mode);

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

    CameraMode getMode() const;

private:
    void updateCameraVectors();
};