#include "VarioModel.h"
#include <Arduino.h>

void VarioModel::begin(const VarioConfig& cfg) {
    config = cfg;
}

float VarioModel::normalizeRate(float rate) {
    float x = rate / config.scale;

    // clamp symétrique
    if (x > 1.0f) x = 1.0f;
    if (x < -1.0f) x = -1.0f;

    return x;
}

float VarioModel::applyCurve(float x) {
    // courbe douce au début, agressive ensuite
    float sign = (x >= 0) ? 1.0f : -1.0f;

    float a = fabs(x);

    // courbe type perception humaine
    a = powf(a, 0.65f);

    return sign * a;
}

VarioAudioState VarioModel::computeUp(float x) {
    VarioAudioState s;

    // fréquence LXNav-like
    s.freq = config.baseFreq + (config.maxFreq - config.baseFreq) * x;

    // volume augmente avec montée
    s.volume = 0.3f + 0.7f * x;

    // duty cycle = bips plus fréquents
    s.duty = 0.15f + 0.85f * x;

    s.level = x;

    return s;
}

VarioAudioState VarioModel::computeDown(float x) {
    VarioAudioState s;

    // son plus grave
    s.freq = config.baseFreq * (0.6f - 0.3f * x);

    if (s.freq < 200) s.freq = 200;

    // volume modéré (évite agressivité)
    s.volume = 0.4f + 0.3f * x;

    // son continu (sink tone)
    s.duty = 1.0f;

    s.level = -x;

    return s;
}

VarioAudioState VarioModel::process(float rate) {
    float x = normalizeRate(rate);
    x = applyCurve(x);

    if (x >= 0) {
        return computeUp(x);
    } else {
        return computeDown(-x);
    }
}

