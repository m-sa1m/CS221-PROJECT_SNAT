#include <iostream>
#include "structure.h"
#include "algorithm.h"
#include "input.h"
#include "fileio.h"
using namespace std;

int main() {
    cout << "========================================\n";
    cout << "  TEAM 2 - UI & I/O TESTING\n";
    cout << "========================================\n\n";
    
    // TEST 1: Input Validation
    cout << "TEST 1: Input Validation\n";
    cout << "------------------------------------\n";
    
    // Simulate valid inputs (you'll need to manually test this)
    cout << "Testing is_valid_ip():\n";
    cout << "  192.168.1.1: " << (is_valid_ip("192.168.1.1") ? "✓ VALID" : "✗ INVALID") << "\n";
    cout << "  256.1.1.1:   " << (is_valid_ip("256.1.1.1") ? "✓ VALID" : "✗ INVALID") << "\n";
    cout << "  192.168.1:   " << (is_valid_ip("192.168.1") ? "✓ VALID" : "✗ INVALID") << "\n";
    
    cout << "\nTesting is_valid_name():\n";
    cout << "  Server1:     " << (is_valid_name("Server1") ? "✓ VALID" : "✗ INVALID") << "\n";
    cout << "  Server@#:    " << (is_valid_name("Server@#") ? "✓ VALID" : "✗ INVALID") << "\n";
    cout << "  (empty):     " << (is_valid_name("") ? "✓ VALID" : "✗ INVALID") << "\n";
    
    // TEST 2: File I/O
    cout << "\n\nTEST 2: File I/O Operations\n";
    cout << "------------------------------------\n";
    
    SystemList list;
    
    // Create test systems
    System* s1 = new System();
    s1->name = "TestServer1";
    s1->ip = "10.0.0.1";
    s1->password_strength = 8;
    s1->open_ports = 2;
    s1->firewalls = true;
    s1->encryption_enabled = true;
    s1->malware_detected = false;
    s1->port_count = 0;
    s1->vuln_count = 0;
    s1->is_vulnerable = false;
    calculate_risk(s1);
    list.add_system(s1);
    
    System* s2 = new System();
    s2->name = "TestServer2";
    s2->ip = "10.0.0.2";
    s2->password_strength = 4;
    s2->open_ports = 8;
    s2->firewalls = false;
    s2->encryption_enabled = false;
    s2->malware_detected = true;
    s2->port_count = 0;
    s2->vuln_count = 0;
    s2->is_vulnerable = false;
    calculate_risk(s2);
    list.add_system(s2);
    
    cout << "Created " << list.get_count() << " test systems\n";
    
    // Test save
    cout << "\nTesting save_systems_to_file()...\n";
    if (save_systems_to_file(list, "test_data.txt")) {
        cout << "✓ Save successful!\n";
    } else {
        cout << "✗ Save failed!\n";
    }
    
    // Test load
    SystemList list2;
    cout << "\nTesting load_systems_from_file()...\n";
    if (load_systems_from_file(list2, "test_data.txt")) {
        cout << "✓ Load successful!\n";
        cout << "  Loaded " << list2.get_count() << " systems\n";
    } else {
        cout << "✗ Load failed!\n";
    }
    
    // Test report generation
    cout << "\nTesting generate_report()...\n";
    generate_report(list, "test_report.txt");
    cout << "✓ Check test_report.txt for output\n";
    
    // TEST 3: Display original data
    cout << "\n\nTEST 3: Original Systems\n";
    cout << "------------------------------------\n";
    list.display_all();
    
    // TEST 4: Display loaded data
    cout << "\n\nTEST 4: Loaded Systems\n";
    cout << "------------------------------------\n";
    list2.display_all();
    
    cout << "\n========================================\n";
    cout << "  ALL TESTS COMPLETED!\n";
    cout << "========================================\n";
    cout << "\nGenerated files:\n";
    cout << "  • test_data.txt (saved systems)\n";
    cout << "  • test_report.txt (detailed report)\n\n";
    
    return 0;
}