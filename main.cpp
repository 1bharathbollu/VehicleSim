#include <iostream>
#include <limits>
#include "Simulation.h"

int main() {
    Settings s{1.0, 5.0, "m/s", true}; // Default: 1 sec step, 5 m safety, logging ON
    Simulation sim(s);

    int choice;
    do {
        std::cout << "\n=== Vehicle Simulation Menu ===\n";
        std::cout << "1. Add Vehicle\n";
        std::cout << "2. View Vehicles\n";
        std::cout << "3. Start Simulation\n";
        std::cout << "4. View History\n";
        std::cout << "5. Replay Run\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
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
            sim.viewVehicles();
        }
        else if (choice == 3) {
            sim.start();
        }
        else if (choice == 4) {
            sim.viewHistory();
        }
        else if (choice == 5) {
            int id;
            std::cout << "Run ID: "; std::cin >> id;
            sim.replayRun(id);
        }
    } while (choice != 0);

    std::cout << "Exiting program...\n";
    return 0;

}
