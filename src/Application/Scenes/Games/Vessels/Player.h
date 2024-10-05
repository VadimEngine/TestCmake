#pragma once
#include <string>
#include "Entity.h"

namespace vessels {

    class VesselsGame;

    class Player : public Entity {
    public:

        /**
         * @brief Construct a new Player object
         * 
         * @param theGame game this player is in
         */
        Player(VesselsGame& theGame);

        /**
         * Update player
         * @param dt Time since last update
         */
        void update(const float dt) override;

        void render(const Renderer& theRenderer) const override;

        void renderInMenu(const Renderer& theRenderer, const glm::vec2& guiPosition, const glm::vec3& scale, const glm::vec3& rotation);

        glm::vec3 getForward();

        glm::vec3 getRight();
        

    private:
        std::string mName_;
    };

} // namespace vessels
