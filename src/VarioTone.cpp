#include "VarioTone.h"
#include <Arduino.h>

VarioTone::VarioTone() {}

void VarioTone::begin() {
    lastTime = millis();
    filteredValue = 0;
    lastFiltered = 0;
}

void VarioTone::setConfig(const VarioConfig& cfg) {
    config = cfg;
}

VarioConfig& VarioTone::getConfig() {
    return config;
}

float VarioTone::filter(float value, float dt) {
    float alpha = dt / (config.timeConstant + dt);
    filteredValue += alpha * (value - filteredValue);
    return filteredValue;
}

float VarioTone::computeRate(float value, float dt) {
    float rate = (value - lastFiltered) / dt;
    lastFiltered = value;
    return rate;
}

void VarioTone::update(float value) {
    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0f;
    if (dt <= 0) return;

    lastTime = now;

    float f = filter(value, dt);
    float rate = computeRate(f, dt);

    // zone morte
    if (fabs(rate) < config.deadband) {
        rate = 0;
    }

    // TODO commit #0002 :
    // - mapping rate -> audio level
    // - synthèse sonore
}