#pragma once
#include "IRenderable.h"
#include "Model.h"

class ModelRenderable : public IRenderable {
private:
    /**The Model of this Model Renderable */
    Model* mpModel_ = nullptr;
    
    /** The Shader used to draw this model */
    Shader* mpShader_ = nullptr;

    /** If the wire frames are also drawn*/
    bool drawWireframe_ = false;
public:

    /**
     * Constructor
     * \param pModel Model for this Renderable
     * \param pShader Shader used for this Renderable
     */
    ModelRenderable(Model* pModel, Shader* pShader);

    /** Destructor*/
    ~ModelRenderable();

    /**
     * Render this model
     * \param theRenderer Helper Renderer object
     * \param theCamera Camera to draw relative to
     * \param parentModelMat Model matrix with the model transforms
     */
    void render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const override;

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
     * Set if wireframes should be rendered
     * \param enable if wireframe rendering is enabled
     */
    void setWireframeRendering(const bool enable);

    /** Get the Model for this Renderable */
    Model* getModel() const;

    /** Get the Shader used for this Renderable */
    Shader* getShader() const;
};
