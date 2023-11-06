#pragma once
#include <queue>
#include <bitset>
#include <optional>
#include <GLFW/glfw3.h>

// TODO make child keyboardInput/mouseInput class?
class InputHandler {

public:
    class KeyEvent {
    public:
        enum class Type {
            PRESS, RELEASE
        };
    private:
        Type type;
        unsigned int code;
    public:
        KeyEvent(Type type, unsigned int code);
        bool isPress() const;
        bool isRelease() const;
        unsigned int getCode() const;
    };
private:
    /** Number of key codes to check status of*/
    static constexpr unsigned int nKeys = 512;
    /** Max number of key events in the event queue */
    static constexpr unsigned int maxKeyQueueSize = 16;

	/** Bit set to track which keys are currently pressed*/
    std::bitset<nKeys> keyStates;
    /** Queue of key events to use for single updates on a key event */
    std::queue<KeyEvent> keyQueue;
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

    /**
     * Set all tracked keys as not pressed. Used when losing focus on application 
     */
    void clearKeys();

    std::optional<KeyEvent> getKeyEvent();

private:
    /** Helper method to keep keyBuffer within the size limit */
    void trimBuffer();
};