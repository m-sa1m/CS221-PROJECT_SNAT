#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "input.h"
using namespace std;

// ============================================
// String Input with Validation
// ============================================

string get_string_input(string prompt) {
    string input;
    
    while (true) {
        cout << prompt << ": ";
        getline(cin, input);
        
        // Check if empty
        if (input.empty()) {
            cout << "[ERROR] Input cannot be empty. Try again.\n";
            continue;
        }
        
        // Check if valid name
        if (!is_valid_name(input)) {
            cout << "[ERROR] Invalid characters. Use letters, numbers, spaces, hyphens, underscores only.\n";
            continue;
        }
        
        return input;
    }
}

// ============================================
// Integer Input with Range Validation
// ============================================

int get_int_input(string prompt, int min, int max) {
    int value;
    string input;
    
    while (true) {
        cout << prompt << " (" << min << "-" << max << "): ";
        getline(cin, input);
        
        // Try to convert to integer
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            // Check range
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << "[ERROR] Value must be between " << min << " and " << max << ".\n";
            }
        } else {
            cout << "[ERROR] Please enter a valid number.\n";
        }
    }
}

// ============================================
// Boolean Input (Yes/No)
// ============================================

bool get_bool_input(string prompt) {
    string input;
    
    while (true) {
        cout << prompt << " (y/n): ";
        getline(cin, input);
        
        // Convert to lowercase for comparison
        for (char& c : input) {
            c = tolower(c);
        }
        
        if (input == "y" || input == "yes") {
            return true;
        } else if (input == "n" || input == "no") {
            return false;
        } else {
            cout << "[ERROR] Please enter 'y' or 'n'.\n";
        }
    }
}

// ============================================
// IP Address Input with Validation
// ============================================

string get_ip_input(string prompt) {
    string ip;
    
    while (true) {
        cout << prompt << " (e.g., 192.168.1.1): ";
        getline(cin, ip);
        
        if (is_valid_ip(ip)) {
            return ip;
        } else {
            cout << "[ERROR] Invalid IP format. Must be xxx.xxx.xxx.xxx (0-255 each).\n";
        }
    }
}

// ============================================
// IP Validation Helper
// ============================================

bool is_valid_ip(string ip) {
    stringstream ss(ip);
    string segment;
    int count = 0;
    
    while (getline(ss, segment, '.')) {
        count++;
        
        // Check if too many segments
        if (count > 4) return false;
        
        // Check if segment is empty
        if (segment.empty()) return false;
        
        // Check if all digits
        for (char c : segment) {
            if (!isdigit(c)) return false;
        }
        
        // Convert to integer and check range
        try {
            int num = stoi(segment);
            if (num < 0 || num > 255) return false;
        } catch (...) {
            return false;
        }
    }
    
    // Must have exactly 4 segments
    return count == 4;
}

// ============================================
// Name Validation Helper
// ============================================

bool is_valid_name(string name) {
    // Check length
    if (name.empty() || name.length() > 50) {
        return false;
    }
    
    // Check characters (allow letters, numbers, spaces, hyphens, underscores)
    for (char c : name) {
        if (!isalnum(c) && c != ' ' && c != '-' && c != '_') {
            return false;
        }
    }
    
    return true;
}