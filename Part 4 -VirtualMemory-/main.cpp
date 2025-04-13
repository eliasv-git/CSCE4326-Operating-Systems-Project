#include <iostream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"
#include "auth.h"
#include "VirtualMemory.h"

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

// Function to simulate virtual memory operations
void runVirtualMemorySimulation() {
    // Create virtual memory with 64KB virtual space, 32KB physical memory
    VirtualMemory vm(64 * 1024, 32 * 1024);
    
    int choice;
    int nextPid = 1;
    
    while (true) {
        cout << "\n=== Virtual Memory Simulation ===\n";
        cout << "1. Create new process\n";
        cout << "2. Read from memory\n";
        cout << "3. Write to memory\n";
        cout << "4. Display inverted page table\n";
        cout << "5. Display statistics\n";
        cout << "6. Return to main menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int memorySize;
                cout << "Enter process memory size (bytes): ";
                cin >> memorySize;
                
                vm.createProcess(nextPid, memorySize);
                cout << "Created process with ID: " << nextPid << endl;
                nextPid++;
                break;
            }
            case 2: {
                int pid, address;
                cout << "Enter process ID: ";
                cin >> pid;
                cout << "Enter virtual address to read: ";
                cin >> address;
                
                vm.translateAddress(pid, address, false);
                break;
            }
            case 3: {
                int pid, address;
                cout << "Enter process ID: ";
                cin >> pid;
                cout << "Enter virtual address to write: ";
                cin >> address;
                
                vm.translateAddress(pid, address, true);
                break;
            }
            case 4: {
                int pid;
                cout << "Enter process ID: ";
                cin >> pid;
                
                vm.displayPageTable(pid);
                break;
            }
            case 5:
                vm.displayStats();
                break;
            case 6:
                return;  // Return to main menu
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}

int main() {
    // Simulate Boot-Up
    Process::simulateBootUp();
    
    // Authenticate User
    if (!authenticateUser()) {
        cout << "Authentication failed. Exiting the system." << endl;
        return 1;
    }
    
    int choice;
    
    while (true) {
        cout << "\n=== Operating System Simulator ===\n";
        cout << "1. Process Scheduling\n";
        cout << "2. Virtual Memory\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Process Scheduling Simulation
                Scheduler scheduler;
                int schedChoice;
                
                while (true) {
                    cout << "\n=== Process Scheduling ===\n";
                    cout << "1. Input Processes\n";
                    cout << "2. Run FCFS\n";
                    cout << "3. Run SJF (Non-preemptive)\n";
                    cout << "4. Run SJF (Preemptive)\n";
                    cout << "5. Return to main menu\n";
                    cout << "Enter choice: ";
                    cin >> schedChoice;
                    
                    if (schedChoice == 5) break;
                    
                    switch (schedChoice) {
                        case 1: {
                            scheduler.clear();
                            vector<Process> processes = getProcessInput();
                            scheduler.addProcesses(processes);
                            break;
                        }
                        case 2:
                            cout << "\n=== First-Come, First-Served ===\n";
                            scheduler.runFCFS();
                            scheduler.displayResults();
                            break;
                        case 3:
                            cout << "\n=== Shortest Job First (Non-preemptive) ===\n";
                            scheduler.runSJF(false);
                            scheduler.displayResults();
                            break;
                        case 4:
                            cout << "\n=== Shortest Job First (Preemptive) ===\n";
                            scheduler.runSJF(true);
                            scheduler.displayResults();
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                }
                break;
            }
            case 2:
                runVirtualMemorySimulation();
                break;
            case 3:
                cout << "Exiting simulator..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
