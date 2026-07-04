#include "VarioOutput.h"
#include <driver/ledc.h>

#define PWM_CHANNEL 0
#define PWM_PIN 25
#define PWM_RES 8
#define PWM_FREQ 20000

void VarioOutput::begin(OutputMode m) {
    mode = m;

    if (mode == OutputMode::PWM) {
        ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
        ledcAttachPin(PWM_PIN, PWM_CHANNEL);
    }
}

void VarioOutput::writeSample(float sample) {

    sample = smoothSample(sample);

    int pwm = (int)((sample * 0.5f + 0.5f) * 255.0f);

    pwm = constrain(pwm, 0, 255);

    ledcWrite(PWM_CHANNEL, pwm);
}

float VarioOutput::smoothSample(float s) {
    // filtre anti-crack (très important en PWM)
    lastSample += 0.25f * (s - lastSample);
    return lastSample;
}