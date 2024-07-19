#include "BasicScene.h"
#include "App.h"

namespace basic_scene {
    BasicScene::BasicScene(App& theApp)
        : Scene(theApp),
        mCameraController_(getFocusCamera(),
        mApp_.getWindow().getInputHandler()),
        mGui_(*this),
        mSprite_(*mApp_.getResources().getResource<SpriteSheet>("SpriteSheet1"), glm::ivec2(0, 0)) {
        // load/build resources
        assembleResources();

        mBackgroundColor_ = {.4,.4,.4,1.f};
        getFocusCamera()->setPosition({0,.1,5});

        // First Entity
        {
            std::unique_ptr<Entity> theEntity1 = std::make_unique<Entity>(*this);
            // Solid cube properties
            ModelRenderable* solidCubeRenderable = theEntity1->addRenderable<ModelRenderable>();
            solidCubeRenderable->setModel(mResources_.getResource<Model>("Cube"));
            solidCubeRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));

            solidCubeRenderable->setWireframeRendering(true);
            solidCubeRenderable->setColor({.3f, .3f, .3f, 1.0f});
            // Set sprite properties
            SpriteRenderable* spriteRenderable = theEntity1->addRenderable<SpriteRenderable>();
            spriteRenderable->setSprite(&mSprite_);
            spriteRenderable->setColor({.3f, 0.f, 0.f, 1.0f});
            spriteRenderable->setPosition({0.f, 1.f, 0.f});
            // First entity properties
            theEntity1->setPosition({0.f, .5f, 0.f});
            mEntities_.push_back(std::move(theEntity1));
        }
        // Second Entity
        {
            std::unique_ptr<Entity> theEntity2 = std::make_unique<Entity>(*this);
            ModelRenderable* textureCubeRenderable = theEntity2->addRenderable<ModelRenderable>();
            textureCubeRenderable->setModel(mResources_.getResource<Model>("Cube"));
            textureCubeRenderable->setShader(getApp().getResources().getResource<Shader>("MVPTexShader"));
            // Texture cube properties
            textureCubeRenderable->setTexture(
                0,
                mApp_.getResources().getResource<Texture>("SampleTexture")->getId(),
                "texture0"
            );

            // Second Entity properties
            theEntity2->setPosition({3.f, .5f, 0.f});
            mEntities_.push_back(std::move(theEntity2));
        }
        // Third Entity (Floor)
        {
            std::unique_ptr<Entity> floorEntity = std::make_unique<Entity>(*this);
            ModelRenderable* floorRenderable = floorEntity->addRenderable<ModelRenderable>();
            floorRenderable->setModel(mResources_.getResource<Model>("RectPlane"));
            floorRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));
            // Plane Renderable properties
            floorRenderable->setRotation({-90, 0, 0});
            floorRenderable->setScale({10, 10, 0});
            floorRenderable->setColor({0.f, 0.f, 0.f, 1.0f});
            // Add renderable to floor entity
            mEntities_.push_back(std::move(floorEntity));
        }
        // Forth Entity (Sphere)
        {
            std::unique_ptr<Entity> assimpEntity = std::make_unique<Entity>(*this);
            ModelRenderable* assimpRenderable = assimpEntity->addRenderable<ModelRenderable>();
            assimpRenderable->setModel(mResources_.getResource<Model>("Sphere"));
            assimpRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));

            assimpEntity->setPosition({0.f, 5.f, 0.f});
            mEntities_.push_back(std::move(assimpEntity));
        }
        // Fifth Entity (Textured rectangle)
        {
            std::unique_ptr<Entity> planeTextureEntity = std::make_unique<Entity>(*this);
            ModelRenderable* planeTextureRenderable = planeTextureEntity->addRenderable<ModelRenderable>();
            planeTextureRenderable->setModel(mResources_.getResource<Model>("RectPlane"));
            planeTextureRenderable->setShader(getApp().getResources().getResource<Shader>("TextureSurface"));
            // Texture. TODO allow imgui set this from list of textures
            planeTextureRenderable->setTexture(
                1,
                mApp_.getResources().getResource<Texture>("SpriteSheet")->getId(),
                "uTexture"
            );
            planeTextureRenderable->setSubTextureTopLeft({0.f, 0.f});
            planeTextureRenderable->setSubTextureSize({16.f/512.f, 16.f/512.f});

            planeTextureEntity->setPosition({-2.f, 2.f, 0.f});
            mEntities_.push_back(std::move(planeTextureEntity));
        }
        // Sixth Entity (Text rectangle)
        {
            std::unique_ptr<Entity> entity = std::make_unique<Entity>(*this);
            TextRenderable* textRenderable = entity->addRenderable<TextRenderable>();
            textRenderable->setText("TEST STRING");
            textRenderable->setFont(mApp_.getResources().getResource<Font>("Consolas"));
            textRenderable->setScale({.1f, .1f, 1});
            textRenderable->setColor({1, 0, 0, 1});

            mEntities_.push_back(std::move(entity));
        }
    }

    BasicScene::~BasicScene() {}

    void BasicScene::update(float dt) {
        mCameraController_.update(dt);
    }

    void BasicScene::render(Renderer& renderer) {
        for (int i = 0; i < mEntities_.size(); ++i) {
            mEntities_[i]->render(renderer, *getFocusCamera());
        }
        mGui_.render();
    }

    void BasicScene::assembleResources() {
        // Cube
        std::unique_ptr<Model> cubeModel = std::make_unique<Model>();
        cubeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("Cube")
        );
        mResources_.addResource(std::move(cubeModel), "Cube");
        // Plane
        std::unique_ptr<Model> planeModel = std::make_unique<Model>();;
        planeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(planeModel), "RectPlane");
        // Sphere
        std::unique_ptr<Model> sphereModel = std::make_unique<Model>();;
        sphereModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("Sphere")
        );
        mResources_.addResource(std::move(sphereModel), "Sphere");
    }

    std::vector<std::unique_ptr<Entity>>& BasicScene::getEntities() {
        return mEntities_;
    }
} // namespace basic_scene