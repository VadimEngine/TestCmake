#pragma once
#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>

class SoundDevice {
private:
    /** Pointer to found audio device */
    ALCdevice* mpALCDevice_;
    /** Pointer to context to allow track audio state*/
    ALCcontext* mpALCContext_;
public:
    /** Constructor */
    SoundDevice();
    /** Destructor */
    ~SoundDevice();
};