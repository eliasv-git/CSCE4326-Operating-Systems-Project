#include <iostream>
#include <string>
#include <ctime>
#include "auth.h"  // Include the header file for the authentication function
#include "Process.h"  // Include the Process class to handle processes

using namespace std;

int main() {
    // Simulate Boot-Up (Loading Screen)
    Process systemProcess(1, time(0), 1000, 1, 500, false);  // Example process
    systemProcess.simulateBootUp();  // Show the loading part with dots

    // Authenticate User
    if (authenticateUser()) {  // Call the authentication function
        systemProcess.loadOperatingSystem();  // Simulate OS loading
        systemProcess.selectApp();  // Ask the user to select an application or power off
    } else {
        cout << "Authentication failed. Exiting the system." << endl;
    }

    return 0;
}
