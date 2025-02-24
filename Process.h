#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Enum for process states
enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class Process {
private:
    int pid;                    // Process ID
    time_t arrival_time;        // Arrival time
    int burst_time;             // CPU execution time required
    int priority;               // Priority level
    ProcessState state;         // Current state of the process
    int remaining_time;         // Time left to complete execution
    int waiting_time;           // Time spent waiting in the ready queue
    int turnaround_time;        // Time from arrival to completion
    int memory_required;        // Memory required for the process
    bool io_operations;         // Flag for I/O operations (optional)

public:
    // Constructor to initialize process attributes
    Process(int id, time_t arrival, int burst, int priorityLevel, int memory, bool ioOps);

    // New method to display the OS loading process and app selection
    void loadOperatingSystem();
    void selectApp();
    void simulateBootUp();  // Simulate the boot-up process
};

#endif // PROCESS_H
