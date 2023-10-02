#pragma once
#include "Scene.h"
#include "MenuGUI.h"

class MenuScene : public Scene {
private:
    MenuGUI* mpMenuPage_;
public:
    MenuScene(App* theApp);
    
    void update(const float dt) override;
    
    void render() override;
};