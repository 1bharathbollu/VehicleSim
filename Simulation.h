#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "Settings.h"
#include <vector>
#include <string>

struct LogEntry {
    double time;
    std::vector<Vehicle> positions;
};

struct RunRecord {
    int runId;
    std::string status;
    std::vector<LogEntry> logs;
};

class Simulation {
private:
    Settings settings;
    std::vector<Vehicle> vehicles;
    std::vector<RunRecord> pastRuns;
    bool running;
    int nextRunId;

public:
    Simulation(Settings s);
    void addVehicle(const Vehicle& v);
    void viewVehicles() const;
    void start();
    void viewHistory() const;
    void replayRun(int runId) const;

    // ✅ Added public wrappers for testing
    void publicStep(double& elapsed, RunRecord& run) { step(elapsed, run); }
    const std::vector<Vehicle>& getVehicles() const { return vehicles; }

private:
    void step(double& elapsed, RunRecord& run);
    bool checkCollision(const std::vector<Vehicle>& vehs);
};

#endif
