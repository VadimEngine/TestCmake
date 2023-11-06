#include "InputHandler.h"

// EVENT

InputHandler::KeyEvent::KeyEvent(Type type, unsigned int code)
    : type(type), code(code) {
}

bool InputHandler::KeyEvent::isPress() const {
    return type == Type::PRESS;
}

bool InputHandler::KeyEvent::isRelease() const {
    return type == Type::RELEASE;
}

unsigned int InputHandler::KeyEvent::getCode() const {
    return code;
}

// END OF EVENT

// Input Handler

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::onKeyPressed(int keyCode) {
    keyStates[keyCode] = true;
    keyQueue.push(InputHandler::KeyEvent(InputHandler::KeyEvent::Type::PRESS, keyCode));
    trimBuffer();
}

void InputHandler::onKeyReleased(int keyCode) {
    keyStates[keyCode] = false;
    keyQueue.push(InputHandler::KeyEvent(InputHandler::KeyEvent::Type::RELEASE, keyCode));
    trimBuffer();
}

bool InputHandler::isKeyPressed(int keyCode) const {
    return keyStates[keyCode];
}

void InputHandler::clearKeys() {
    keyStates.reset();
}

std::optional<InputHandler::KeyEvent> InputHandler::getKeyEvent() {
    if (keyQueue.size() > 0) {
        InputHandler::KeyEvent e = keyQueue.front();
        keyQueue.pop();
        return e;
    } else {
        return std::nullopt;
    }
}

void InputHandler::trimBuffer() {
    while (keyQueue.size() > maxKeyQueueSize) {
        keyQueue.pop();
    }
}

// End of Input Handler