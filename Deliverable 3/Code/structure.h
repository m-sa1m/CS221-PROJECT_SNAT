#ifndef STRUCTURE_H
#define STRUCTURE_H
#pragma once

#include <string>
using namespace std;

// System structure
struct System {
    // Basic info
    string name;
    string ip;
    
    // Security parameters
    int password_strength;      // 1-10 scale
    int open_ports;
    bool firewalls;
    bool encryption_enabled;
    bool malware_detected;
    int risk_score;
    
    // Detailed arrays
    int port_list[10];
    string services[10];
    string vulnerabilities[5];
    int port_count;
    int vuln_count;
    bool is_vulnerable;
};
