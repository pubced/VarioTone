#pragma once

#include "VarioModel.h"

enum class SynthMode {
    PWM,
    I2S
};

class VarioSynth {
public:
    void begin(SynthMode mode = SynthMode::PWM);

    void update(const VarioAudioState& state);

    void setVolume(float v);

private:
    SynthMode mode;

    float phase = 0.0f;
    float volume = 0.5f;

    // ADSR interne
    float envelope = 0.0f;
    float envTarget = 0.0f;

    float sampleRate = 22050.0f;

    float generateSample(float freq);
    float applyEnvelope(float sample);
};