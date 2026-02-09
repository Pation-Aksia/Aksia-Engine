#ifndef _AKSI_SOUND_CH_
#define _AKSI_SOUND_CH_

#include <vector>
#include <string>

#include <iosfwd>

enum class SoundType {
    NONE = 0,
    MUSIC = 1,
    SFX = 2
};

class ASound {
private:

    std::vector<float> data;

    SoundType type = SoundType::NONE;
    float length = 0.0f;
    float sampleRate = 0.0f;
    float outSampleRate = 0.0f; //live playback resampling (thanks to pipewire :3)
    float speedMult = 1.0f;
    float progressSeconds = 0.0f;
    float progressPercent = 0.0f;
    bool playing = false;

    std::string directory;

public:
    ASound(const std::string& dir = "");
    ASound();
    ~ASound();

    friend std::ostream& operator<<(std::ostream& os, const ASound& i);


    void SetFile(const std::string& dir = "");

    void Load();


    void SetSpeed(const float i);

    void SetOutSampleRate(const float i);

    void Play();
    void Pause();
    void Skip(const float i);
    void SkipPercent(const float i);

    float GetProgress() const;
    float GetProgressPercent() const;
    bool IsPlaying() const;
};

#endif