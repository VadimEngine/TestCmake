#pragma once
#include "SoundDevice.h"
#include "SoundSource.h"
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>
#include <unordered_map>
#include <string>

class AudioManager {
private:
    /** Map of loaded audios */
    static std::unordered_map<std::string, ALuint> sLoadedAudio_;
    /** Sound Device*/
    SoundDevice* mSoundDevice_;
    /** Sound Source */
    SoundSource* mSoundSource_;
public:
    /** Load a preset list of audio */
    static void loadAudios();

    /** Release all the loaded audios */
    static void freeLoadedAudios();

    /**
     * Load an audio from the given file path
     * \param filename sound file path
     */
    static ALuint loadAudioFile(const char* filename);

    /** Constructor */
    AudioManager();

    /** Destructor */
    ~AudioManager();
    
    /**
     *  Play the audio if it has been loaded
     * \param soundName Name of the audio to play
     */
    void playSound(std::string soundName);

    /** 
     * Set the gain of the audio source
     * \param newGain Gain to set (0-1.0f)
     */
    void setGain(float newGain);

    /** Get the current Gain */
    float getGain() const;
};