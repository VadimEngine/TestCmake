#pragma once
#include "Renderer.h"
#include <vector>
#include "Texture.h"
#include "SpriteSheet.h"
#include "CameraController.h"
#include "ModelRenderable.h"
#include "Unit.h"
#include "Settlement.h"
#include "Camera.h"
#include "TileMap.h"
#include "Resource.h"

// forward declare App
class App;
class TurnStrategyScene;

namespace turn_strategy {

    class TurnStrategyGame {
    private:

        TurnStrategyScene& mScene_;
        App& mApp_;

        /** Camera Controller */
        CameraController mCameraController_;

        std::vector<Unit*> mUnitList_;

        std::vector<Settlement*> mSettlementList_;

        SpriteSheet::Sprite mSprite1_;

        SpriteSheet::Sprite mSprite2_;

        Unit mUnit_;

        // TODO maybe use a SelectedEntity class that has the pointer and object type. Maybe other properties as well?
        Entity* selectedEntity = nullptr;

        float minCameraDistance = 1.f;


    public:
        TileMap* mpTileMap_;

        int currentTurn = 0;

        bool addTerritoryMode = false;

    public:
        TurnStrategyGame(TurnStrategyScene& scene, Camera& focusCamera);

        /**
         * Update Game
         * @param dt Time since last update
         */
        void update(const float dt);

        /**
         * Render Game
         * @param renderer Rendering Renderer
         * @param camera Camera to render relative to
         */
        void render(const Renderer& renderer, const Camera& camera);

        void setTileMap(Texture* texture);

        Entity* getSelectedEntity();

        /**
         * On Mouse button press handler
         * @param mousePos Mouse Position at time of the event
         * @param mouseEvent Mouse event details
         */
        void onMousePress(const InputHandler::MouseEvent& mouseEvent);

        /**
         * On Mouse Button release handler
         * @param mousePos Mouse Position at time of the event
         * @param mouseEvent Mouse event details
         */
        void onMouseRelease(const InputHandler::MouseEvent& mouseEvent);

        void onMouseWheel(const InputHandler::MouseEvent& mouseEvent);

        void selectEntity(const glm::vec3& mouseOrigin, const glm::vec3& mouseDirection);

        void drawGrid(const Renderer& theRenderer);

        void spawnUnit(glm::ivec2 tileLocation);

        void spawnSettlement(glm::ivec2 tileLocation);

        void updateCamera(float dt);

        void nextTurn();

        int getCurrentTurn();

        std::vector<Settlement*>& getSettlementList();

        std::vector<Unit*>& getUnitList();


    private:
        void onLeftClick(const InputHandler::MouseEvent& mouseEvent);

        void onRightClick(const InputHandler::MouseEvent& mouseEvent);
    };

} // namespace turn_strategy