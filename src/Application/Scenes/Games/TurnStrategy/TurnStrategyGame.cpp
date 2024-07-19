#include "App.h"
#include "TurnStrategyGame.h"
#include "TurnStrategyScene.h"
#include "Logger.h"

namespace turn_strategy {
    TurnStrategyGame::TurnStrategyGame(TurnStrategyScene& scene)
    : mScene_(scene), mApp_(mScene_.getApp()), 
    mCameraController_(mScene_.getFocusCamera(), mApp_.getWindow().getInputHandler()) {
        // set camera position
        mScene_.getFocusCamera()->setPosition({5, 5, 11});
        // build sprites
        mSprites_["Unit"] = std::make_unique<SpriteSheet::Sprite>(
            *mScene_.getApp().getResources().getResource<SpriteSheet>("SpriteSheet1"), 
            glm::ivec2{0, 0}
        );
        mSprites_["Settlement"] = std::make_unique<SpriteSheet::Sprite>(
            *mScene_.getApp().getResources().getResource<SpriteSheet>("SpriteSheet1"), 
            glm::ivec2{5, 21}
        );

        // create first unit
        Unit* theUnit = new Unit(mScene_, *this, mSprites_["Unit"].get());
        theUnit->setName("Unit 1");
        theUnit->setCollider2(new Collider2(*theUnit));
        theUnit->setPosition({6,5,0});
        mUnitList_.push_back(std::unique_ptr<Unit>(theUnit));
        // create first settlement
        Settlement* settlement = new Settlement(*this, mSprites_["Settlement"].get(), {5,5});
        settlement->setName("Settlement1");
        settlement->setCollider2(new Collider2(*settlement));
        settlement->setPosition({5,5,0});
        mSettlementList_.push_back(std::unique_ptr<Settlement>(settlement));
        mpTileMap_ = std::make_unique<TileMap>(
            (mScene_.getResources().getResource<Texture>("World1")),
            mScene_.getApp().getResources().getResource<SpriteSheet>("SpriteSheet1")
        );
    }

    TurnStrategyGame::~TurnStrategyGame() {}

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
            if (eachSettlement.get() == mSelectedEntity_.selected) {
                eachSettlement->renderHighlight(renderer, camera);
            }
        }

        // render units
        for (const auto& eachUnit : mUnitList_) {
            eachUnit->render(renderer, camera);
            if (eachUnit.get() == mSelectedEntity_.selected) {
                eachUnit->renderHighlight(renderer, camera);
                eachUnit->renderValidMoves(renderer, camera);
            }
        }
    }

    Entity* TurnStrategyGame::getSelectedEntity() {
        return mSelectedEntity_.selected;
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
            if (theCamera.getPosition().z < mMinCameraDistance_) {
                glm::vec3 newPosition = theCamera.getPosition();
                newPosition.z = mMinCameraDistance_;
                theCamera.setPosition(newPosition);
            }
        } else if (mouseEvent.getType() == InputHandler::MouseEvent::Type::SCROLL_DOWN) {
            theCamera.move(theCamera.getForward(), -1.f);
        }
    }

    void TurnStrategyGame::selectEntity(const glm::vec3& mouseOrigin, const glm::vec3& mouseDirection) {
        // TODO fix this. Is doesnt quite work right
        mSelectedEntity_.selected = nullptr;
        for (const auto& eachUnit: mUnitList_) {
            Collider2* theCollider = eachUnit->getCollider();
            if (theCollider->rayCollides(mouseOrigin, mouseDirection)) {
                mSelectedEntity_.selected = eachUnit.get();
                mSelectedEntity_.type = EntityType::UNIT;
                break;
            }
        }

        // if unit is not selected, check settlements
        if (mSelectedEntity_.selected == nullptr) {
            for (const auto& eachSettlement: mSettlementList_) {
                Collider2* theCollider = eachSettlement->getCollider();
                if (theCollider->rayCollides(mouseOrigin, mouseDirection)) {
                    mSelectedEntity_.selected = eachSettlement.get();
                    mSelectedEntity_.type = EntityType::SETTLEMENT;
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
        Unit* newUnit = new Unit(mScene_, *this, mSprites_["Unit"].get());
        newUnit->setName("Unit " + std::to_string(mUnitList_.size()));
        newUnit->setCollider2(new Collider2(*newUnit));
        newUnit->setPosition({tileLocation.x,tileLocation.y,0});
        mUnitList_.push_back(std::unique_ptr<Unit>(newUnit));
    }

    void TurnStrategyGame::spawnSettlement(glm::ivec2 tileLocation) {
        Settlement* settlement = new Settlement(*this, mSprites_["Settlement"].get(), tileLocation);
        settlement->setName("Settlement" + std::to_string(mSettlementList_.size()));
        settlement->setCollider2(new Collider2(*settlement));
        settlement->setPosition({tileLocation.x, tileLocation.y,0});
        mSettlementList_.push_back(std::unique_ptr<Settlement>(settlement));
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
        ++mCurrentTurn_;
        for (const auto& eachUnit: mUnitList_) {
            eachUnit->resetForTurn();
        }
        for (const auto& eachSettlement: mSettlementList_) {
            eachSettlement->resetForTurn();
        }
        mAddTerritoryMode_ = false;
    }

    int TurnStrategyGame::getCurrentTurn() {
        return mCurrentTurn_;
    }

    void TurnStrategyGame::setTerritoryMode(bool mode) {
        mAddTerritoryMode_ = mode;
    }


    std::vector<std::unique_ptr<Settlement>>& TurnStrategyGame::getSettlementList() {
        return mSettlementList_;
    }

    std::vector<std::unique_ptr<Unit>>& TurnStrategyGame::getUnitList() {
        return mUnitList_;
    }

    const TileMap* TurnStrategyGame::getTileMap() {
        return mpTileMap_.get();
    }

    Scene& TurnStrategyGame::getScene() {
        return mScene_;
    }

    void TurnStrategyGame::onLeftClick(const InputHandler::MouseEvent& mouseEvent) {
        glm::ivec2 mousePosition = mouseEvent.getPosition();
        glm::ivec2 screenSize = mApp_.getWindow().getWindowDimensions(); // get this incase the size changes

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

        if (mAddTerritoryMode_ && mSelectedEntity_.selected != nullptr) {
            float t = -cameraPos.z / ray_direction.z;
            glm::vec3 intersectionPoint = cameraPos + t * ray_direction;
            int tileX = static_cast<int>(std::round(intersectionPoint.x));
            int tileY = static_cast<int>(std::round(intersectionPoint.y));

            if (dynamic_cast<Settlement*>(mSelectedEntity_.selected)) {
                dynamic_cast<Settlement*>(mSelectedEntity_.selected)->addTerritory({tileX, tileY});
            }
            mAddTerritoryMode_ = false;
        } else {
            mAddTerritoryMode_ = false;
            // why does this need the camera position if the ray_direction is already translated by the camera?
            selectEntity(cameraPos, ray_direction);
        }
    }

    void TurnStrategyGame::onRightClick(const InputHandler::MouseEvent& mouseEvent) {
        if (mSelectedEntity_.selected != nullptr && dynamic_cast<Unit*>(mSelectedEntity_.selected)) {
            // TODO make a function to calculate mouse ray
            glm::ivec2 mousePosition = mouseEvent.getPosition();
            glm::ivec2 screenSize = mApp_.getWindow().getWindowDimensions(); // get this incase the size changes


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

            dynamic_cast<Unit*>(mSelectedEntity_.selected)->moveToTile({newX, newY});
        }
    }

} // namespace turn_strategy