#pragma once

class PhysicsComponentBase {
public:
    /** Physics Component types*/
    enum class ComponentType {
        RIGID_BODY
    };

    /** If this Component is enabled (update is applied)*/
    bool mEnabled_ = true;

    virtual void update(float dt) = 0;

    /**
     * Set if this Component is enabled
     * \param isEnabled New enabled value
     */
    void setEnabled(const bool isEnabled);

    /** Get if this Component is enabled */
    bool isEnabled() const;

    /** Get the type of Physics Component */
    virtual ComponentType getType() const = 0;
};