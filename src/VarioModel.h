#pragma once

#include "VarioConfig.h"

struct VarioAudioState {
    float level = 0.0f;      // -1..+1
    float freq = 0.0f;       // Hz
    float volume = 0.0f;     // 0..1
    float duty = 0.0f;       // bip/silence ratio
};

class VarioModel {
public:
    void begin(const VarioConfig& cfg);

    VarioAudioState process(float rate);

private:
    VarioConfig config;

    float normalizeRate(float rate);
    float applyCurve(float x);
    VarioAudioState computeUp(float x);
    VarioAudioState computeDown(float x);
};