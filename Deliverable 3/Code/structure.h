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

// STEP 2: Node for Circular Doubly Linked List
struct Node {
    System* data;
    Node* next;
    Node* prev;
};

// STEP 3: SystemList class (Circular Doubly Linked List)
class SystemList {
private:
    Node* head;
    int count;
    
public:
    SystemList();
    ~SystemList();
    
    // Core operations
    void add_system(System* sys);
    bool delete_system(string name);
    System* search_system(string name);
    int get_count();
    
    // Display operations
    void display_all();
    void display_high_risk();
    void display_by_ip(string ip);
    
    // Traversal
    Node* get_head();
    void traverse_forward();
    void traverse_backward();
};
