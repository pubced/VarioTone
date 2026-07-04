#include "VarioSynth.h"
#include <Arduino.h>

void VarioSynth::begin(SynthMode m) {
    mode = m;
    phase = 0;

    // PWM ou I2S init sera ajouté au commit #0004
}

float VarioSynth::applyEnvelope(float sample) {
    // attaque douce
    envelope += (envTarget - envelope) * 0.15f;

    return sample * envelope * volume;
}

float VarioSynth::generateSample(float freq) {
    phase += freq / sampleRate;

    if (phase > 1.0f) phase -= 1.0f;

    float s = sinf(2 * PI * phase);

    // harmonique douce (signature vario)
    s += 0.35f * sinf(2 * PI * phase * 2);
    s += 0.15f * sinf(2 * PI * phase * 3);

    return s;
}

void VarioSynth::update(const VarioAudioState& state) {

    static float dutyCounter = 0;
    float active = (dutyCounter < state.duty) ? 1.0f : 0.0f;

    dutyCounter += 0.02f;
    if (dutyCounter > 1.0f) dutyCounter = 0;

    if (!active) {
        output.writeSample(0.0f);
        return;
    }

    envTarget = state.volume;

    float sample = generateSample(state.freq);

    sample = applyEnvelope(sample);

    output.writeSample(sample);
}

