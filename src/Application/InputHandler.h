#pragma once

// TODO make child keyboardInput/mouseInput class?
class InputHandler {

public:
    // TODO use this class in a input queue 
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
private:
    /**
     * Array of currently pressed keys
     * Maybe use a bitset
     */
    bool mKeyPressed_[1024] = {0};
public:
    /** Constructor */
    InputHandler();

    /** Destructor*/
    ~InputHandler();
    
    /** 
     * Track the key that is pressed
     * \param keyCode Keycode for pressed key
     */
    void onKeyPressed(int keyCode);

    /**
     * Track the key that is released
     * \param keyCode Keycode for pressed key
     */
    void onKeyReleased(int keyCode);

    /** Check if a key is marked as pressed */
    bool isKeyPressed(int keyCode) const;

    // when losing focus
    /**
     * Set all tracked keys as not pressed. Used when losing focus on application 
     */
    void clearKeys();
};

