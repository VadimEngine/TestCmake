// forward declare
#include "App.h" // needed for #define GLEW_STATIC from app
#include "TurnStrategyGame.h"
// class
#include "Unit.h"

namespace turn_strategy {
    Unit::Unit(TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite)
     : Entity(theGame.getScene()), mGame_(theGame) {
        addRenderable(new SpriteRenderable(pSprite));
    }

    void Unit::update(const float dt) {
    }

    void Unit::setName(const std::string& newName) {
        mName_ = newName;
    }

    std::string Unit::getName() const {
        return mName_;
    }

    int Unit::getMoves() const {
        return mMoves_;
    }

    void Unit::renderValidMoves(const Renderer& theRenderer) {
        //gather valid tiles first
        std::unordered_set<glm::ivec2, utils::Vec2Hash> validTiles = getMoveableTiles();

        glm::vec4 lineColor = {0,0,1,1};
        glm::mat4 translationMatrix = glm::identity<glm::mat4>();

        // TODO diagonal directions
        const std::array<glm::ivec2, 4> dirs = {{
            {1,0},
            {0,1},
            {0,-1},
            {-1,0},
        }};

        // draw border
        for (const auto& eachTile : validTiles) {
            // iterate 4 directions
            for (const auto& dir: dirs) {
                if (!validTiles.contains(glm::ivec2(eachTile.x + dir.x, eachTile.y + dir.y))) {
                    //draw border line
                    glm::vec3 p1 = {
                            eachTile.x + dir.x/2.f - dir.y / 2.f,
                            eachTile.y + dir.y/2.f - dir.x / 2.f,
                            0.f
                    };

                    glm::vec3 p2 = {
                            eachTile.x + dir.x/2.f + dir.y / 2.f,
                            eachTile.y + dir.y/2.f + dir.x / 2.f,
                            0.f
                    };
                    theRenderer.renderLineSimple(p1, p2, translationMatrix, lineColor);
                }
            }
        }
    }

    std::unordered_set<glm::ivec2, utils::Vec2Hash> Unit::getMoveableTiles() const {
        //gather valid tiles first
        std::unordered_set<glm::ivec2, utils::Vec2Hash> validTiles;

        glm::ivec2 currentTile = {
            static_cast<int>(std::round(mPosition_.x)),
            static_cast<int>(std::round(mPosition_.y))
        };

        // TODO diagonal directions
        const std::array<glm::ivec2, 4> dirs = {{
            {1,0},
            {0,1},
            {0,-1},
            {-1,0},
        }};

        std::queue<glm::ivec2> traverseQueue;
        traverseQueue.push(currentTile);

        const TileMap* tileMap = mGame_.getTileMap();

        // BFS all valid tile up to mMoves_ steps away
        int distance = 0;
        while (distance < mMoves_ && !traverseQueue.empty()) {
            int tiles = traverseQueue.size();

            for (int i = 0; i < tiles; ++i) {
                glm::ivec2 curr = traverseQueue.front();
                traverseQueue.pop();
                validTiles.insert(curr);

                for (const auto& dir: dirs) {
                    const glm::ivec2 newTile = curr + dir;
                    if (!validTiles.contains(newTile)) {
                        if (newTile.x >= 0 && newTile.y >= 0 && newTile.x < tileMap->getWidth() && newTile.y < tileMap->getHeight()) {
                            // avoid sea tiles
                            if (tileMap->tileAt(newTile)->type != TileMap::Tile::Type::SEA) {
                                traverseQueue.push(newTile);
                            }
                        }
                    }
                }
            }
            ++distance;
        }

        return validTiles;
    }

    void Unit::moveToTile(glm::ivec2 newPosition) {
        auto validTiles = getMoveableTiles();
        if (validTiles.contains(newPosition)) {
            int distance = static_cast<int>(abs(newPosition.x - mPosition_.x) + abs(newPosition.y - mPosition_.y));

            // now check the tile is not occupied
            for (auto& eachUnit: mGame_.getUnitList()) {
                if (eachUnit->getPosition().x == newPosition.x && eachUnit->getPosition().y == newPosition.y) {
                    return;
                }
            }

            setPosition({newPosition.x, newPosition.y, 0});
            doAction(distance);
        }
    }

    void Unit::resetForTurn() {
        mMoves_ = mMaxMoves_;
    }

    void Unit::doAction(int cost) {
        mMoves_ -= cost;
        if (mMoves_ < 0) {
            mMoves_ = 0;
        }
    }

    bool Unit::canSettle() const {
        // if there is no settlement within 5 tiles, can settle
        bool ret = true;
        for (const auto& eachSettlement: mGame_.getSettlementList()) {
            int distance = static_cast<int>(abs(mPosition_.x - eachSettlement->getPosition().x) + abs(mPosition_.y - eachSettlement->getPosition().y));
            if (distance < 5) {
                ret = false;
                break;
            }
        }
        return ret;
    }

} // namespace turn_strategy