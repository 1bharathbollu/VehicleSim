
#include <iostream>
#include <cmath>
#include "Simulation.h"

/**
 * @brief Compares two double values for approximate equality.
 * 
 * @param a First value to compare.
 * @param b Second value to compare.
 * @param epsilon Maximum allowed difference between a and b.
 * @return true if the values are approximately equal, false otherwise.
 */
bool almostEqual(double a, double b, double epsilon=1e-5) {
    return std::fabs(a - b) < epsilon;
}

/**
 * @brief Tests the addition of a vehicle to the simulation.
 * 
 * This test adds a vehicle to the simulation and verifies that it can be viewed.
 */
void testAddVehicle() {
    std::cout << "[TEST] AddVehicle\n";
    Settings s{1.0, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v{1, 0, 0, 20, 90, 5};
    sim.addVehicle(v);
    sim.viewVehicles();
    std::cout << "Test AddVehicle complete.\n\n";
}

/**
 * @brief Tests the position update of a vehicle after one time step.
 * 
 * This test adds a vehicle to the simulation, advances one time step,
 * and verifies that the vehicle's position has been updated correctly.
 */
void testPositionUpdate() {
    std::cout << "[TEST] PositionUpdate\n";
    Settings s{1.0, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v{1, 0, 0, 10, 0, 2}; // Moves along +X axis
    sim.addVehicle(v);
    double elapsed = 0.0;
    RunRecord run{1, "Running", {}};
    sim.publicStep(elapsed, run);
    auto pos = run.logs.back().positions[0];
    if (almostEqual(pos.x, 10.0)) {
        std::cout << "PASS: Position updated to x=" << pos.x << "\n";
    } else {
        std::cout << "FAIL: Position was x=" << pos.x << "\n";
    }
    std::cout << "Test PositionUpdate complete.\n\n";
}

/**
 * @brief Tests the collision detection mechanism.
 * 
 * This test adds two vehicles close to each other and verifies
 * that a collision is detected.
 */
void testCollisionDetection() {
    std::cout << "[TEST] CollisionDetection\n";
    Settings s{1.0, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v1{1, 0, 0, 0, 0, 2};
    Vehicle v2{2, 1, 1, 0, 0, 2}; // Distance ~1.41m, less than safety distance+length
    sim.addVehicle(v1);
    sim.addVehicle(v2);

    double elapsed = 0.0;
    RunRecord run{1, "Running", {}};
    sim.publicStep(elapsed, run);

    // Directly check using positions from run log
    bool collision = false;
    const auto& vehs = run.logs.back().positions;
    for (size_t i = 0; i < vehs.size(); i++) {
        for (size_t j = i+1; j < vehs.size(); j++) {
            double dx = vehs[i].x - vehs[j].x;
            double dy = vehs[i].y - vehs[j].y;
            double dist = std::sqrt(dx*dx + dy*dy);
            double minDist = std::max(vehs[i].length, vehs[j].length) + s.safetyDistance;
            if (dist <= minDist) collision = true;
        }
    }

    if (collision)
        std::cout << "PASS: Collision detected.\n";
    else
        std::cout << "FAIL: Collision not detected.\n";

    std::cout << "Test CollisionDetection complete.\n\n";
}

/**
 * @brief Tests that no collision is detected when vehicles are far apart.
 * 
 * This test adds two vehicles far from each other and verifies
 * that no collision is detected.
 */
void testNoCollision() {
    std::cout << "[TEST] NoCollision\n";
    Settings s{1.0, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v1{1, 0, 0, 0, 0, 2};
    Vehicle v2{2, 100, 100, 0, 0, 2};
    sim.addVehicle(v1);
    sim.addVehicle(v2);

    double elapsed = 0.0;
    RunRecord run{1, "Running", {}};
    sim.publicStep(elapsed, run);

    const auto& vehs = run.logs.back().positions;
    bool collision = false;
    for (size_t i = 0; i < vehs.size(); i++) {
        for (size_t j = i+1; j < vehs.size(); j++) {
            double dx = vehs[i].x - vehs[j].x;
            double dy = vehs[i].y - vehs[j].y;
            double dist = std::sqrt(dx*dx + dy*dy);
            double minDist = std::max(vehs[i].length, vehs[j].length) + s.safetyDistance;
            if (dist <= minDist) collision = true;
        }
    }

    if (!collision)
        std::cout << "PASS: No collision as expected.\n";
    else
        std::cout << "FAIL: Unexpected collision detected.\n";

    std::cout << "Test NoCollision complete.\n\n";
}

/**
 * @brief Tests the history recording functionality of the simulation.
 * 
 * This test runs a simulation and then checks if the history has been recorded.
 */
void testHistoryRecording() {
    std::cout << "[TEST] HistoryRecording\n";
    Settings s{0.1, 5.0, "m/s", true}; // small step
    Simulation sim(s);
    Vehicle v1{1, 0, 0, 1, 0, 2};
    Vehicle v2{2, 10, 0, -1, 180, 2};
    sim.addVehicle(v1);
    sim.addVehicle(v2);
    sim.start();
    sim.viewHistory();
    std::cout << "Test HistoryRecording complete.\n\n";
}

/**
 * @brief Tests the replay functionality of the simulation.
 * 
 * This test runs a simulation and then attempts to replay the first run.
 */
void testReplayRun() {
    std::cout << "[TEST] ReplayRun\n";
    Settings s{0.5, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v1{1, 0, 0, 1, 0, 2};
    Vehicle v2{2, 20, 0, -1, 180, 2};
    sim.addVehicle(v1);
    sim.addVehicle(v2);
    sim.start();
    sim.replayRun(1); // first run
    std::cout << "Test ReplayRun complete.\n\n";
}

/**
 * @brief Main function to run all manual tests.
 * 
 * This function calls all the test functions in sequence.
 * 
 * @return int Returns 0 on successful execution of all tests.
 */
int main() {
    testAddVehicle();
    testPositionUpdate();
    testCollisionDetection();
    testNoCollision();
    testHistoryRecording();
    testReplayRun();
    return 0;
}