#include <iostream>
#include <string>
#include <ctime>
#include "auth.h"  // Include the header file for the authentication function

using namespace std;

void simpleDelay(int milliseconds) { // Function that creates a delay
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000)) {
    }
}

void simulateBootUp() { // Function to create the loading part
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "\rLoading";
            for (int k = 0; k < j; k++) {
                cout << ".";
                simpleDelay(500);
            }
            cout.flush(); // Resets the dots
        }
        cout << "\rLoading   ";
        simpleDelay(500);
    }
    cout << endl;
}

void loadOperatingSystem() { // Function that simulates after signing in to load the OS
    cout << "\nLoading Operating System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        simpleDelay(500);
    }
    cout << endl;
}

int main() {
    simulateBootUp(); // Function call for the Loading part

    if (authenticateUser()) { // Call the authentication function
        loadOperatingSystem(); // Function call to load the OS
        cout << "\nWelcome to your system!" << endl;
        cout << "The operating system is now ready for use." << endl;
    } else {
        cout << "Authentication failed. Exiting the system." << endl;
    }

    return 0;
}
