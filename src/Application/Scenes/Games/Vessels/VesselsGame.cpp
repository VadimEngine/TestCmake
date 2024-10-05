// forward declare
#include "App.h"
#include "VesselsScene.h"
// class
#include "VesselsGame.h"

#include <iostream>

namespace vessels {

    VesselsGame::VesselsGame(VesselsScene& scene) 
     : mScene_(scene), 
     mInputHandler_(mScene_.getApp().getWindow().getInputHandler()),
     mCameraController_(mScene_.getFocusCamera(), mScene_.getApp().getWindow().getInputHandler()) {
        mpPlayer_ =  std::make_unique<Player>(*this);
        mpPlayer_->addRenderable(new ModelRenderable(
            mScene_.getResources().getResource<Model>("Cube"),
            mScene_.getApp().getResources().getResource<Shader>("Assimp")
        ));
        mpPlayer_->setPosition({0.f,.5f,0.f});

        // make floor
        {
            std::unique_ptr<Entity> floorEntity = std::make_unique<Entity>(mScene_);
            ModelRenderable* floorRenderable = floorEntity->addRenderable<ModelRenderable>();
            floorRenderable->setModel(mScene_.getResources().getResource<Model>("RectPlane"));
            floorRenderable->setShader(mScene_.getApp().getResources().getResource<Shader>("Assimp"));
            // Plane Renderable properties
            floorRenderable->setRotation({-90, 0, 0});
            floorRenderable->setScale({10, 10, 0});
            floorRenderable->setColor({0.f, 1.f, 0.f, 1.0f});
            // Add renderable to floor entity
            mEntities_.push_back(std::move(floorEntity));
        }
    }

    VesselsGame::~VesselsGame() {}

    void VesselsGame::update(const float dt) {
        handleKeyUpdate(dt);
    }

    void VesselsGame::render(Renderer& renderer) {
        if (mState_ == VesselsGame::GameState::CORPOREAL_REALM) {
            mpPlayer_->render(renderer);
            for (const auto& entity: mEntities_) {
                entity->render(renderer);
            }
        }
    }

    void VesselsGame::handleKeyUpdate(float dt) {
        if (mState_ == VesselsGame::GameState::CORPOREAL_REALM) {

            if (mInputHandler_.isKeyPressed(GLFW_KEY_LEFT)) {
                auto currRot = mpPlayer_->getRotation();
                currRot += glm::vec3{0,1,0} * dt * 50.f;
                mpPlayer_->setRotation(currRot);

            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_RIGHT)) {
                auto currRot = mpPlayer_->getRotation();
                currRot += glm::vec3{0,-1,0} * dt * 50.f;
                mpPlayer_->setRotation(currRot);
            }

            const float speed = 5.f;
            glm::vec3 curPlayerPos = mpPlayer_->getPosition();

            glm::vec3 dir = {0,0,0};

            if (mInputHandler_.isKeyPressed(GLFW_KEY_W)) {
                dir += mpPlayer_->getForward();
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_D)) {
                dir += mpPlayer_->getRight();
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_S)) {
                dir += -mpPlayer_->getForward();
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_A)) {
                dir += -mpPlayer_->getRight();
            }


            if (glm::length(dir) > 0.0f) {
                dir = glm::normalize(dir);
                mpPlayer_->setPosition(curPlayerPos + dir * dt * speed);
            }
        }
    }

    void VesselsGame::onKeyPress(unsigned int code) {}

    void VesselsGame::onKeyRelease(unsigned int code) {}

    VesselsGame::GameState VesselsGame::getGameState() {
        return mState_;
    }

    void VesselsGame::setState(VesselsGame::GameState newState) {
        mState_ = newState;
    }

    VesselsScene& VesselsGame::getScene() {
        return mScene_;
    }

} // namespace vessels