#include "App.h"
#include "Scene2d.h"
#include <iostream>

Scene2d::Scene2d(App* theApp)
    :Scene(theApp), mGui_(this) {

    GLuint VBO;
    GLfloat vertices[] = {
        // position     // uv
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mpShader_ = new Shader("src/Shaders/Texture2d.vert", "src/Shaders/Texture2d.frag");

    texId = Texture::loadTexture("res/Sprites.png"); 

    theSpriteSheet = new SpriteSheet(texId, {512, 512}, {16,16});
    theSprite = new SpriteSheet::Sprite(theSpriteSheet, glm::ivec2(0, 0));
    theSprite2 = new SpriteSheet::Sprite(theSpriteSheet, glm::ivec2(1, 0));


    mFocusCamera_->move({0,0,1}, 5);
}

void Scene2d::update(const float dt) {

}

void Scene2d::render(Renderer& renderer) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //renderer.drawSprite(*mFocusCamera_);

    glm::vec3 position1 = {0,0,0};
    glm::vec3 rotation1 = {0,0,0};
    glm::vec3 scale = {1,1,1};

    glm::vec3 position2 = {.6,.6,0};
    glm::vec3 rotation2 = {0,0,0};


    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = mFocusCamera_->getProjectionMatrix();
    glm::mat4 view = mFocusCamera_->getViewMatrix();


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


    //renderer.drawSprite(*mFocusCamera_, model1);
    //renderer.drawSprite(*mFocusCamera_, model2);
    renderer.drawSprite(*theSprite, *mFocusCamera_, model1);

    renderer.drawSprite(*theSprite2, *mFocusCamera_, model2);



    mGui_.render();

}
