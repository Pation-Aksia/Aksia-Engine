#include "ASound.h"

#include <iostream>

ASound::ASound(const std::string& dir) : directory(dir) {
    if(directory == "") {
        std::cerr << "Error: No directory provided!" << std::endl;
    } else {
        ASound::Load();
    }
}

ASound::ASound() : directory("") {}
ASound::~ASound() {}

std::ostream& operator<<(std::ostream& os, const ASound& i) {
    return os << i.directory;
}


void ASound::SetFile(const std::string& dir) {
    directory = dir;
    ASound::Load();
}

void ASound::Load() {
    data.clear();
    data.shrink_to_fit();

    if(directory == "") {
        std::cerr << "Error: ASound could not be loaded: no directory specified!" << std::endl;
        return;
    }

    std::cout << "No WAV handler written\nAborting load call. . ." << std::endl;
    //WAVHandler::LoadWAV(directory, length, sampleRate, data);
}


void ASound::SetSpeed(const float i) {
    speedMult = i;
}

void ASound::SetOutSampleRate(const float i) {
    outSampleRate = i;
}

void ASound::Play() {
    if(playing) {
        return;
    }
    playing = true;
    std::cout << "playing sound. . ." << std::endl;
}

void ASound::Pause() {
    if(!playing) {
        return;
    }
    playing = false;
    std::cout << "pausing sound. . ." << std::endl;
}

void ASound::Skip(const float i) { //skip to in seconds
    if(i < 0) {
        progressSeconds = 0.0f;
    } else if(i >= length) {
        progressSeconds = length;
    } else {
        progressSeconds = i;
    }

    if(length !=0) {
        progressPercent = (progressSeconds/length)*100.0f;
    }
}

void ASound::SkipPercent(const float i) {
    if(i < 0) {
        progressPercent = 0.0f;
    } else if(i >= 100.0f) {
        progressPercent = 100.0f;
    } else {
        progressPercent = i;
    }

    progressSeconds = length*(progressPercent*0.01f);
}

float ASound::GetProgress() const {
    return progressSeconds;
}
float ASound::GetProgressPercent() const {
    return progressPercent;
}
bool ASound::IsPlaying() const {
    return playing;
}