#include <iostream>
#include <cmath>
#include "Simulation.h"

bool almostEqual(double a, double b, double epsilon=1e-5) {
    return std::fabs(a - b) < epsilon;
}

// === Existing tests ===
void testAddVehicle() {
    std::cout << "[TEST] AddVehicle\n";
    Settings s{1.0, 5.0, "m/s", true};
    Simulation sim(s);
    Vehicle v{1, 0, 0, 20, 90, 5};
    sim.addVehicle(v);
    sim.viewVehicles();
    std::cout << "Test AddVehicle complete.\n\n";
}

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

// === New tests ===

// 1. Collision detection test
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

// 2. No collision test
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

// 3. History tracking test
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

// 4. Replay run test
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

int main() {
    testAddVehicle();
    testPositionUpdate();
    testCollisionDetection();
    testNoCollision();
    testHistoryRecording();
    testReplayRun();
    return 0;
}
