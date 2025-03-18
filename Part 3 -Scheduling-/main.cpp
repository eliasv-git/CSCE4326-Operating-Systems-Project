#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"
#include "auth.h"

using namespace std;

// Function to get process input from user
vector<Process> getProcessInput() {
    vector<Process> processes;
    int n;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int arrivalTime, burstTime;
        
        cout << "Process " << i+1 << endl;
        cout << "Enter arrival time: ";
        cin >> arrivalTime;
        cout << "Enter burst time: ";
        cin >> burstTime;
        
        processes.push_back(Process(i+1, arrivalTime, burstTime));
    }
    
    return processes;
}

int main() {
    // Simulate Boot-Up
    Process::simulateBootUp();
    
    // Authenticate User
    if (!authenticateUser()) {
        cout << "Authentication failed. Exiting the system." << endl;
        return 1;
    }
    
    // Process Scheduling Simulation
    Scheduler scheduler;
    int choice;
    
    while (true) {
        cout << "\n=== Process Scheduling Simulator ===\n";
        cout << "1. Input Processes\n";
        cout << "2. Run FCFS Scheduling\n";
        cout << "3. Run SJF Non-preemptive Scheduling\n";
        cout << "4. Run SJF Preemptive Scheduling\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                scheduler.clear();
                vector<Process> processes = getProcessInput();
                scheduler.addProcesses(processes);
                break;
            }
            case 2: {
                cout << "\n=== First-Come, First-Served (FCFS) Scheduling ===\n";
                scheduler.runFCFS();
                scheduler.displayResults();
                break;
            }
            case 3: {
                cout << "\n=== Shortest Job First (SJF) Non-preemptive Scheduling ===\n";
                scheduler.runSJF(false);
                scheduler.displayResults();
                break;
            }
            case 4: {
                cout << "\n=== Shortest Job First (SJF) Preemptive Scheduling ===\n";
                scheduler.runSJF(true);
                scheduler.displayResults();
                break;
            }
            case 5:
                cout << "Exiting the simulator..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}