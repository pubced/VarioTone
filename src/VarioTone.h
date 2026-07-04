#pragma once

#include "VarioConfig.h"

class VarioTone {
public:
    VarioTone();

    void begin();
    void update(float value);

    void setConfig(const VarioConfig& cfg);
    VarioConfig& getConfig();

private:
    VarioConfig config;

    float filteredValue = 0.0f;
    float lastFiltered = 0.0f;

    unsigned long lastTime = 0;

    float computeRate(float value, float dt);
    float filter(float value, float dt);
};