#include <VarioTone.h>

VarioTone vario;

void setup() {
    Serial.begin(115200);
    vario.begin();

    VarioConfig cfg;
    cfg.timeConstant = 30.0f; // parfait pour température maison
    cfg.scale = 1.0f;

    vario.setConfig(cfg);
}

void loop() {
    // simulation température lente
    float temp = 20.0 + 2.0 * sin(millis() / 60000.0);

    vario.update(temp);

    delay(100);
}