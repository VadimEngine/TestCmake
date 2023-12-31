#include "App.h"
#include "TurnStrategyGame.h"
#include "Logger.h"


namespace TurnStrategy {

    TurnStrategyGame::TurnStrategyGame(App& theApp, Camera& focusCamera) 
    : mApp_(theApp) ,mCameraController_(&focusCamera, theApp.getWindow().getInputHandler()),
      mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}),
      mSprite1_(&mSpriteSheet_, glm::ivec2(0, 0)),
      mSprite2_(&mSpriteSheet_, glm::ivec2(5, 21)), mUnit_(*this, &mSprite1_) {
        // set camera position
        focusCamera.setPosition({5, 5, 11});
        screenSize = theApp.getWindow().getWindowDimensions();
        // create first unit
        mUnit_.setName("Unit 1");
        mUnit_.setCollider2(new Collider2());
        mUnit_.setPosition({6,5,0});
        mUnitList_.push_back(&mUnit_);
        // create first settlement
        Settlement* settlement = new Settlement(*this, &mSprite2_, {5,5});
        settlement->setName("Settlement1");
        settlement->setCollider2(new Collider2());
        settlement->setPosition({5,5,0});
        mSettlementList_.push_back(settlement);
        
        // load tile map
        mpTileMap_ = new TileMap("res/World1.png");
    }

    void TurnStrategyGame::update(const float dt) {
        updateCamera(dt);
        
        // update units
        for (const auto& eachUnit : mUnitList_) {
            eachUnit->update(dt);
        }
        // update settlements
        for (const auto& eachSettlement : mSettlementList_) {
            eachSettlement->update(dt);
        }

        // draw minimap
    }
    
    // TODO maybe this should not take in the camera here and just use the games current focus camera which is needed for input handling (get mouse position)
    void TurnStrategyGame::render(const Renderer& renderer, const Camera& camera) {
        
        mpTileMap_->render(renderer, camera);
        drawGrid(renderer);

        // draw settlements
        for (const auto& eachSettlement : mSettlementList_) {
            eachSettlement->render(renderer, camera);
            if (eachSettlement == selectedEntity) {
                selectedEntity->renderHighlight(renderer, camera);
            }
        }

        // render units
        for (const auto& eachUnit : mUnitList_) {
            eachUnit->render(renderer, camera);
            if (eachUnit == selectedEntity) {
                selectedEntity->renderHighlight(renderer, camera);
                eachUnit->renderValidMoves(renderer, camera);
            }
        }
    }

    Entity* TurnStrategyGame::getSelectedEntity() {
        return selectedEntity;
    }

    
    void TurnStrategyGame::onMousePress(const InputHandler::MouseEvent& mouseEvent) {
        if (ImGuiComponent::mouseOnGUI()) {
            return;
        }
        if (mouseEvent.getButton() == InputHandler::MouseEvent::Button::LEFT) {
            onLeftClick(mouseEvent);
        } else if (mouseEvent.getButton() == InputHandler::MouseEvent::Button::RIGHT) {
            onRightClick(mouseEvent);
        }
    }

    void TurnStrategyGame::onMouseRelease(const InputHandler::MouseEvent& mouseEvent) {

    }

    void TurnStrategyGame::onMouseWheel(const InputHandler::MouseEvent& mouseEvent) {
        Camera& theCamera = *(mCameraController_.getCamera());

        if (mouseEvent.getType() == InputHandler::MouseEvent::Type::SCROLL_UP) {
            theCamera.move(theCamera.getForward(), 1.f);
            if (theCamera.getPosition().z < minCameraDistance) {
                glm::vec3 newPosition = theCamera.getPosition();
                newPosition.z = 1;
                theCamera.setPosition(newPosition);
            }
        } else if (mouseEvent.getType() == InputHandler::MouseEvent::Type::SCROLL_DOWN) {
            theCamera.move(theCamera.getForward(), -1.f);
            if (theCamera.getPosition().z < minCameraDistance) {
                glm::vec3 newPosition = theCamera.getPosition();
                newPosition.z = 1;
                theCamera.setPosition(newPosition);
            }
        }
    }

    void TurnStrategyGame::selectEntity(const glm::vec3& mouseOrigin, const glm::vec3& mouseDirection) {
        // TODO fix this. Is doesnt quite work right
        selectedEntity = nullptr;
        for (const auto& eachUnit: mUnitList_) {
            Collider2* theCollider = eachUnit->getCollider();
            if (theCollider->rayCollides(mouseOrigin, mouseDirection)) {
                selectedEntity = eachUnit;
                break;
            }
        }

        // if unit is not selected, check settlements
        if (selectedEntity == nullptr) {
            for (const auto& eachSettlement: mSettlementList_) {
                Collider2* theCollider = eachSettlement->getCollider();
                if (theCollider->rayCollides(mouseOrigin, mouseDirection)) {
                    selectedEntity = eachSettlement;
                    break;
                }
            }
        }

    }

    void TurnStrategyGame::drawGrid(const Renderer& theRenderer) {
        float cellWidth = 1.f;
        float cellHeight = 1.f;
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), {0,0,0});
        glm::vec4 lineColor = {0,0,0,1};

        // Horizontal lines
        for (float i = -.5; i < 20; i+=1.f) {
            theRenderer.renderLineSimple(
                {0*cellWidth, i*cellHeight,0}, {20*cellWidth, i*cellHeight,0}, 
                *(mCameraController_.getCamera()), translationMatrix, lineColor
            );
        }

        // Vertical lines
        for (float i = -.5; i < 20; i+=1.f) {
            theRenderer.renderLineSimple(
                {i*cellWidth, 0*cellHeight,0}, {i*cellWidth, 20*cellHeight,0}, 
                *(mCameraController_.getCamera()), translationMatrix, lineColor
            );
        }
    }

    void TurnStrategyGame::spawnUnit(glm::ivec2 tileLocation) {
        Unit* newUnit = new Unit(*this, &mSprite1_);
        newUnit->setName("Unit " + std::to_string(mUnitList_.size()));
        newUnit->setCollider2(new Collider2());
        newUnit->setPosition({tileLocation.x,tileLocation.y,0});
        mUnitList_.push_back(newUnit);
    }

    void TurnStrategyGame::spawnSettlement(glm::ivec2 tileLocation) {
        Settlement* settlement = new Settlement(*this, &mSprite2_, tileLocation);
        settlement->setName("Settlement" + std::to_string(mSettlementList_.size()));
        settlement->setCollider2(new Collider2());
        settlement->setPosition({tileLocation.x, tileLocation.y,0});
        mSettlementList_.push_back(settlement);
    }

    void TurnStrategyGame::updateCamera(float dt) {
        Camera& theCamera = *(mCameraController_.getCamera());

        if (mApp_.getWindow().getInputHandler().isKeyPressed(GLFW_KEY_W)) {
            theCamera.move(theCamera.getUp(), theCamera.getMoveSpeed() * dt);
        }
        if (mApp_.getWindow().getInputHandler().isKeyPressed(GLFW_KEY_S)) {
            theCamera.move(theCamera.getUp(), -theCamera.getMoveSpeed() * dt);
        }
        if (mApp_.getWindow().getInputHandler().isKeyPressed(GLFW_KEY_A)) {
            theCamera.move(theCamera.getRight(), -theCamera.getMoveSpeed() * dt);
        } 
        if (mApp_.getWindow().getInputHandler().isKeyPressed(GLFW_KEY_D)) {
            theCamera.move(theCamera.getRight(), theCamera.getMoveSpeed() * dt);
        }
    }

    void TurnStrategyGame::nextTurn() {
        // reset all game objects for next turn
        currentTurn++;
        for (const auto& eachUnit: mUnitList_) {
            eachUnit->resetForTurn();
        }
        for (const auto& eachSettlement: mSettlementList_) {
            eachSettlement->resetForTurn();
        }
        addTerritoryMode = false;
    }

    int TurnStrategyGame::getCurrentTurn() {
        return currentTurn;
    }

    std::vector<Settlement*>& TurnStrategyGame::getSettlementList() {
        return mSettlementList_;
    }

    std::vector<Unit*>& TurnStrategyGame::getUnitList() {
        return mUnitList_;
    }

    void TurnStrategyGame::onLeftClick(const InputHandler::MouseEvent& mouseEvent) {

        glm::ivec2 mousePosition = mouseEvent.getPosition();

        glm::vec3 ray_ndc(
            (2.0f * mousePosition.x) / screenSize.x - 1.0f,
            1.0f - (2.0f * mousePosition.y) / screenSize.y,
            1.0f
        );

        glm::vec4 ray_clip(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
        glm::mat4 inverseProjectionMatrix = glm::inverse(mCameraController_.getCamera()->getProjectionMatrix());
        glm::vec4 ray_eye = inverseProjectionMatrix * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

        glm::mat4 inverseViewMatrix = glm::inverse(mCameraController_.getCamera()->getViewMatrix());
        glm::vec4 ray_world = inverseViewMatrix * ray_eye;
        glm::vec3 ray_direction = glm::normalize(glm::vec3(ray_world));

        glm::vec3 cameraPos = mCameraController_.getCamera()->getPosition();

        if (addTerritoryMode && selectedEntity != nullptr) {
            float t = -cameraPos.z / ray_direction.z;
            glm::vec3 intersectionPoint = cameraPos + t * ray_direction;
            int tileX = static_cast<int>(std::round(intersectionPoint.x));
            int tileY = static_cast<int>(std::round(intersectionPoint.y));

            if (dynamic_cast<Settlement*>(selectedEntity)) {
                dynamic_cast<Settlement*>(selectedEntity)->addTerritory({tileX, tileY});
            }
            addTerritoryMode = false;
        } else {
            addTerritoryMode = false;
            selectEntity(cameraPos, ray_direction);
        }
    }

    void TurnStrategyGame::onRightClick(const InputHandler::MouseEvent& mouseEvent) {
        if (selectedEntity != nullptr && dynamic_cast<Unit*>(selectedEntity)) {
            // TODO make a function to calculate mouse ray
            glm::ivec2 mousePosition = mouseEvent.getPosition();

            glm::vec3 ray_ndc(
                (2.0f * mousePosition.x) / screenSize.x - 1.0f,
                1.0f - (2.0f * mousePosition.y) / screenSize.y,
                1.0f
            );

            glm::vec4 ray_clip(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
            glm::mat4 inverseProjectionMatrix = glm::inverse(mCameraController_.getCamera()->getProjectionMatrix());
            glm::vec4 ray_eye = inverseProjectionMatrix * ray_clip;
            ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

            glm::mat4 inverseViewMatrix = glm::inverse(mCameraController_.getCamera()->getViewMatrix());
            glm::vec4 ray_world = inverseViewMatrix * ray_eye;
            glm::vec3 ray_direction = glm::normalize(glm::vec3(ray_world));

            glm::vec3 cameraPos = mCameraController_.getCamera()->getPosition();

            float t = -cameraPos.z / ray_direction.z;
            glm::vec3 intersectionPoint = cameraPos + t * ray_direction;

            int newX = static_cast<int>(std::round(intersectionPoint.x));
            int newY = static_cast<int>(std::round(intersectionPoint.y));

            dynamic_cast<Unit*>(selectedEntity)->moveToTile({newX, newY});
        }
    }

} // namespace TurnStrategy