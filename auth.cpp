#include <iostream>
#include <string>
#include "auth.h"  // Include the header file to match the declaration

using namespace std;

// Define the authenticateUser function
bool authenticateUser() {
    string username, password;

    // Hardcoded credentials for authentication
    const string correctUsername = "admin";
    const string correctPassword = "password123";

    cout << "\nWelcome to the system!" << endl;
    cout << "Please Sign In to continue." << endl;

    // Prompt user for input
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Check if the input matches the hardcoded credentials
    if (username == correctUsername && password == correctPassword) {
        cout << "Authentication successful!" << endl;
        return true;  // Authentication success
    } else {
        cout << "Invalid username or password!" << endl;
        return false; // Authentication failure
    }
}
