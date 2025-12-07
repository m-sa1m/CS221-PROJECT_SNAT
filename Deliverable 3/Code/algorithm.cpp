#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "algorithm.h"
#include "structure.h"
using namespace std;

// Risk weights array
int risk_weights[5] = {25, 30, 15, 20, 10}; // Password, Ports, Encryption, Malware, Firewall

// ============================================
// SECTION 1: Risk Calculation
// ============================================

int calculate_risk(System* sys) {
    int score = 0;
    
    // Password risk (weaker password = higher risk)
    score += (10 - sys->password_strength) * risk_weights[0] / 10;
    
    // Open ports risk
    score += sys->open_ports * risk_weights[1] / 2;
    
    // Encryption risk
    if (!sys->encryption_enabled) score += risk_weights[2];
    
    // Malware risk
    if (sys->malware_detected) score += risk_weights[3];
    
    // Firewall risk
    if (!sys->firewalls) score += risk_weights[4];
    
    // Cap at 100
    sys->risk_score = (score > 100) ? 100 : score;
    return sys->risk_score;
}

void calculate_all_risks(SystemList& list) {
    Node* head = list.get_head();
    if (!head) return;
    
    Node* temp = head;
    do {
        calculate_risk(temp->data);
        temp = temp->next;
    } while (temp != head);
}


