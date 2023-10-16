#pragma once
#include "IRenderable.h"
#include "SpriteSheet.h"

class SpriteRenderable : public IRenderable {
private:
    /** The Sprite for this Renderable. */
    SpriteSheet::Sprite* mpSprite_;

public:
    /**
     * Constructor
     * \param pSprite Sprite for this Renderable
     */
    SpriteRenderable(SpriteSheet::Sprite* pSprite = nullptr);

    /** Destructor */
    ~SpriteRenderable();

    /**
     * Draw this renderable
     * \param theRenderer Helper Render object
     * \param theCamera Camera to draw relative to
     * \param parentModelMat Model matrix of the parent to render relative to
     */
    void render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const override;

    /**
     * Set the Sprite this Renderable will draw 
     * \param pSprite the Sprite
     */
    void setSprite(SpriteSheet::Sprite* pSprite);

    /** Get the Sprite for this Renderable */
    SpriteSheet::Sprite* getSprite() const;
};