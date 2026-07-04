#pragma once

struct VarioConfig {
    // dynamique du système (important pour ton usage domotique)
    float timeConstant = 10.0f;   // secondes (lent par défaut)
    
    // sensibilité de la variation
    float scale = 1.0f;

    // zone morte (évite bruit sonore inutile)
    float deadband = 0.01f;

    // fréquence audio de base
    int baseFreq = 800;

    // fréquence max
    int maxFreq = 2500;
};