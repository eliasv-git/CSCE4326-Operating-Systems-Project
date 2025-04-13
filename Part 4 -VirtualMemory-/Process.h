#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <thread>
#include <chrono>

class Process {
public:
    int pid;             // Process ID
    int arrivalTime;     // Arrival Time
    int burstTime;       // Burst Time (CPU time)
    int waitingTime;     // Waiting Time
    int turnaroundTime;  // Turnaround Time
    int completionTime;  // Completion Time
    int remainingTime;   // Remaining Burst Time (for preemptive SJF)
    
    // Constructor
    Process(int id, int arrival, int burst) 
        : pid(id), arrivalTime(arrival), burstTime(burst), 
          waitingTime(0), turnaroundTime(0), completionTime(0), 
          remainingTime(burst) {}
    
    // Static method to simulate boot-up
    static void simulateBootUp() {
        for (int i = 0; i < 2; i++) {
            for (int j = 1; j <= 3; j++) {
                std::cout << "\rLoading";
                for (int k = 0; k < j; k++) {
                    std::cout << ".";
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
                std::cout.flush();
            }
            std::cout << "\rLoading   ";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        std::cout << std::endl;
    }
};

#endif // PROCESS_H