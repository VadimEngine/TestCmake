#pragma once
// project
#include "Entity.h"
#include "ModelRenderable.h"

namespace galaxy {
class PlanetEntity : public Entity {
public:
    /**
     * @brief Construct a new Planet Entity object
     *
     * @param scene Scene this Entity is in
     */
    PlanetEntity(Scene& scene);

    /** Destructor */
    ~PlanetEntity();

    /** Get Radius */
    float getRadius() const;

    /**
     * @brief Set the radius
     *
     * @param radius New Radius
     */
    void setRadius(float radius);

    /** Get the Color */
    glm::vec4 getColor() const;

    /** Set color */
    void setColor(const glm::vec4& color);

    /** Get the applied rotation speed*/
    float getRotationSpeed() const;

    /**
     * @brief Update the rotation speed
     *
     * @param rotation
     */
    void setRotationSpeed(float rotation);

private:
    /** Model radius */
    float mRadius_ = 0.5f;
    /** Speed this planet orbits the sun */
    float mOrbitRadius_ = 5.f;
    /** Speed this plant rotates around its center */
    float mRotationSpeed_ = 1.f;
    /** Pointer to the model renderable this Entity has */
    ModelRenderable* mpRenderable_ = nullptr;
};

} // namespace galaxy