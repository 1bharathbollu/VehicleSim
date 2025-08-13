#include "Simulation.h"
#include <iostream>
#include <sstream>   // ✅ Needed for std::stringstream
#include <string>    // ✅ For std::string
#include <cmath>
#include <cassert>   // ✅ C++ style assert

using namespace std;

void testSimulationStartWithCollision() {
    Settings testSettings;
    testSettings.timeStep = 0.1;
    testSettings.safetyDistance = 1.0;
    testSettings.enableLogging = true;

    Simulation sim(testSettings);

    Vehicle v1{1, 0, 0, 10, 0, 5};
    Vehicle v2{2, 1, 0, 10, 180, 5};
    sim.addVehicle(v1);
    sim.addVehicle(v2);

    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    sim.start();

    std::string outputStr = output.str();
    std::cout.rdbuf(oldCout);

    // Check if simulation started message is present
    assert(outputStr.find("🚗 Simulation started...") != std::string::npos);

    // Check if collision alert message is present
    assert(outputStr.find("💥 [ALERT] Collision imminent! Stopping simulation.") != std::string::npos);

    // Check if simulation ended message is present
    assert(outputStr.find("Simulation ended. Status: Collision") != std::string::npos);

    // Check if at least one time step was printed
    assert(outputStr.find("Time: 0.1s") != std::string::npos);

    // Check if vehicle positions were updated
    assert(outputStr.find("Vehicle 1 at (1, 0)") != std::string::npos);
    assert(outputStr.find("Vehicle 2 at (0.9, 0)") != std::string::npos);

    std::cout << "testSimulationStartWithCollision passed successfully." << std::endl;
}
