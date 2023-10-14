#include "App.h"
#include "Scene2d.h"

Scene2d::Scene2d(App& theApp)
    :Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this) {

    unsigned int texId = Texture::loadTexture("res/Sprites.png"); 

    mpSpriteSheet_ = new SpriteSheet(texId, {512, 512}, {16,16});
    mSprite1_ = new SpriteSheet::Sprite(mpSpriteSheet_, glm::ivec2(0, 0));
    mSprite2_ = new SpriteSheet::Sprite(mpSpriteSheet_, glm::ivec2(1, 0));

    mpFocusCamera_->setPosition({0,0,5});
}

Scene2d::~Scene2d() {
    delete mpFocusCamera_;
}

void Scene2d::update(const float dt) {
    mCameraController_.update(dt);
}

void Scene2d::render(Renderer& renderer) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::vec3 position1 = {0,0,0};
    glm::vec3 rotation1 = {0,0,0};
    glm::vec3 scale = {1,1,1};

    glm::vec3 position2 = {.6,.6,0};
    glm::vec3 rotation2 = {0,0,0};

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = mpFocusCamera_->getProjectionMatrix();
    glm::mat4 view = mpFocusCamera_->getViewMatrix();

    // translation matrix for position
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position1);
    //rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(rotation1.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation1.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation1.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    glm::mat4 model1 = translationMatrix * rotationMatrix * scaleMatrix;

    // translation matrix for position
    glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1.0f), position2);
    //rotation matrix
    glm::mat4 rotationMatrix2 = glm::rotate(glm::mat4(1), glm::radians(rotation2.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix2 = glm::rotate(rotationMatrix, glm::radians(rotation1.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix2 = glm::rotate(rotationMatrix, glm::radians(rotation1.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 model2 = translationMatrix2 * rotationMatrix2 * scaleMatrix;

    renderer.drawSprite(*mSprite1_, *mpFocusCamera_, model1);

    renderer.drawSprite(*mSprite2_, *mpFocusCamera_, model2);

    mGui_.render();

}
