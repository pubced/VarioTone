#pragma once

#include "VarioConfig.h"
#include "VarioModel.h"
#include "VarioSynth.h"
#include "VarioOutput.h"

enum class VarioMode {
    FLIGHT,     // rapide type LXNav
    THERMAL,    // mix
    HOME        // lent domotique
};

class VarioTone {
public:
    VarioTone();

    void begin();
    void update(float value);

    void setMode(VarioMode mode);
    void setConfig(const VarioConfig& cfg);

    void setVolume(float v);

private:
    VarioConfig config;

    VarioModel model;
    VarioSynth synth;
    VarioOutput output;

    VarioMode mode;

    float adaptRate(float rawRate);
};