#include "Simulation.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <corecrt_math_defines.h>

Simulation::Simulation(Settings s)
    : settings(s), running(false), nextRunId(1) {}

void Simulation::addVehicle(const Vehicle& v) {
    vehicles.push_back(v);
}

void Simulation::viewVehicles() const {
    if (vehicles.empty()) {
        std::cout << "No vehicles available.\n";
        return;
    }
    for (const auto& v : vehicles) {
        std::cout << "ID: " << v.id
                  << " Pos(" << v.x << "," << v.y << ")"
                  << " Speed: " << v.speed
                  << " Dir: " << v.direction
                  << " Len: " << v.length << "\n";
    }
}

void Simulation::start() {
    if (vehicles.size() < 2) {
        std::cout << "Need at least 2 vehicles to start simulation.\n";
        return;
    }
    running = true;
    double elapsed = 0.0;

    RunRecord run;
    run.runId = nextRunId++;
    run.status = "Running";

    std::cout << "\n🚗 Simulation started...\n\n";

    while (running) {
        step(elapsed, run);

        // Show live positions
        std::cout << "Time: " << elapsed << "s\n";
        for (const auto& v : vehicles) {
            std::cout << "  Vehicle " << v.id 
                      << " at (" << v.x << ", " << v.y << ")\n";
        }
        std::cout << "---------------------------------\n" << std::flush;

        if (checkCollision(run.logs.back().positions)) {
            std::cout << "\n💥 [ALERT] Collision imminent! Stopping simulation.\n";
            run.status = "Collision";
            running = false;
        }

        // Sleep for timeStep seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(
            static_cast<int>(settings.timeStep * 1000)
        ));

        // TEMP: Stop after 20 seconds for demo so it doesn't run forever
        if (elapsed >= 5 && run.status == "Running") {
            std::cout << "\n⏹️  Max simulation time reached. Stopping.\n";
            running = false;
        }
    }

    if (run.status == "Running") run.status = "Stopped";
    pastRuns.push_back(run);

    std::cout << "\nSimulation ended. Status: " << run.status << "\n";
}

void Simulation::viewHistory() const {
    if (pastRuns.empty()) {
        std::cout << "No past runs.\n";
        return;
    }
    for (const auto& r : pastRuns) {
        std::cout << "Run ID: " << r.runId
                  << " Steps: " << r.logs.size()
                  << " Status: " << r.status << "\n";
    }
}

void Simulation::replayRun(int runId) const {
    for (const auto& r : pastRuns) {
        if (r.runId == runId) {
            std::cout << "\n=== Replay of Run " << r.runId << " ===\n";
            for (const auto& log : r.logs) {
                std::cout << "Time: " << log.time << "s\n";
                for (const auto& v : log.positions) {
                    std::cout << "  Vehicle " << v.id 
                              << " Pos(" << v.x << ", " << v.y << ")\n";
                }
                std::cout << "---------------------------------\n";
            }
            return;
        }
    }
    std::cout << "Run ID not found.\n";
}

void Simulation::step(double& elapsed, RunRecord& run) {
    elapsed += settings.timeStep;

    for (auto& v : vehicles) {
        double rad = v.direction * M_PI / 180.0;
        v.x += std::cos(rad) * v.speed * settings.timeStep;
        v.y += std::sin(rad) * v.speed * settings.timeStep;
    }

    if (settings.enableLogging) {
        LogEntry entry;
        entry.time = elapsed;
        entry.positions = vehicles;
        run.logs.push_back(entry);
    }
}

bool Simulation::checkCollision(const std::vector<Vehicle>& vehs) {
    for (size_t i = 0; i < vehs.size(); i++) {
        for (size_t j = i + 1; j < vehs.size(); j++) {
            double dx = vehs[i].x - vehs[j].x;
            double dy = vehs[i].y - vehs[j].y;
            double dist = std::sqrt(dx * dx + dy * dy);
            double minDist = std::max(vehs[i].length, vehs[j].length) + settings.safetyDistance;
            if (dist <= minDist) {
                return true;
            }
        }
    }
    return false;
}
