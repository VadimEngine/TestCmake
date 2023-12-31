#include "PongGame.h"
#include "App.h"

namespace Pong {
    PongGame::PongGame(App& app) 
    : mPaddleLeft_(-5.f, 5.f, -5.f), mPaddleRight_(5.f, 5.f, -5.f), 
    mApp_(app), mInputHandler_(app.getWindow().getInputHandler()) {
        mEntities_.push_back(&mPaddleLeft_);
        mEntities_.push_back(&mPaddleRight_);
        mEntities_.push_back(&mBall_);
    }

    PongGame::~PongGame() {}

    void PongGame::update(const float dt) {
        handleKeyUpdate(dt);
        handleEntityCollision(dt);
        if (currentState == GameState::PLAYING) {
            for (int i = 0; i < mEntities_.size(); i++) {
                mEntities_[i]->update(dt);
            }
            glm::vec3 ballPos = mBall_.getPosition();
            if (ballPos.x < -5 || ballPos.x > 5) {
                // If the ball is out of left/right bound
                // Set score
                if (ballPos.x < -5) {
                    leftScore++;
                } else {
                    rightScore++;
                }
                // Rest ball and start it into opposite direction
                mBall_.setPosition({0,0,0});
                glm::vec3 newBallDir = -glm::normalize(mBall_.getVelocity());
                mBall_.reset();
                mBall_.start(newBallDir); 
            }
            // If end of game
            if (leftScore == maxScore || rightScore == maxScore) {
                currentState = GameState::END;
                mBall_.reset();
            }
        }
        // Separate overlapping entities
        handleEntityOverlap();
    }

    void PongGame::render(Renderer& renderer, Camera& camera) {
        for (int i = 0; i < mEntities_.size(); i++) {
            mEntities_[i]->render(renderer, camera);
        }
        // Display text
        renderer.renderText("PONG", {350.0f, 500.0f}, 1.0f, {1.f, 1.f, 1.f});

        glm::vec2 windowDimension = mApp_.getWindow().getWindowDimensions();

        if (currentState == GameState::INITIAL) {
            renderer.renderTextCentered(initalMsg, {windowDimension.x/2.f, 400.0f}, .5f, {1.f, 1.f, 1.f, 1.f});
        } else if (currentState == GameState::PLAYING) {
            std::string playMsg = std::to_string(leftScore) + ":" + std::to_string(rightScore);
            renderer.renderTextCentered(playMsg,  {windowDimension.x/2.f, 400.0f}, .5f, {1.f, 1.f, 1.f, 1.f});
        } else if (currentState == GameState::PAUSE) {
            renderer.renderTextCentered(pauseMsg, {windowDimension.x/2.f, 400.f}, .5f, {1.f, 1.f, 1.f, 1.f});
        } else if (currentState == GameState::END) {
            renderer.renderTextCentered(endMsg,  {windowDimension.x/2.f, 400.0f}, .5f, {1.f, 1.f, 1.f, 1.f});
            std::string playMsg = std::to_string(leftScore) + ":" + std::to_string(rightScore);
            renderer.renderTextCentered(playMsg, {windowDimension.x/2.f, 350.0f}, .5f, {1.f, 1.f, 1.f, 1.f});
        }
    }

    void PongGame::handleKeyUpdate(float dt) {
        if (currentState == GameState::PLAYING) {
            // Move paddles with key updates
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_7)) {
                mPaddleLeft_.moveUp(dt);
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_1)) {
                mPaddleLeft_.moveDown(dt);
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_9)) {
                mPaddleRight_.moveUp(dt);
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_3)) {
                mPaddleRight_.moveDown(dt);
            }
        }
    }

    void PongGame::onKeyPress(unsigned int code) {
        if (!ImGuiComponent::keyboardGUIFocus()) {
            // Update Game State with from key event
            if (code == GLFW_KEY_SPACE) {
                if (currentState == GameState::INITIAL) {
                    mBall_.start({1,1,0});
                    currentState = GameState::PLAYING;
                } else if (currentState == GameState::PLAYING) {
                    currentState = GameState::PAUSE;
                } else if (currentState == GameState::PAUSE) {
                    currentState = GameState::PLAYING;
                } else if (currentState == GameState::END) {
                    // Reset
                    mPaddleLeft_.reset();
                    mPaddleRight_.reset();
                    mBall_.reset();
                    leftScore = 0;
                    rightScore = 0;

                    currentState = GameState::INITIAL;
                }
            }
        }
    }

    void PongGame::onKeyRelease(unsigned int code) {}

    void PongGame::handleEntityOverlap() {
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

    void PongGame::handleEntityCollision(const float dt) {
        RigidBodyComponent* paddleLeftRigid = mPaddleLeft_.getPhysicsComponent<RigidBodyComponent>();
        RigidBodyComponent* paddleRightRigid = mPaddleRight_.getPhysicsComponent<RigidBodyComponent>();
        RigidBodyComponent* ballRigid = mBall_.getPhysicsComponent<RigidBodyComponent>();

        if (paddleLeftRigid->handleIfCollision(ballRigid) || paddleRightRigid->handleIfCollision(ballRigid)) {
            // bounce paddle of paddle
            mApp_.getAudioManger().playSound("Blip1");
            mBall_.setSpeed(mBall_.getSpeed() * 1.1f);
        }
    }

} // namespace Pong