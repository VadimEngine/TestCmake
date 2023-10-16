#pragma once
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    /** Camera mode options */
    enum class CameraMode {PERSPECTIVE=0, ORTHOGONAL};
private:
    /** World up vector */
    glm::vec3 mWorldUp_;
    /** Camera Position */
    glm::vec3 mPosition_;
    /** Camera forward vector */
    glm::vec3 mForward_;
    /** Camera up vector */
    glm::vec3 mUp_;
    /** Camera right vector */
    glm::vec3 mRight_;
    /** Camera FOV in degrees */
    float mFOV_ = 45.0f;
    /** Camera rotation vector (TODO try quaternions) */
    glm::vec3 mRotation_ = glm::vec3(0.0, 0.0f, 0.0f);
    /** The camera's mode */
    CameraMode mMode_ = CameraMode::PERSPECTIVE;
    /** Speed the camera moves */
    float mMoveSpeed_ = 20.f;
    /** Speed the camera rotates */
    float mRotationSpeed_ = 40.f;
    /** Speed the camera Zooms (adjust the FOV) */
    float mZoomSpeed_ = 2.f;

public:
    /** Constructor */
    Camera(glm::vec3 position = {0,0,0});

    /** Destructor */
    ~Camera();

    /** 
     * Update Camera 
     * \param dt Time since last update in seconds
     */
    void update(float dt);

    /**
     *  Move the camera from current postion in the given direction and step
     * \param dir Direction to move
     * \param step Amount to move 
     */
    void move(const glm::vec3 dir, const float step);

    /**
     *  Rotate the camera from current rotation in the given axis and step
     * \param axis Axis to rotate around
     * \param angle Amount to rotate 
     */
    void rotate(glm::vec3 axis, const float angle);

    /**
     * Set the Camera FOV
     * \param newFOV New FOV in degrees
     */
    void setFOV(const float newFOV);

    /**
     * Set the Camera Position 
     * \param newPosition New Position vector
    */
    void setPosition(glm::vec3 newPosition);

    /**
     * Set the Rotation vector
     * \param newRotation New Rotation vector
     */
    void setRotation(glm::vec3 newRotation);

    /**
     * Adjust the FOV with the given amount
     * \param zoomAdjust FOV adjustment amount
     */
    void zoom(const float zoomAdjust);

    /**
     * Set the Camera mode (Perspective/Orthogonal )
     * \param mode New Camera mode
     */
    void setMode(const CameraMode mode);

    /** Get the Projection matrix for this camera (Depends on Camera mode) */
    glm::mat4 getProjectionMatrix() const;

    /** Get the view matrix which is based on the Camera position and direction */
    glm::mat4 getViewMatrix() const;
    
    /** Get camera rotations */
    glm::vec3 getRotation() const;
    
    /** Get camera position */
    glm::vec3 getPosition() const;
    
    /** Get camera forward direction */
    glm::vec3 getForward() const;

    /** Get the Camera's Right vector */
    glm::vec3 getRight() const;

    /** Get the Camera FOV in degrees */
    float getFOV() const;

    /** Get the Cameras mode */
    CameraMode getMode() const;

    /**
     * Set the camera movement speed
     * \param mode New Camera mode
     */
    void setMoveSpeed(float newSpeed);

    /**
     * Set the camera rotation speed
     * \param mode New Camera mode
     */
    void setRotationSpeed(float newSpeed);
    
    /**
     * Set the camera zoom speed
     * \param mode New Camera mode
     */
    void setZoomSpeed(float newSpeed);
    
    /**
     * Get the Camera movement speed
     */
    float getMoveSpeed() const;

    /**
     * Get the Camera rotation speed
     */
    float getRotationSpeed() const;

    /**
     * Get the Camera zoom speed
     */
    float getZoomSpeed() const;

private:
    /** Update the forward, Right and Up vector based on the camera's rotation*/
    void updateCameraVectors();
};