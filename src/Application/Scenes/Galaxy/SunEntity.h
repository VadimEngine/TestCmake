#pragma once
// project
#include "Entity.h"
#include "LightSource.h"
#include "ModelRenderable.h"

namespace galaxy {
    class SunEntity : public Entity {
    public:
        /**
         * @brief Construct a new Sun Entity
         *
         * @param scene Scene this sun is in
         */
        SunEntity(Scene& scene);

        /** Destructor */
        ~SunEntity();

        /** Get radius */
        float getRadius() const;

        /**
         * @brief Set Radius
         *
         * @param radius new radius
         */
        void setRadius(float radius);

        /** Get color */
        glm::vec4 getColor() const;

        /**
         * @brief Set Color
         *
         * @param color new color
         */
        void setColor(const glm::vec4& color);

        /** Get the light source for this entity */
        LightSource* getLightSource();

    private:
        /** Radius of this entity*/
        float mRadius_ = 1;
        /** Pointer to this Renderable of this entity */
        ModelRenderable* mpRenderable_ = nullptr;
        /** Light Source for this entity */
        LightSource mLight_;
    };
} // namespace galaxy