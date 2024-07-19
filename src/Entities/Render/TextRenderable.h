#pragma once
#include "BaseRenderable.h"

class TextRenderable : public BaseRenderable {
public:

    /**
     * @brief Constructor
     * 
     * @param text Text for rendering
     * @param font font used for rendering text
     */
    TextRenderable(const std::string& text = "", Font* font = nullptr);

    /** Destructor */
    ~TextRenderable();
    
    /**
     * @brief Render this renderable
     * 
     * @param theRenderer Render object
     * @param theCamera Camera to render relative to
     * @param parentModelMat Additional transformation from parent
     */
    void render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const override;

    /**
     * @brief Update the rendered text
     * 
     * @param text new text
     */
    void setText(const std::string& text);

    /**
     * @brief Update the used font
     * 
     * @param font new font
     */
    void setFont(Font* font);

private:
    /** Text rendered by this renderable */
    std::string mText_;
    /** Font used for the text */
    Font* mFont_;
};