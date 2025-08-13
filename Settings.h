#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct Settings {
    double timeStep;        // seconds
    double safetyDistance;  // meters
    std::string speedUnit;  // "m/s" or "km/h"
    bool enableLogging;
};

#endif
