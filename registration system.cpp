#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

// Use the standard namespace globally
using namespace std;

const string DB_FILE = "user_database.txt";

// Helper function to convert a string to lowercase for case-insensitive checking
string to_lowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Validates that inputs are not too short and do not contain delimiter tokens
bool validate_inputs(const string& username, const string& password) {
    if (username.length() < 3) {
        cout << "❌ Error: Username must be at least 3 characters long.\n";
        return false;
    }
    if (password.length() < 6) {
        cout << "❌ Error: Password must be at least 6 characters long.\n";
        return false;
    }
    if (username.find(',') != string::npos || password.find(',') != string::npos) {
        cout << "❌ Error: Username and password cannot contain commas.\n";
        return false;
    }
    return true;
}

// Checks if the username already exists in the file database
bool is_duplicate_username(const string& username) {
    ifstream file(DB_FILE);
    if (!file.is_open()) {
        return false; // File doesn't exist yet, so no duplicates possible
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string stored_username;
        
        // Read up to the comma delimiter
        if (getline(ss, stored_username, ',')) {
            if (to_lowercase(stored_username) == to_lowercase(username)) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

// Registers a new user and appends their credentials to the text file
bool register_user(const string& username, const string& password) {
    if (!validate_inputs(username, password)) {
        return false;
    }

    if (is_duplicate_username(username)) {
        cout << "❌ Error: The username '" << username << "' is already taken.\n";
        return false;
    }

    // Open file in append mode
    ofstream file(DB_FILE, ios::app);
    if (!file.is_open()) {
        cout << "❌ Error: Could not open database file for writing.\n";
        return false;
    }

    // Write username and password separated by a comma delimiter
    file << username << "," << password << "\n";
    file.close();

    cout << "🎉 Success: User '" << username << "' registered successfully!\n";
    return true;
}

// Verifies credentials against the file data
bool login_user(const string& username, const string& password) {
    ifstream file(DB_FILE);
    if (!file.is_open()) {
        cout << "❌ Error: No registered users found. Please register first.\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string stored_username, stored_password;

        if (getline(ss, stored_username, ',') && getline(ss, stored_password)) {
            if (stored_username == username && stored_password == password) {
                cout << "🔓 Success: Welcome back, " << stored_username << "! Login successful.\n";
                file.close();
                return true;
            }
        }
    }
    file.close();
    cout << "❌ Error: Invalid username or password.\n";
    return false;
}

int main() {
    cout << "--- Testing Registration ---\n";
    register_user("Ehtisham", "SecurePass123");
    register_user("ehtisham", "DifferentPass"); // Duplicate check
    register_user("Ab", "123");                // Length check

    cout << "\n--- Testing Login ---\n";
    login_user("Ehtisham", "SecurePass123");    // Correct login
    login_user("Ehtisham", "WrongPassword");    // Wrong password
    login_user("UnknownUser", "SomePassword");  // Non-existent user

    return 0;
}
