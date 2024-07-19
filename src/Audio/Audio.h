#pragma once
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>
#include <string>
#include <filesystem>

class Audio {
public:
    static int loadAudio(const std::filesystem::path& filename);

    Audio(const std::filesystem::path& filePath);

    ~Audio();

    int getId();

private:
    ALuint mId_;
};