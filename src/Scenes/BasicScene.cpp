#include "BasicScene.h"
#include "App.h"

BasicScene::BasicScene(App* theApp)
    : Scene(theApp), mCamera_({0,0,0}), cameraController(&mCamera_, mpApp_->getWindow()->getInputHandler()) {

    mpShader_ = new Shader("src/Shaders/MVPShader.vert", "src/Shaders/MVPShader.frag");

    // unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void BasicScene::update(float dt) {
    cameraController.update(dt);
}

void BasicScene::render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = mCamera_.getProjectionMatrix();
    glm::mat4 view = mCamera_.getViewMatrix();

    // Use Shader so uniforms are set on this shader
    mpShader_->bind();
    mpShader_->setMat4("model", model);
    mpShader_->setMat4("view", view);
    mpShader_->setMat4("projection", projection);
    mpShader_->setVec4("uColor", { 1.0f, 0.0f, 0.0f, 1.0f });

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 
}
