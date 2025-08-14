#include "Simulation.h"
#include <iostream>
#include <sstream>   // Needed for std::stringstream
#include <string>    // For std::string
#include <cmath>
#include <cassert>   // C++ style assert

using namespace std;

/**
 * @brief Test case for simulating a collision between two vehicles.
 *
 * This function tests the simulation of two vehicles moving towards each other
 * and checks if the simulation correctly detects and reports a collision.
 *
 * The test performs the following steps:
 * 1. Sets up a simulation with specific test settings.
 * 2. Adds two vehicles moving towards each other.
 * 3. Runs the simulation.
 * 4. Checks the output for expected messages and vehicle positions.
 *
 * @note This test uses string matching to verify the simulation output.
 *
 * @see Simulation
 * @see Vehicle
 * @see Settings
 */
void testSimulationStartWithCollision() {
    // Set up test settings
    Settings testSettings;
    testSettings.timeStep = 0.1;
    testSettings.safetyDistance = 1.0;
    testSettings.enableLogging = true;

    // Create simulation with test settings
    Simulation sim(testSettings);

    // Add two vehicles moving towards each other
    Vehicle v1{1, 0, 0, 10, 0, 5};
    Vehicle v2{2, 1, 0, 10, 180, 5};
    sim.addVehicle(v1);
    sim.addVehicle(v2);

    // Capture console output
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    // Run the simulation
    sim.start();

    // Restore console output and get captured output as string
    std::string outputStr = output.str();
    std::cout.rdbuf(oldCout);

    // Verify simulation output
    assert(outputStr.find("🚗 Simulation started...") != std::string::npos);
    assert(outputStr.find("💥 [ALERT] Collision imminent! Stopping simulation.") != std::string::npos);
    assert(outputStr.find("Simulation ended. Status: Collision") != std::string::npos);
    assert(outputStr.find("Time: 0.1s") != std::string::npos);
    assert(outputStr.find("Vehicle 1 at (1, 0)") != std::string::npos);
    assert(outputStr.find("Vehicle 2 at (0.9, 0)") != std::string::npos);

    std::cout << "testSimulationStartWithCollision passed successfully." << std::endl;
}