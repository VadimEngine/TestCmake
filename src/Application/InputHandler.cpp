#include "InputHandler.h"

//EVENT

InputHandler::Event::Event(Type type, unsigned char code)
    : type(type), code(code) {
}

bool InputHandler::Event::isPress() const {
    return type == Type::PRESS;
}

bool InputHandler::Event::isRelease() const {
    return type == Type::RELEASE;
}

bool InputHandler::Event::isInvalid() const {
    return type == Type::INVALID;
}

unsigned char InputHandler::Event::getCode() const {
    return code;
}

//END OF EVENT

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::onKeyPressed(int keyCode) {
    mKeyPressed_[keyCode] = true;
}

void InputHandler::onKeyReleased(int keyCode) {
    mKeyPressed_[keyCode] = false;
}

bool InputHandler::isKeyPressed(int keyCode) const {
    return mKeyPressed_[keyCode];
}

// when losing focus
void InputHandler::clearKeys() {
    for (int i = 0; i < 1024; i++) {
        mKeyPressed_[i] = false;
    }
}
