#pragma once
// project
#include "Entity.h"
#include "ModelRenderable.h"

namespace galaxy {
    class MoonEntity : public Entity {
    public:
        /**
         * @brief Construct a new Moon Entity object
         *
         * @param mScene Scene this entity is in
         */
        MoonEntity(Scene& mScene);

        /** Destructor */
        ~MoonEntity();

        /** Get Model Radius*/
        float getRadius() const;

        /**
         * @brief Set the model radius
         *
         * @param radius new radius
         */
        void setRadius(float radius);

        /** Get Color of model */
        glm::vec4 getColor() const;

        /**
         * @brief Set color of Model
         *
         * @param color new Color
         */
        void setColor(const glm::vec4& color);

        /** Set the speed this Entity rotates around its center */
        float getRotationSpeed() const;

        /**
         * @brief Set the speed this plant rotates around its center
         *
         * @param rotation
         */
        void setRotationSpeed(float rotation);

    private:
        /** Radius of the model */
        float mRadius_ = 0.25f;
        /** Radius this entity orbits around another entity */
        float mOrbitRadius_ = 1.f;
        /** Speed this entity rotates around another entity */
        float mRotationSpeed_ = 12.f;
        /** Pointer to the model renderable this Entity has */
        ModelRenderable* mpRenderable_ = nullptr;
    };

} // namespace galaxy