#include "VarioTone.h"
#include <Arduino.h>

VarioTone::VarioTone() {}

void VarioTone::begin() {

    model.begin(config);
    synth.begin(SynthMode::PWM);
    output.begin(OutputMode::PWM);

    mode = VarioMode::HOME;
}

void VarioTone::setConfig(const VarioConfig& cfg) {
    config = cfg;

    model.begin(cfg);
}

void VarioTone::setVolume(float v) {
    synth.setVolume(v);
}

void VarioTone::setMode(VarioMode m) {
    mode = m;

    switch (mode) {

        case VarioMode::FLIGHT:
            config.timeConstant = 1.0f;
            config.scale = 2.0f;
            break;

        case VarioMode::THERMAL:
            config.timeConstant = 10.0f;
            config.scale = 0.5f;
            break;

        case VarioMode::HOME:
            config.timeConstant = 60.0f;
            config.scale = 0.2f;
            break;
    }

    model.begin(config);
}

float VarioTone::adaptRate(float rawRate) {
    return rawRate * config.scale;
}

void VarioTone::update(float value) {

    // =========================
    // 1. MODEL (physique → audio)
    // =========================

    VarioAudioState state = model.process(value);

    // =========================
    // 2. ADAPTATION MODE
    // =========================

    switch (mode) {

        case VarioMode::HOME:
            // amortissement supplémentaire (très lent)
            state.duty *= 0.6f;
            break;

        case VarioMode::THERMAL:
            // équilibré
            state.duty *= 0.85f;
            break;

        case VarioMode::FLIGHT:
            // plus nerveux
            state.duty *= 1.0f;
            break;
    }

    // =========================
    // 3. SYNTHÈSE SONORE
    // =========================

    synth.update(state);

    // =========================
    // 4. SORTIE AUDIO
    // =========================

    // (le synth écrit déjà dans output via PWM/I2S dans #0004)
}