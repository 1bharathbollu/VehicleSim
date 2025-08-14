
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

/**
 * @brief Represents a vehicle in the simulation.
 *
 * This struct encapsulates all the properties of a vehicle necessary for the simulation,
 * including its identifier, position, speed, direction, and physical dimensions.
 */
struct Vehicle {
    int id;         /**< Unique identifier for the vehicle. */
    double x;       /**< X-coordinate of the vehicle's position. */
    double y;       /**< Y-coordinate of the vehicle's position. */
    double speed;   /**< Speed of the vehicle in meters per second (m/s). */
    double direction; /**< Direction of the vehicle in degrees. 0 degrees is East, 90 is North, etc. */
    double length;  /**< Length of the vehicle in meters. */

    /**
     * @brief Constructs a new Vehicle object.
     *
     * @param i The unique identifier for the vehicle.
     * @param X The initial X-coordinate of the vehicle.
     * @param Y The initial Y-coordinate of the vehicle.
     * @param sp The initial speed of the vehicle in m/s.
     * @param dir The initial direction of the vehicle in degrees.
     * @param len The length of the vehicle in meters.
     */
    Vehicle(int i=0, double X=0, double Y=0, double sp=0, double dir=0, double len=0)
        : id(i), x(X), y(Y), speed(sp), direction(dir), length(len) {}
};

#endif // VEHICLE_H