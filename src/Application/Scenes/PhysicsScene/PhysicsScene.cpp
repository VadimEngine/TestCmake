// forward declare
#include "App.h"
// class
#include "PhysicsScene.h"

namespace physics_scene {
PhysicsScene::PhysicsScene(App& theApp)
    : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this) {
    assembleResources();
    mBackgroundColor_ = {0,0,0, 1.f};
    getFocusCamera()->setPosition({0,0,5});
    // First particle
    {
        Entity* theEntity = new Entity(*this);
        ModelRenderable* modelRenderable = theEntity->addRenderable<ModelRenderable>();
        modelRenderable->setModel(mResources_.getResource<Model>("CircularPlane"));
        modelRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));
        RigidBodyComponent* rigid = theEntity->addPhysicsComponent<RigidBodyComponent>();
        rigid->getCollider().setShape(ColliderOLD::Shape::CIRCLE);
        rigid->setMobile(true);
        rigid->setAttractive(true);
        mEntities_.emplace_back(theEntity);
    }
    // floor
    {
        Entity* theEntity = new Entity(*this);
        ModelRenderable* modelRenderable = theEntity->addRenderable<ModelRenderable>();
        modelRenderable->setModel(mResources_.getResource<Model>("RectPlane"));
        modelRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));
        theEntity->setPosition({0.f, -10.f, 0.f});
        theEntity->setScale({10.f, 1.f, 1.f});
        RigidBodyComponent* rigid = theEntity->addPhysicsComponent<RigidBodyComponent>();
        rigid->getCollider().setShape(ColliderOLD::Shape::RECTANGLE);
        rigid->setMobile(false);
        rigid->setAttractive(false);
        mEntities_.emplace_back(theEntity);
    }
}

PhysicsScene::~PhysicsScene() {}

void PhysicsScene::update(const float dt) {
    mCameraController_.update(dt);
    if (mIsRunning_) {
        handleEntityCollision(dt);
        for (int i = 0; i < mEntities_.size(); ++i) {
            mEntities_[i]->update(dt);
        }
    }
    handleEntityOverlap();
}

void PhysicsScene::render(Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
}

void PhysicsScene::renderGUI() {
    mGui_.render();
}

std::vector<std::unique_ptr<Entity>>& PhysicsScene::getEntities() {
    return mEntities_;
}

void PhysicsScene::addEntity(const glm::vec3 position) {
    Entity* newEntity = new Entity(*this);
    newEntity->setPosition(position);
    ModelRenderable* modelRenderable = newEntity->addRenderable<ModelRenderable>();
    modelRenderable->setModel(mResources_.getResource<Model>("CircularPlane"));
    modelRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));

    RigidBodyComponent* rigid = newEntity->addPhysicsComponent<RigidBodyComponent>();
    rigid->getCollider().setShape(ColliderOLD::Shape::CIRCLE);
    rigid->setMobile(true);
    rigid->setAttractive(true);

    mEntities_.emplace_back(newEntity);
}

void PhysicsScene::assembleResources() {
    // Circle Plane Model
    std::unique_ptr<Model> circleModel = std::make_unique<Model>();
    circleModel->addSharedMesh(
        mApp_.getResources().getResource<Mesh>("CircularPlane")
    );
    mResources_.addResource(std::move(circleModel), "CircularPlane");
    // Rectangle Plane Model
    std::unique_ptr<Model> rectModel = std::make_unique<Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
}

void PhysicsScene::handleEntityCollision(const float dt) {
    for (int i = 0; i < mEntities_.size(); ++i) {
        RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); ++j) {
                RigidBodyComponent* rigidBodyB = mEntities_[j]->getPhysicsComponent<RigidBodyComponent>();
                if (rigidBodyB != nullptr) {
                    rigidBodyA->handleIfCollision(rigidBodyB);
                    rigidBodyA->applyIfAttraction(rigidBodyB, dt);
                }
            }
        }
    }
}

void PhysicsScene::handleEntityOverlap() {
    // Separate any overlap
    for (int i = 0; i < mEntities_.size(); ++i) {
        RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); ++j) {
                RigidBodyComponent* rigidBodyB = mEntities_[j]->getPhysicsComponent<RigidBodyComponent>();
                if (rigidBodyB != nullptr) {
                    auto mvt = rigidBodyA->getCollider().getCollisionMVT(&(rigidBodyB->getCollider()));
                    if (mvt.has_value()) {
                        glm::vec3 newPos1 = mEntities_[i]->getPosition() + mvt.value();
                        glm::vec3 newPos2 = mEntities_[j]->getPosition() - mvt.value();

                        if (rigidBodyA->isMobile()) {
                            mEntities_[i]->setPosition(newPos1);
                        }

                        if (rigidBodyB->isMobile()) {
                            mEntities_[j]->setPosition(newPos2);
                        }
                    }
                }
            }
        }
    }
}
} // namespace physics_scene