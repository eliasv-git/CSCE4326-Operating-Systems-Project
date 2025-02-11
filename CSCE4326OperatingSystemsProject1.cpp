#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void simpleDelay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000)) {
    }
}

void simulateBootUp() {
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "\rLoading";
            for (int k = 0; k < j; k++) {
                cout << ".";
                simpleDelay(500);
            }
            cout.flush();
        }
        cout << "\rLoading   ";
        simpleDelay(500);
    }
    cout << endl;
}

void userAuthentication() {
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

void loadOperatingSystem() {
    cout << "\nLoading Operating System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        simpleDelay(500);
    }
    cout << endl;
}

int main() {
    simulateBootUp();
    userAuthentication();
    loadOperatingSystem();
    cout << "\nWelcome to your system!" << endl;
    cout << "The operating system is now ready for use." << endl;

    return 0;
}
