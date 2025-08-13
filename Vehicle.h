#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    int id;
    double x;
    double y;
    double speed;      // m/s
    double direction;  // degrees
    double length;     // meters

    Vehicle(int i=0, double X=0, double Y=0, double sp=0, double dir=0, double len=0)
        : id(i), x(X), y(Y), speed(sp), direction(dir), length(len) {}
};

#endif
