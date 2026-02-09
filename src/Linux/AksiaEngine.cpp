#include "AksiaEngine.h"

#include <chrono>

double ATime::startTime = std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();

double ATime::elapsedTime = 0.0;
double ATime::systemTime = 0.0;
double ATime::deltaTime = 0.0;

//void Init() {}

void AEngine::Loop(Display* dis) {
    AEvent::MandatoryUpdate(dis);

    ATime::deltaTime = std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count() - ATime::systemTime;
    ATime::systemTime = std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    ATime::elapsedTime = ATime::systemTime - ATime::startTime;
}