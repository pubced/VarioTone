#pragma once

#include <Arduino.h>

enum class OutputMode {
    PWM,
    I2S
};

class VarioOutput {
public:
    void begin(OutputMode mode);

    void writeSample(float sample); // -1..+1

    void setVolume(float v);

private:
    OutputMode mode;

    float volume = 0.5f;
    float lastSample = 0.0f;

    float smoothSample(float s);
};