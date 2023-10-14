#pragma once
#include "IRenderable.h"
#include "SpriteSheet.h"

class SpriteRenderable : public IRenderable {
private:
    /** The Sprite for this Renderable. */
    SpriteSheet::Sprite* mpSprite_;

public:
    /**
     * \param pSprite Sprite for this Renderable
     */
    SpriteRenderable(SpriteSheet::Sprite* pSprite);

    ~SpriteRenderable();

    void render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const override;

    /**
     * Set the Sprite this Renderable will draw 
     * \param pSprite the Sprite
     */
    void setSprite(SpriteSheet::Sprite* pSprite);

    /** Get the Sprite for this Renderable */
    SpriteSheet::Sprite* getSprite() const;
};