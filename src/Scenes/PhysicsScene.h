#pragma once
#include "Scene.h"
#include "PhysicsSceneGUI.h"
#include "Entity.h"
#include "ModelRenderable.h"
#include "CameraController.h"
#include "RigidBodyComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>

// Forward Declare App
class App;

class PhysicsScene : public Scene {
private:
    bool mRunning_ = true;

    /** Camera Controller */
    CameraController mCameraController_;

    /** GUI for this Scene*/
    PhysicsSceneGUI mGui_;

    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;

    /** Circle Plane Model*/
    Model mCircleModel_;

    /** Rectangle Plane Model*/
    Model mRectModel_;

public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    PhysicsScene(App& theApp);

    /** Destructor */
    ~PhysicsScene();
    
    /** 
     * Update the Scene
     * \param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * \param renderer Rendering helper
     */
    void render(Renderer& renderer) override;

    /** get the entities in this scene*/
    std::vector<Entity*>& getEntities();

    /** Spawn an Entity*/
    void addEntity();

    /**
     *  Set if the scene is being updated
     * \param dt Time since last update in seconds
     */
    void setRunning(bool enabled);

private:
    /** Resolve collisions to avoid overlapping */
    void handleEntityOverlap();

    /** Check and enact collision actions between Entities */
    void handleEntityCollision(const float dt);
};