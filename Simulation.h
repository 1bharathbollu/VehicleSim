#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "Settings.h"
#include <vector>
#include <string>

/**
 * @brief Represents a single log entry in the simulation.
 *
 * This struct stores the state of all vehicles at a specific point in time
 * during the simulation.
 */
struct LogEntry {
    double time; /**< The simulation time at which this log entry was created. */
    std::vector<Vehicle> positions; /**< The positions and states of all vehicles at this time. */
};

/**
 * @brief Represents a complete record of a simulation run.
 *
 * This struct stores all the information about a single simulation run,
 * including its unique identifier, status, and a log of vehicle positions
 * throughout the simulation.
 */
struct RunRecord {
    int runId; /**< Unique identifier for this simulation run. */
    std::string status; /**< The final status of the simulation (e.g., "Running", "Collision", "Stopped"). */
    std::vector<LogEntry> logs; /**< A chronological log of vehicle positions throughout the simulation. */
};

/**
 * @brief The main simulation class that manages vehicles and runs the simulation.
 *
 * This class is responsible for managing vehicles, running the simulation,
 * detecting collisions, and maintaining a history of simulation runs.
 */
class Simulation {
private:
    Settings settings; /**< Configuration settings for the simulation. */
    std::vector<Vehicle> vehicles; /**< List of vehicles in the current simulation. */
    std::vector<RunRecord> pastRuns; /**< History of past simulation runs. */
    bool running; /**< Flag indicating whether the simulation is currently running. */
    int nextRunId; /**< The ID to be assigned to the next simulation run. */

public:
    /**
     * @brief Constructs a new Simulation object.
     * 
     * @param s The settings to use for this simulation.
     */
    Simulation(Settings s);

    /**
     * @brief Adds a new vehicle to the simulation.
     * 
     * @param v The vehicle to add.
     */
    void addVehicle(const Vehicle& v);

    /**
     * @brief Displays information about all vehicles currently in the simulation.
     */
    void viewVehicles() const;

    /**
     * @brief Starts the simulation.
     * 
     * This method runs the simulation until a collision occurs or the maximum
     * simulation time is reached. It updates vehicle positions, checks for
     * collisions, and logs the simulation state at each time step.
     */
    void start();

    /**
     * @brief Displays the history of past simulation runs.
     */
    void viewHistory() const;

    /**
     * @brief Replays a specific simulation run.
     * 
     * @param runId The ID of the run to replay.
     */
    void replayRun(int runId) const;

    /**
     * @brief Public wrapper for the step method, used for testing.
     * 
     * @param elapsed Reference to the elapsed time variable.
     * @param run Reference to the current run record.
     */
    void publicStep(double& elapsed, RunRecord& run) { step(elapsed, run); }

    /**
     * @brief Getter for the vehicles vector, used for testing.
     * 
     * @return const std::vector<Vehicle>& A constant reference to the vehicles vector.
     */
    const std::vector<Vehicle>& getVehicles() const { return vehicles; }

private:
    /**
     * @brief Advances the simulation by one time step.
     * 
     * @param elapsed Reference to the elapsed time variable.
     * @param run Reference to the current run record.
     */
    void step(double& elapsed, RunRecord& run);

    /**
     * @brief Checks for collisions between vehicles.
     * 
     * @param vehs The vector of vehicles to check for collisions.
     * @return true if a collision is detected, false otherwise.
     */
    bool checkCollision(const std::vector<Vehicle>& vehs);
};

#endif // SIMULATION_H