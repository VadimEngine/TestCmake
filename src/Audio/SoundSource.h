#pragma once
#define AL_LIBTYPE_STATIC
#include <AL\al.h>

class SoundSource {
private:
    /** Sound source id */
    ALuint mSource_;
    /** Sound source pitch */
    float mPitch_ = 1.f;
    /** Sound source gain */
    float mGain_ = 1.f;
    /** Sound source position */
    float mPosition_[3] = { 0,0,0 };
    /** Sound source velocity */
    float mVelocity[3] = { 0,0,0 };
    /** If sound source is looped */
    bool mLoopSound_ = false;
    /** Current assigned audio buffer */
    ALuint mBuffer_ = 0;

public:
    /** Constructor */
    SoundSource();

    /** Destructor */
    ~SoundSource();

    /** 
     * Play the audio of the given id
     * \param xPos X position of paddle
     */
    void play(const ALuint buffer_to_play);

    /**
     * Set the Gain of this source
     * \param newGain New gain setting
     */
    void setGain(float newGain);

    /** Get Gain of audio */
    float getGain() const;
    
    /** Get the id of this Source */
    ALuint getId() const;
};