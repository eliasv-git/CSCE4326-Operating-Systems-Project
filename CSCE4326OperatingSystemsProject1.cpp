#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void simpleDelay(int milliseconds) { //Function that creates a Delay
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000)) {
    }
}

void simulateBootUp() { //Function to create the loading part
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "\rLoading";
            for (int k = 0; k < j; k++) {
                cout << ".";
                simpleDelay(500);
            }
            cout.flush();//Resets the dots
        }
        cout << "\rLoading   ";
        simpleDelay(500);
    }
    cout << endl;
}

void userAuthentication() { //Function that asks for the user sign in or sign up
    string username, password, action;

    cout << "\nWelcome to the system!" << endl;
    cout << "Do you want to Sign Up or Sign In? (Type 'signup' or 'signin'): ";
    cin >> action;

    while (action != "signup" && action != "signin") {
        cout << "Invalid input. Please type 'signup' or 'signin': ";
        cin >> action;
    }

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    cout << "\n" << (action == "signup" ? "Sign Up" : "Sign In") << " successful!" << endl;
}

void loadOperatingSystem() { //Function that simulates after signing in to load the OS
    cout << "\nLoading Operating System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        simpleDelay(500);
    }
    cout << endl;
}

int main() {
    simulateBootUp(); //Function call for the Loading part 
    userAuthentication(); //Function call that asks the user to sign in/up
    loadOperatingSystem(); // Function call to load the OS
    cout << "\nWelcome to your system!" << endl;
    cout << "The operating system is now ready for use." << endl;

    return 0;
}
