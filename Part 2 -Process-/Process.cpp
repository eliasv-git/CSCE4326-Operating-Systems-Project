#include "Process.h"
#include <iostream>
#include <ctime>
#include <thread>  // Include for sleep functionality
#include <chrono>  // Include for chrono functionality

using namespace std;

// Constructor to initialize process attributes
Process::Process(int id, time_t arrival, int burst, int priorityLevel, int memory, bool ioOps)
    : pid(id), arrival_time(arrival), burst_time(burst), priority(priorityLevel),
      state(ProcessState::NEW), remaining_time(burst), waiting_time(0), turnaround_time(0),
      memory_required(memory), io_operations(ioOps) {}

// Method to simulate boot-up process (Loading with dots)
void Process::simulateBootUp() {
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "\rLoading";
            for (int k = 0; k < j; k++) {
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500)); // 500ms delay
            }
            cout.flush(); // Resets the dots
        }
        cout << "\rLoading   ";
        this_thread::sleep_for(chrono::milliseconds(500));  // 500ms delay
    }
    cout << endl;
}

// Method to simulate the loading of the operating system
void Process::loadOperatingSystem() {
    cout << "\nLoading Operating System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));  // 500ms delay
    }
    cout << endl;
}

// Method to allow the user to select an application
void Process::selectApp() {
    int choice;
    while (true){
    cout << "\nSelect an application to use:" << endl;
    cout << "1. Notepad" << endl;
    cout << "2. VSCode" << endl;
    cout << "3. Word" << endl;
    cout << "4. PowerPoint" << endl;
    cout << "5. Power Off the OS" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "You selected Notepad!" << endl;
            break;
        case 2:
            cout << "You selected VSCode!" << endl;
            break;
        case 3:
            cout << "You selected Word!" << endl;
            break;
        case 4:
            cout << "You selected PowerPoint!" << endl;
            break;
        case 5:
            cout << "Shutting down the OS..." << endl;
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
    };
}
