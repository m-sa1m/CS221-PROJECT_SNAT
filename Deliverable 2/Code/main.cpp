#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structure.h"
#include "algorithm.h"
#include "menu.h"
#include "input.h"
#include "fileio.h"
using namespace std;


void initialize_sample_data(SystemList& list) {
    cout << "\n⏳ Loading sample data...\n";
    
    // System 1: Low Risk
    System* sys1 = new System();
    sys1->name = "WebServer";
    sys1->ip = "192.168.1.10";
    sys1->password_strength = 9;
    sys1->open_ports = 2;
    sys1->firewalls = true;
    sys1->encryption_enabled = true;
    sys1->malware_detected = false;
    sys1->port_count = 0;
    sys1->vuln_count = 0;
    sys1->is_vulnerable = false;
    calculate_risk(sys1);
    list.add_system(sys1);
    
    // System 2: High Risk
    System* sys2 = new System();
    sys2->name = "Database";
    sys2->ip = "192.168.1.20";
    sys2->password_strength = 3;
    sys2->open_ports = 8;
    sys2->firewalls = false;
    sys2->encryption_enabled = false;
    sys2->malware_detected = true;
    sys2->port_count = 0;
    sys2->vuln_count = 0;
    sys2->is_vulnerable = false;
    calculate_risk(sys2);
    list.add_system(sys2);
    
    // System 3: Low Risk
    System* sys3 = new System();
    sys3->name = "Workstation";
    sys3->ip = "192.168.1.30";
    sys3->password_strength = 8;
    sys3->open_ports = 1;
    sys3->firewalls = true;
    sys3->encryption_enabled = true;
    sys3->malware_detected = false;
    sys3->port_count = 0;
    sys3->vuln_count = 0;
    sys3->is_vulnerable = false;
    calculate_risk(sys3);
    list.add_system(sys3);
    
    // System 4: Medium Risk
    System* sys4 = new System();
    sys4->name = "FileServer";
    sys4->ip = "192.168.1.40";
    sys4->password_strength = 6;
    sys4->open_ports = 4;
    sys4->firewalls = true;
    sys4->encryption_enabled = false;
    sys4->malware_detected = false;
    sys4->port_count = 0;
    sys4->vuln_count = 0;
    sys4->is_vulnerable = false;
    calculate_risk(sys4);
    list.add_system(sys4);
    
    // System 5: Medium Risk
    System* sys5 = new System();
    sys5->name = "MailServer";
    sys5->ip = "192.168.1.50";
    sys5->password_strength = 5;
    sys5->open_ports = 5;
    sys5->firewalls = false;
    sys5->encryption_enabled = true;
    sys5->malware_detected = false;
    sys5->port_count = 0;
    sys5->vuln_count = 0;
    sys5->is_vulnerable = false;
    calculate_risk(sys5);
    list.add_system(sys5);
    
    cout << "✅ Loaded " << list.get_count() << " sample systems.\n";
}

int main() {
    
    srand(time(0));
    
    
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║                                            ║\n";
    cout << "║  SECURE NETWORK ASSESSMENT TOOL (SNAT)    ║\n";
    cout << "║  Version 3.0 - Deliverable 3              ║\n";
    cout << "║                                            ║\n";
    cout << "║  Data Structures & Algorithms Project     ║\n";
    cout << "║  CS221 - Fall 2024                        ║\n";
    cout << "║                                            ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    
    SystemList network;
    
    
    cout << "\n📋 Would you like to load sample data? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        initialize_sample_data(network);
        pause_screen();
    } else {
        cout << "\n✓ Starting with empty network.\n";
        pause_screen();
    }
    
   
    int option;
    bool running = true;
    
                
                if (network.get_count() > 0) {
                    cout << "📊 Generate final assessment report? (y/n): ";
                    char gen;
                    cin >> gen;
                    
                    if (gen == 'y' || gen == 'Y') {
                        generate_report(network, "final_assessment_report.txt");
                        cout << "\n✅ Report saved as: final_assessment_report.txt\n";
                    }
                    
                    cout << "\n💾 Save current network state? (y/n): ";
                    cin >> gen;
                    
                    if (gen == 'y' || gen == 'Y') {
                        save_systems_to_file(network, "network_backup.txt");
                        cout << "\n✅ Network saved as: network_backup.txt\n";
                    }
                }
                
                cout << "\nGoodbye!\n\n";
                running = false;
                break;
                
            default:
                cout << "\n❌ Invalid option! Please enter a number between 1-9.\n";
                pause_screen();
        }
    }
    
    return 0;
}