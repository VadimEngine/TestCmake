#pragma once
#include "SoundDevice.h"
#include "SoundSource.h"
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>
#include <unordered_map>
#include <string>
#include "Resource.h"

class AudioManager {
private:
    /** Sound Device*/
    SoundDevice* mSoundDevice_;
    /** Sound Source */
    SoundSource* mSoundSource_;
public:
    /** Constructor */
    AudioManager();

    /** Destructor */
    ~AudioManager();

    /**
     * Play the audio if it has been loaded
     * @param audioId Audio buffer id
     */
    void playSound(ALuint audioId);

    /**
     * Set the gain of the audio source
     * @param newGain Gain to set (0-1.0f)
     */
    void setGain(float newGain);

    /** Get the current Gain */
    float getGain() const;
};