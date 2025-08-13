

## **README.md**

```markdown
#  Vehicle Simulation (C++17, No Database)

##  Overview
This is a **console-based vehicle simulation system** written in **C++17** that manages multiple vehicles, simulates their movement over time, detects potential collisions, logs simulation runs, and allows replay of past runs — all **without a database**.  
Everything is stored in **memory** during runtime.

---

##  Features
- **Vehicle Management**
  - Add new vehicles with ID, position, speed, direction, and length.
  - View the list of all current vehicles.

- **Simulation Engine**
  - Time-step based movement updates using basic kinematics.
  - Detects "Collision Imminent" events when vehicles are too close.
  - Auto-stop either when collision is detected OR when maximum simulation time reached.
  - Step-by-step position printing for live monitoring.

- **History & Replay**
  - Saves every completed simulation run in memory.
  - View past history (Run ID, Steps, Status).
  - Replay any previous run with per-step positions.

- **Testing**
  - Includes **ManualTests** executable with PASS/FAIL output for core logic (no external libraries like GoogleTest).

---

##  Project Structure

```
VehicleSimNoDB/
│
├── main.cpp              # Interactive console simulation
├── Vehicle.h / .cpp      # Vehicle struct definition
├── Settings.h            # Simulation configuration parameters
├── Simulation.h / .cpp   # Main simulation logic + wrappers for testing
├── ManualTests.cpp       # Simple PASS/FAIL unit tests without external libs
├── CMakeLists.txt        # Build configuration for VehicleSim & ManualTests
└── README.md             # This documentation
```

---

## ⚙ Requirements
- **C++17 compatible compiler** (g++, clang++, MSVC)
- **CMake 3.10+**
- Works on Windows, Linux, macOS (console-based)

---

##  Build Instructions

### 1 Clone the project
```
git clone 
cd VehicleSimNoDB
```

### 2 Create a build folder
```
mkdir build
cd build
```

### 3 Configure with CMake
```
cmake ..
```

### 4 Build the project
```
cmake --build .
```

This produces:
- `VehicleSim` → main interactive program
- `ManualTests` → runs internal test cases

---

##  Running the Simulation

### Run main program:
**Linux/macOS:**
```
./VehicleSim
```

**Windows (PowerShell):**
```
.\VehicleSim.exe
```

### Menu Options:
```
=== Vehicle Simulation Menu ===
1. Add Vehicle
2. View Vehicles
3. Start Simulation
4. View History
5. Replay Run
0. Exit
```

Example:
```
Choice: 1
Vehicle ID: 101
Initial X: 0
Initial Y: 0
Speed (m/s): 5
Direction (degrees): 90
Length (m): 4
 Vehicle added successfully.
```

---

##  Running Manual Tests

We provide **ManualTests.exe** — a lightweight unit test runner without external dependencies.

Run it to check:
- Adding vehicles
- Position update logic
- Collision detection & no-collision cases
- History tracking
- Replay functionality

**Linux/macOS:**
```
./ManualTests
```

**Windows:**
```
.\ManualTests.exe
```

Example output:
```
[TEST] AddVehicle
ID: 1 Pos(0,0) Speed: 20 Dir: 90 Len: 5
Test AddVehicle complete.

[TEST] PositionUpdate
PASS: Position updated to x=10
Test PositionUpdate complete.

[TEST] CollisionDetection
PASS: Collision detected.
...
```

---

## ⚙ Settings
The simulation parameters are set in `Settings s{ ... }` found in `main.cpp` and `ManualTests.cpp`:

| Parameter       | Default | Description |
|-----------------|---------|-------------|
| `timeStep`      | 1.0     | Time step in seconds for each simulation iteration |
| `safetyDistance`| 5.0     | Extra safe distance to avoid collisions (meters) |
| `speedUnit`     | "m/s"   | Display unit for speed |
| `enableLogging` | true    | Store positions at each step in run history |

Modify these before creating the Simulation object if needed.

---

##  Collision Logic
Two vehicles are considered in **collision danger** if:
```
distance_between_centers <= max(vehicle1.length, vehicle2.length) + safetyDistance
```
Where `distance` is Euclidean distance between (x, y) coordinates.

---

##  Future Improvements
- Load & save vehicles/runs to file (CSV or JSON) for persistence.
- Pause & resume during simulation.
- Support for acceleration changes mid-simulation.
- More advanced collision prediction algorithms.
- Graphical 2D/3D visualization.

---

##  License
This project is released under the MIT License — free to use and modify.
```

***

###  Notes:
- I’ve written this README so someone **cloning the repo** will know exactly how to build, run, and test it.
- It documents both `VehicleSim` and `ManualTests` usage.
- It explains the **core logic**, structure, and settings.

***
