
#include <iostream>
#include <limits>
#include "Simulation.h"

/**
 * @brief The main entry point of the Vehicle Simulation program.
 *
 * This function sets up the simulation environment and provides a menu-driven
 * interface for the user to interact with the simulation. It allows users to:
 * - Add vehicles to the simulation
 * - View existing vehicles
 * - Start the simulation
 * - View history of past simulation runs
 * - Replay a specific simulation run
 *
 * The program runs in a loop until the user chooses to exit.
 *
 * @return int Returns 0 on successful execution.
 */
int main() {
    // Initialize simulation settings
    Settings s{1.0, 5.0, "m/s", true}; // Default: 1 sec step, 5 m safety, logging ON
    Simulation sim(s);

    int choice;
    do {
        // Display menu options
        std::cout << "\n=== Vehicle Simulation Menu ===\n";
        std::cout << "1. Add Vehicle\n";
        std::cout << "2. View Vehicles\n";
        std::cout << "3. Start Simulation\n";
        std::cout << "4. View History\n";
        std::cout << "5. Replay Run\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        // Process user choice
        if (choice == 1) {
            // Add a new vehicle
            Vehicle v;
            std::cout << "Vehicle ID: "; std::cin >> v.id;
            std::cout << "Initial X: "; std::cin >> v.x;
            std::cout << "Initial Y: "; std::cin >> v.y;
            std::cout << "Speed (" << s.speedUnit << "): "; std::cin >> v.speed;
            std::cout << "Direction (degrees): "; std::cin >> v.direction;
            std::cout << "Length (m): "; std::cin >> v.length;

            sim.addVehicle(v);
            std::cout << "Vehicle added successfully.\n";
        }
        else if (choice == 2) {
            // View existing vehicles
            sim.viewVehicles();
        }
        else if (choice == 3) {
            // Start the simulation
            sim.start();
        }
        else if (choice == 4) {
            // View history of past runs
            sim.viewHistory();
        }
        else if (choice == 5) {
            // Replay a specific run
            int id;
            std::cout << "Run ID: "; std::cin >> id;
            sim.replayRun(id);
        }
    } while (choice != 0);

    std::cout << "Exiting program...\n";
    return 0;
}