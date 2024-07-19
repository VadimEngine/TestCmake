// forward declare headers first
#include "App.h"
// class header
#include "PongGame.h"

namespace pong {
    const std::string PongGame::kInitalMsg = "Press Space to Begin";
    const std::string PongGame::kPauseMsg = "Paused. Press Space to Resume";
    const std::string PongGame::kEndMsg = "Game Over! Press Space to Continue";

    PongGame::PongGame(Scene& scene)
    : mScene_(scene),
      mApp_(mScene_.getApp()),
      mInputHandler_(mApp_.getWindow().getInputHandler()) {
        mScene_.getFocusCamera()->setMode(Camera::CameraMode::ORTHOGONAL);
        mScene_.getFocusCamera()->setPosition({0,0,1});

        // Build left paddle
        mPaddles_[0] = std::make_unique<Paddle>(mScene_, glm::vec2{mProperties_.leftPaddle.width, mProperties_.leftPaddle.height});
        mPaddles_[0]->setDefaultPosition({mProperties_.leftPaddle.startX, mProperties_.leftPaddle.startY});

        // build right paddle
        mPaddles_[1] = std::make_unique<Paddle>(mScene_, glm::vec2{mProperties_.rightPaddle.width, mProperties_.rightPaddle.height});
        mPaddles_[1]->setDefaultPosition({mProperties_.rightPaddle.startX, mProperties_.rightPaddle.startY});
        
        // move paddles to default position
        mPaddles_[0]->reset();
        mPaddles_[1]->reset();

        // build ball
        mBall_ = std::make_unique<Ball>(mScene_, mProperties_.ballRadius);

        mEntities_.push_back(mPaddles_[0].get());
        mEntities_.push_back(mPaddles_[1].get());
        mEntities_.push_back(mBall_.get());
    }

    PongGame::~PongGame() {}

    void PongGame::update(const float dt) {
        handleKeyUpdate(dt);
        if (mCurrentState_ == GameState::PLAYING) {
            for (int i = 0; i < mEntities_.size(); ++i) {
                mEntities_[i]->update(dt);
            }
            glm::vec3 ballPos = mBall_->getPosition();
            if (ballPos.x < -mProperties_.boardSize.x/2 || ballPos.x > mProperties_.boardSize.x/2) {
                // If the ball is out of left/right bound
                // Set score
                if (ballPos.x < mProperties_.boardSize.x/2) {
                    ++mScores_[0];
                } else {
                    ++mScores_[1];
                }
                // Rest ball and start it into opposite direction
                mBall_->setPosition({0,0,0});
                glm::vec3 newBallDir = -glm::normalize(mBall_->getVelocity());
                mBall_->reset();
                mBall_->start(newBallDir);
            }
            // If end of game
            if (mScores_[0] == mProperties_.maxScore || mScores_[1] == mProperties_.maxScore) {
                mCurrentState_ = GameState::END;
                mBall_->reset();
            }
        }
        // Separate overlapping entities
        handleEntityOverlap();
    }

    void PongGame::render(Renderer& renderer, Camera& camera) {
        for (const auto& entity: mEntities_) {
            entity->render(renderer, camera);
        }
        // Display Game title
        renderer.renderText(
            "PONG",
            {350.0f, 500.0f},
            *(mApp_.getResources().getResource<Font>("Consolas")),
            1.0f,
            {1.f, 1.f, 1.f}
        );

        glm::vec2 windowDimension = mApp_.getWindow().getWindowDimensions();
        // Display game state specific text
        std::string renderString;
        if (mCurrentState_ == GameState::INITIAL) {
            renderString = kInitalMsg;
        } else if (mCurrentState_ == GameState::PLAYING) {
            renderString = std::to_string(mScores_[0]) + ":" + std::to_string(mScores_[1]);
        } else if (mCurrentState_ == GameState::PAUSE) {
            renderString = kPauseMsg;
        } else if (mCurrentState_ == GameState::END) {
            renderString = kEndMsg;
        }
        renderer.renderTextCentered(
            renderString,
            {windowDimension.x/2.f, 400.0f},
            *(mApp_.getResources().getResource<Font>("Consolas")),
            .5f,
            {1.f, 1.f, 1.f, 1.f}
        );
        // render scores in addition to message
        if (mCurrentState_ == GameState::END) {
            std::string playMsg = std::to_string(mScores_[0]) + ":" + std::to_string(mScores_[1]);
            renderer.renderTextCentered(
                playMsg,
                {windowDimension.x/2.f, 350.0f},
                *(mApp_.getResources().getResource<Font>("Consolas")),
                .5f,
                {1.f, 1.f, 1.f, 1.f}
            );
        }

    }

    void PongGame::handleKeyUpdate(float dt) {
        if (mCurrentState_ == GameState::PLAYING) {
            // Move paddles with key updates
            // Left paddle
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_7)) {
                mPaddles_[0]->moveUp(dt);
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_1)) {
                mPaddles_[0]->moveDown(dt);
            }
            // right paddle
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_9)) {
                mPaddles_[1]->moveUp(dt);
            }
            if (mInputHandler_.isKeyPressed(GLFW_KEY_KP_3)) {
                mPaddles_[1]->moveDown(dt);
            }
        }
    }

    void PongGame::onKeyPress(unsigned int code) {
        // Update Game State with from key event
        if (code == GLFW_KEY_SPACE) {
            if (mCurrentState_ == GameState::INITIAL) {
                mBall_->start({1,1,0});
                mCurrentState_ = GameState::PLAYING;
            } else if (mCurrentState_ == GameState::PLAYING) {
                mCurrentState_ = GameState::PAUSE;
            } else if (mCurrentState_ == GameState::PAUSE) {
                mCurrentState_ = GameState::PLAYING;
            } else if (mCurrentState_ == GameState::END) {
                // Reset
                mPaddles_[0]->reset();
                mPaddles_[1]->reset();
                mBall_->reset();
                mScores_ = {0,0};

                mCurrentState_ = GameState::INITIAL;
            }
        }
    }

    void PongGame::onKeyRelease(unsigned int code) {}

    glm::vec2 PongGame::getBoardSize() const {
        return mProperties_.boardSize;
    }

    void PongGame::handleEntityOverlap() {
        // Separate any overlap and handle paddle-ball collision
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
                            // paddle-ball collision
                            if (mEntities_[i] == mBall_.get() || mEntities_[j] == mBall_.get()) {
                                mApp_.getAudioManger().playSound(mScene_.getApp().getResources().getResource<Audio>("Blip1")->getId());
                                mBall_->setVelocity(
                                    glm::reflect(mBall_->getVelocity(), glm::normalize( glm::vec3{1,0,0}))
                                );
                                mBall_->setSpeed(mBall_->getSpeed() * 1.1f);
                            }

                        }
                    }
                }
            }
        }
    }

} // namespace pong