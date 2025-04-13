#include <iostream>
#include <string>
#include "auth.h"

// Define the authenticateUser function
bool authenticateUser() {
    std::string username, password;

    // Hardcoded credentials for authentication
    const std::string correctUsername = "admin";
    const std::string correctPassword = "password123";

    std::cout << "\nWelcome to the system!" << std::endl;
    std::cout << "Please Sign In to continue." << std::endl;

    while(true) {
        // Prompt user for input
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        // Check if the input matches the hardcoded credentials
        if (username == correctUsername && password == correctPassword) {
            std::cout << "Authentication successful!" << std::endl;
            return true;  // Authentication success
        }
        
        std::cout << "Invalid username or password! Try again or press Ctrl+C to exit." << std::endl;
    }
}