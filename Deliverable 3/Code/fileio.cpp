#include <iostream>
#include <fstream>
#include <sstream>
#include "fileio.h"
#include "algorithm.h"
using namespace std;

// Save Systems to File

bool save_systems_to_file(SystemList& list, string filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "[ERROR] Cannot create file: " << filename << "\n";
        return false;
    }
    
    Node* head = list.get_head();
    
    // Empty list
    if (!head) {
        file.close();
        return true;
    }
    
    // Write header
    file << "# SNAT Data File\n";
    file << "# Format: name|ip|pwd_strength|ports|firewall|encryption|malware|risk\n";
    
    // Write each system
    Node* temp = head;
    do {
        System* s = temp->data;
        file << s->name << "|"
             << s->ip << "|"
             << s->password_strength << "|"
             << s->open_ports << "|"
             << (s->firewalls ? "1" : "0") << "|"
             << (s->encryption_enabled ? "1" : "0") << "|"
             << (s->malware_detected ? "1" : "0") << "|"
             << s->risk_score << "\n";
        
        temp = temp->next;
    } while (temp != head);
    
    file.close();
    return true;
}

// Load Systems from File


bool load_systems_from_file(SystemList& list, string filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "[ERROR] Cannot open file: " << filename << "\n";
        return false;
    }
    
    string line;
    int loaded = 0;
    
    while (getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        stringstream ss(line);
        string token;
        System* sys = new System();
        
        try {
            // Parse data
            getline(ss, sys->name, '|');
            getline(ss, sys->ip, '|');
            
            getline(ss, token, '|');
            sys->password_strength = stoi(token);
            
            getline(ss, token, '|');
            sys->open_ports = stoi(token);
            
            getline(ss, token, '|');
            sys->firewalls = (token == "1");
            
            getline(ss, token, '|');
            sys->encryption_enabled = (token == "1");
            
            getline(ss, token, '|');
            sys->malware_detected = (token == "1");
            
            getline(ss, token, '|');
            sys->risk_score = stoi(token);
            
            // Initialize arrays
            sys->port_count = 0;
            sys->vuln_count = 0;
            sys->is_vulnerable = false;
            
            // Add to list
            list.add_system(sys);
            loaded++;
            
        } catch (...) {
            cout << "[WARNING] Skipped invalid line: " << line << "\n";
            delete sys;
        }
    }
    
    file.close();
    cout << "[SUCCESS] Loaded " << loaded << " systems from file.\n";
    return true;
}

// Generate Detailed Report

void generate_report(SystemList& list, string filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "[ERROR] Cannot create report file.\n";
        return;
    }
    
    // Header
    file << "========================================\n";
    file << "  NETWORK SECURITY ASSESSMENT REPORT\n";
    file << "  Secure Network Assessment Tool (SNAT)\n";
    file << "========================================\n\n";
    
    // Summary statistics
    file << "EXECUTIVE SUMMARY\n";
    file << "----------------------------------------\n";
    file << "Total Systems Assessed: " << list.get_count() << "\n\n";
    
    Node* head = list.get_head();
    
    if (!head) {
        file << "No systems assessed.\n";
        file.close();
        cout << "[INFO] Report generated (empty network).\n";
        return;
    }
    
    // Count risk levels
    int high_risk = 0, medium_risk = 0, low_risk = 0;
    int total_vulnerabilities = 0;
    
    Node* temp = head;
    do {
        if (temp->data->risk_score >= 80) high_risk++;
        else if (temp->data->risk_score >= 50) medium_risk++;
        else low_risk++;
        
        total_vulnerabilities += temp->data->vuln_count;
        
        temp = temp->next;
    } while (temp != head);
    
    // Risk distribution
    file << "Risk Distribution:\n";
    file << "  • High Risk (≥80):     " << high_risk << " systems\n";
    file << "  • Medium Risk (50-79): " << medium_risk << " systems\n";
    file << "  • Low Risk (<50):      " << low_risk << " systems\n\n";
    
    file << "Total Vulnerabilities Found: " << total_vulnerabilities << "\n\n";
    
    // Critical findings
    if (high_risk > 0) {
        file << "⚠️  CRITICAL FINDINGS\n";
        file << "----------------------------------------\n";
        file << high_risk << " system(s) require immediate attention!\n\n";
    }
    
    // Detailed system information
    file << "DETAILED SYSTEM ANALYSIS\n";
    file << "========================================\n\n";
    
    temp = head;
    int index = 1;
    
    do {
        System* s = temp->data;
        string level = (s->risk_score < 50) ? "LOW" : 
                      (s->risk_score < 80) ? "MEDIUM" : "HIGH";
        
        file << "System #" << index++ << ": " << s->name << "\n";
        file << "----------------------------------------\n";
        file << "IP Address:         " << s->ip << "\n";
        file << "Risk Score:         " << s->risk_score << "/100 [" << level << "]\n";
        file << "Password Strength:  " << s->password_strength << "/10\n";
        file << "Open Ports:         " << s->open_ports << "\n";
        file << "Firewall:           " << (s->firewalls ? "ENABLED" : "DISABLED") << "\n";
        file << "Encryption:         " << (s->encryption_enabled ? "ENABLED" : "DISABLED") << "\n";
        file << "Malware Detected:   " << (s->malware_detected ? "YES" : "NO") << "\n";
        
        if (s->vuln_count > 0) {
            file << "\nVulnerabilities (" << s->vuln_count << "):\n";
            for (int i = 0; i < s->vuln_count; i++) {
                file << "  • " << s->vulnerabilities[i] << "\n";
            }
        } else {
            file << "\nVulnerabilities: None detected\n";
        }
        
        file << "\n";
        temp = temp->next;
    } while (temp != head);
    
    // Recommendations
    file << "========================================\n";
    file << "RECOMMENDATIONS\n";
    file << "========================================\n\n";
    
    if (high_risk > 0) {
        file << "1. IMMEDIATE ACTION REQUIRED:\n";
        file << "   • Address all HIGH RISK systems within 24 hours\n";
        file << "   • Enable firewalls on all vulnerable systems\n";
        file << "   • Update weak passwords immediately\n\n";
    }
    
    if (medium_risk > 0) {
        file << "2. MEDIUM PRIORITY:\n";
        file << "   • Review and strengthen security for MEDIUM RISK systems\n";
        file << "   • Enable encryption where disabled\n";
        file << "   • Close unnecessary open ports\n\n";
    }
    
    file << "3. GENERAL RECOMMENDATIONS:\n";
    file << "   • Conduct regular security assessments\n";
    file << "   • Implement multi-factor authentication\n";
    file << "   • Keep all systems updated with latest patches\n";
    file << "   • Conduct employee security awareness training\n\n";
    
    file << "========================================\n";
    file << "END OF REPORT\n";
    file << "========================================\n";
    
    file.close();
    cout << "[SUCCESS] Report generated: " << filename << "\n";
}
