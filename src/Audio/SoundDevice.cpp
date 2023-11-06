#include "SoundDevice.h"

SoundDevice::SoundDevice() {
    mpALCDevice_ = alcOpenDevice(nullptr); // nullptr = get default device
    if (!mpALCDevice_) {
        throw("failed to get sound device");
    }
    mpALCContext_ = alcCreateContext(mpALCDevice_, nullptr);  // create context
    if (!mpALCContext_) {
        throw("Failed to set sound context");
    }
    if (!alcMakeContextCurrent(mpALCContext_)) {  // make context current
        throw("failed to make context current");
    }
    const ALCchar* name = nullptr;
    if (alcIsExtensionPresent(mpALCDevice_, "ALC_ENUMERATE_ALL_EXT")) {
        name = alcGetString(mpALCDevice_, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(mpALCDevice_) != AL_NO_ERROR) {
        name = alcGetString(mpALCDevice_, ALC_DEVICE_SPECIFIER);
    }
    printf("Opened \"%s\"\n", name);
}

SoundDevice::~SoundDevice() {
    if (!alcMakeContextCurrent(nullptr)) {
        throw("failed to set context to nullptr");
    }
    alcDestroyContext(mpALCContext_);
    if (mpALCContext_) {
        throw("failed to unset during close");
    }
    if (!alcCloseDevice(mpALCDevice_)) {
        throw("failed to close sound device");
    }
}