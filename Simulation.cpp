
#include "Simulation.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <corecrt_math_defines.h>

/**
 * @brief Constructs a new Simulation object.
 * 
 * Initializes the simulation with the given settings, sets the running flag to false,
 * and initializes the nextRunId to 1.
 * 
 * @param s The settings to use for this simulation.
 */
Simulation::Simulation(Settings s)
    : settings(s), running(false), nextRunId(1) {}

/**
 * @brief Adds a new vehicle to the simulation.
 * 
 * This method appends a new vehicle to the list of vehicles in the simulation.
 * 
 * @param v The Vehicle object to be added to the simulation.
 */
void Simulation::addVehicle(const Vehicle& v) {
    vehicles.push_back(v);
}

/**
 * @brief Displays information about all vehicles currently in the simulation.
 * 
 * This method prints the details of each vehicle, including its ID, position,
 * speed, direction, and length. If no vehicles are present, it displays a
 * message indicating that no vehicles are available.
 */
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

/**
 * @brief Starts the simulation.
 * 
 * This method initiates and runs the main simulation loop. It checks for the minimum
 * number of vehicles, initializes the simulation state, and then enters a loop where it:
 * 1. Advances the simulation by one time step
 * 2. Displays the current positions of all vehicles
 * 3. Checks for collisions
 * 4. Pauses for a short time to control the simulation speed
 * 
 * The simulation continues until a collision occurs, the maximum simulation time
 * is reached, or an external stop condition is met.
 */
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

        // TEMP: Stop after 5 seconds for demo so it doesn't run forever
        if (elapsed >= 5 && run.status == "Running") {
            std::cout << "\n⏹️  Max simulation time reached. Stopping.\n";
            running = false;
        }
    }

    if (run.status == "Running") run.status = "Stopped";
    pastRuns.push_back(run);

    std::cout << "\nSimulation ended. Status: " << run.status << "\n";
}

/**
 * @brief Displays the history of past simulation runs.
 * 
 * This method prints information about all past simulation runs, including
 * their run ID, number of steps, and final status. If no past runs are
 * available, it displays a message indicating so.
 */
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

/**
 * @brief Replays a specific simulation run.
 * 
 * This method searches for a past run with the given runId and, if found,
 * displays a step-by-step replay of that simulation run, showing the positions
 * of all vehicles at each logged time step.
 * 
 * @param runId The ID of the run to replay.
 */
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

/**
 * @brief Advances the simulation by one time step.
 * 
 * This method updates the positions of all vehicles based on their current
 * speed and direction. It also logs the new state if logging is enabled.
 * 
 * @param elapsed Reference to the total elapsed time of the simulation.
 * @param run Reference to the current run record.
 */
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

/**
 * @brief Checks for collisions between vehicles.
 * 
 * This method iterates through all pairs of vehicles and calculates the
 * distance between them. If any pair of vehicles is closer than the sum
 * of their lengths plus the safety distance, a collision is detected.
 * 
 * @param vehs The vector of vehicles to check for collisions.
 * @return true if a collision is detected, false otherwise.
 */
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