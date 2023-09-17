#pragma once

// TODO make child keyboardInput/mouseInput class?
class InputHandler {

public:
    class Event {
    public:
        enum class Type {
            PRESS, RELEASE, INVALID
        };
    private:
        Type type;
        unsigned char code;
    public:
        Event(Type type, unsigned char code);
        bool isPress() const;
        bool isRelease() const;
        bool isInvalid() const;
        unsigned char getCode() const;
    };

    // array of pressed keys
    // input queue
    // Maybe use a bitset
    bool mKeyPressed_[1024] = {0};

    InputHandler();
    ~InputHandler();

    void onKeyPressed(int keyCode);

    void onKeyReleased(int keyCode);

    bool isKeyPressed(int keyCode) const;

    // when losing focus
    void clearKeys();
};

