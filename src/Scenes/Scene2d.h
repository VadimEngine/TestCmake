#pragma once
#include "Scene.h"
#include "Scene2dGUI.h"
#include "Shader.h"
#include "SOIL.h"
#include "SpriteSheet.h"

class Scene2d : public Scene {
private:
    Scene2dGUI mGui_;

    unsigned int mVAO;

    unsigned int texId;

    Shader* mpShader_ = nullptr;
public:
    SpriteSheet* theSpriteSheet;
    SpriteSheet::Sprite* theSprite;
    SpriteSheet::Sprite* theSprite2;

public:
    Scene2d(App* theApp);

    void update(const float dt) override;

    void render(Renderer& renderer) override;

};