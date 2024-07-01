#include "PhysicsScene.h"
#include "App.h"

PhysicsScene::PhysicsScene(App& theApp)
    : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this) {
    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,0,5});

    mCircleModel_.addSharedMesh(mApp_.getResources().getResource<Mesh>("CircularPlane"));
    mRectModel_.addSharedMesh(mApp_.getResources().getResource<Mesh>("RectPlane"));

    Entity* theEntity1 = new Entity(*this);
    theEntity1->addRenderable(new ModelRenderable(&mCircleModel_, getApp().getResources().getResource<Shader>("Assimp")));
    RigidBodyComponent* rigid1  = theEntity1->addPhysicsComponent<RigidBodyComponent>();
    rigid1->getCollider().setShape(ColliderOLD::Shape::CIRCLE);
    rigid1->setMobile(true);
    rigid1->setAttractive(true);
    mEntities_.push_back(theEntity1);

    // floor
    Entity* theEntity3 = new Entity(*this);
    theEntity3->addRenderable(new ModelRenderable(&mRectModel_, getApp().getResources().getResource<Shader>("Assimp")));
    theEntity3->setPosition({0.f, -10.f, 0.f});
    theEntity3->setScale({10.f, 1.f, 1.f});
    RigidBodyComponent* rigid3 = theEntity3->addPhysicsComponent<RigidBodyComponent>();
    rigid3->getCollider().setShape(ColliderOLD::Shape::RECTANGLE);
    rigid3->setMobile(false);
    rigid3->setAttractive(false);
    mEntities_.push_back(theEntity3);
}

PhysicsScene::~PhysicsScene() {
    delete mpFocusCamera_;
    for (auto& eachEntity : mEntities_) {
        delete eachEntity;
    }
}

void PhysicsScene::update(const float dt) {
    mCameraController_.update(dt);
    if (mIsRunning_) {
        handleEntityCollision(dt);
        for (int i = 0; i < mEntities_.size(); i++) {
            mEntities_[i]->update(dt);
        }
    }
    handleEntityOverlap();
}

void PhysicsScene::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }
    mGui_.render();
}

std::vector<Entity*>& PhysicsScene::getEntities() {
    return mEntities_;
}

void PhysicsScene::addEntity() {
    Entity* newEntity = new Entity(*this);
    newEntity->addRenderable(new ModelRenderable(&mCircleModel_, getApp().getResources().getResource<Shader>("Assimp")));
    RigidBodyComponent* rigid = newEntity->addPhysicsComponent<RigidBodyComponent>();
    rigid->getCollider().setShape(ColliderOLD::Shape::CIRCLE);
    rigid->setMobile(true);
    rigid->setAttractive(true);

    mEntities_.push_back(newEntity);
}

void PhysicsScene::handleEntityCollision(const float dt) {
    for (int i = 0; i < mEntities_.size(); i++) {
        RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); j++) {
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
    for (int i = 0; i < mEntities_.size(); i++) {
        RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); j++) {
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
