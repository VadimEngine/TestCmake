#pragma once
#include "BaseRenderable.h"
#include "Model.h"
#include <unordered_map>

class ModelRenderable : public BaseRenderable {
private:
    /**The Model of this Model Renderable */
    const Model* mpModel_ = nullptr;
    
    /** The Shader used to draw this model */
    const Shader* mpShader_ = nullptr;

    /** Map of texture ids and the uniform name for the shader*/
    std::unordered_map<unsigned int, unsigned int> mTextureIdByUnit_;

    /** If the wire frames are also drawn*/
    bool drawWireframe_ = false;

public:
    /**
     * Constructor
     * \param pModel Model for this Renderable
     * \param pShader Shader used for this Renderable
     */
    ModelRenderable(const Model* pModel = nullptr, const Shader* pShader = nullptr);

    /** Destructor*/
    ~ModelRenderable();

    /**
     * Render this model
     * \param theRenderer Helper Renderer object
     * \param theCamera Camera to draw relative to
     * \param parentModelMat Model matrix with the model transforms
     */
    void render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const override;

    /** Get the Model for this Renderable */
    const Model* getModel() const;

    /** Get the Shader used for this Renderable */
    const Shader* getShader() const;

    /**
     * Set the model this Renderable will draw 
     * \param pModel the Model
     */
    void setModel(Model* pModel);

    /**
     * Set the Shader this Renderable will use
     * \param pShader the Shader
     */
    void setShader(Shader* pShader);

    /**
     * Set a texture when rendering this renderable with the assign Texture unit
     * \param textureUnit The unit this texture is binded to
     * \param textureId texture Id
     */
    void setTexture(unsigned int textureUnit, unsigned int textureId);

    /**
     * Set if wireframes should be rendered
     * \param enable if wireframe rendering is enabled
     */
    void setWireframeRendering(const bool enable);
};
