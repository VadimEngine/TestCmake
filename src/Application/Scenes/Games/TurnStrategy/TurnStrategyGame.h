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

namespace turn_strategy {
    // forward declare Scene
    class TurnStrategyScene;

    class TurnStrategyGame {
    public:
        enum class EntityType {
            NONE, UNIT, SETTLEMENT
        };

        /**
         * @brief Constructor
         * 
         * @param scene Scene this game is in
         */
        TurnStrategyGame(TurnStrategyScene& scene);

        /** Destructor */
        ~TurnStrategyGame();

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

        void spawnUnit(glm::ivec2 tileLocation);

        void spawnSettlement(glm::ivec2 tileLocation);

        void nextTurn();

        int getCurrentTurn();

        void setTerritoryMode(bool mode);

        std::vector<std::unique_ptr<Settlement>>& getSettlementList();

        std::vector<std::unique_ptr<Unit>>& getUnitList();

        const TileMap* getTileMap();

        /**
         * @brief Get the Scene this object is in. Just Scene for now to avoid circular dependency bugs
         * 
         */
        Scene& getScene();

    private:
        struct SelectedEntityDetails {
            Entity* selected = nullptr;
            EntityType type;
        };
        /**
         * @brief Helper method to handle moving the camera with key inputs
         * 
         * @param dt time since last update
         */
        void updateCamera(float dt);

        /**
         * @brief Select an entity based on the ray's origin and direction. Only selects if the 
         * ray collides with an entity's collider
         * 
         * @param mouseOrigin Ray origin
         * @param mouseDirection Ray direction
         */
        void selectEntity(const glm::vec3& mouseOrigin, const glm::vec3& mouseDirection);

        /**
         * @brief Helper method to draw the grid around the tiles
         * 
         * @param theRenderer Renderer to render with
         */
        void drawGrid(const Renderer& theRenderer);

        /**
         * @brief Helper methods the handle right mouse clicks
         * 
         * @param mouseEvent Mouse event details
         */
        void onLeftClick(const InputHandler::MouseEvent& mouseEvent);

        /**
         * @brief Helper method to handle left mouse clicks
         * 
         * @param mouseEvent Mouse event details
         */
        void onRightClick(const InputHandler::MouseEvent& mouseEvent);

        /** Reference to the Scene this game is in */
        TurnStrategyScene& mScene_;
        /** Reference top the parent app */
        App& mApp_;
        /** Camera Controller */
        CameraController mCameraController_;
        /** List of units currently in the game */
        std::vector<std::unique_ptr<Unit>> mUnitList_;
        /** List of settlements currently in the game*/
        std::vector<std::unique_ptr<Settlement>> mSettlementList_;
        /** Sprites used in this scene */
        std::unordered_map<std::string, std::unique_ptr<SpriteSheet::Sprite>> mSprites_;
        /** Entity selected by the player */
        SelectedEntityDetails mSelectedEntity_;
        /** Current turn number*/
        int mCurrentTurn_ = 0;
        /** Tile map for this game */
        std::unique_ptr<TileMap> mpTileMap_;
        /** If the player is adding territories for a settlement */
        bool mAddTerritoryMode_ = false;
        /** Minumum camera z position  */
        float mMinCameraDistance_ = 1.f;
    };

} // namespace turn_strategy