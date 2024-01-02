#include "Unit.h"
#include "TurnStrategyGame.h"

namespace TurnStrategy {

    Unit::Unit(TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite)
     : mGame_(theGame) {
        addRenderable(new SpriteRenderable(pSprite));
    }

    void Unit::update(const float dt) {
    }

    void Unit::setName(const std::string& newName) {
        mName_ = newName; 
    }

    std::string Unit::getName() {
        return mName_;
    }

    int Unit::getMoves() {
        return moves;
    }

    void Unit::renderValidMoves(const Renderer& theRenderer, const Camera& theCamera) {
        //gather valid tiles first
        std::unordered_set<glm::ivec2, Vec2Hash> validTiles = getMoveableTiles();

        glm::vec4 lineColor = {0,0,1,1};
        glm::mat4 translationMatrix = glm::identity<glm::mat4>();

        // TODO diagonal directions
        std::vector<glm::ivec2> dirs = {
            {1,0},
            {0,1},
            {0,-1},
            {-1,0},
        };

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
                    theRenderer.renderLineSimple(p1, p2, theCamera, translationMatrix, lineColor);
                }
            }
        }
    }

    std::unordered_set<glm::ivec2, Unit::Vec2Hash> Unit::getMoveableTiles() {
        //gather valid tiles first
        std::unordered_set<glm::ivec2, Vec2Hash> validTiles;

        glm::ivec2 currentTile = {
            static_cast<int>(std::round(mPosition_.x)),
            static_cast<int>(std::round(mPosition_.y))
        };

        // TODO diagonal directions
        std::vector<glm::ivec2> dirs = {
            {1,0},
            {0,1},
            {0,-1},
            {-1,0},
        };

        std::queue<std::pair<glm::ivec2, int>> traverseQueue; // pair.second is distance

        traverseQueue.push(std::make_pair(currentTile, 0));

        // BFS
        while (!traverseQueue.empty()) {
            std::pair<glm::ivec2, int> curr = traverseQueue.front();
            traverseQueue.pop();
            validTiles.insert(curr.first);

            if (curr.second < moves) {
                for (const auto& dir: dirs) {
                    glm::ivec2 newTile = curr.first + dir;
                    // check if tile is valid distance
                    if (!validTiles.contains(newTile)) {
                        if (newTile.x >= 0 && newTile.y >= 0 && newTile.x < 20 && newTile.y < 20) {
                            if (mGame_.mpTileMap_->tiles[newTile.x][newTile.y].type != TileMap::Tile::Type::SEA) {
                                traverseQueue.push(std::make_pair(newTile, curr.second + 1));
                            }
                        }
                    }
                }
            }
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
        moves = maxMoves;
    }

    void Unit::doAction(int cost) {
        moves -= cost;
        if (moves < 0) {
            moves = 0;
        }
    }

    bool Unit::canSettle() {
        // if there is no settlement within 5 tiles, can settle
        bool ret = true;
        for (auto& eachSettlement: mGame_.getSettlementList()) {
            int distance = static_cast<int>(abs(mPosition_.x - eachSettlement->getPosition().x) + abs(mPosition_.y - eachSettlement->getPosition().y));
            if (distance < 5) {
                ret = false;
                break;
            }
        }
        return ret;
    }

} // namespace TurnStrategy