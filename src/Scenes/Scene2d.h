#pragma once
#include "Scene.h"
#include "Scene2dGUI.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "CameraController.h"

class Scene2d : public Scene {
private:
    /** Camera Controller */
    CameraController mCameraController_;

    /** GUI for this Scene*/
    Scene2dGUI mGui_;

    /** Sprite Sheet used for this Scene*/
    SpriteSheet mSpriteSheet_;

    /** Entities rendered in this Scene */
    std::vector<Entity*> mEntities_;

    /** First Sprite used in this Scene*/
    SpriteSheet::Sprite mSprite1_;
    
    /** Second Sprite used in this Scene*/
    SpriteSheet::Sprite mSprite2_;
    
    /** First sprite renderable for this scene*/
    SpriteRenderable mSpriteRenderable1_;

    /** Second sprite renderable for this scene*/
    SpriteRenderable mSpriteRenderable2_;

public:
    /**  
     * Constructor
     * \param theApp Parent app handling this Scene
     */
    Scene2d(App& theApp);

    /** Destructor */
    ~Scene2d();

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
};