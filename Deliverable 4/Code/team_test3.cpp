#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structure.h"
#include "algorithm.h"
#include "input.h"
#include "fileio.h"
using namespace std;

// Test counter
int tests_passed = 0;
int tests_failed = 0;

void test_result(string test_name, bool passed) {
    if (passed) {
        cout << "   ✅ " << test_name << "\n";
        tests_passed++;
    } else {
        cout << "   ❌ " << test_name << " FAILED!\n";
        tests_failed++;
    }
}

int main() {
    srand(time(0));
    
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║   SNAT INTEGRATION TEST SUITE            ║\n";
    cout << "║   Deliverable 3 - Complete Testing       ║\n";
    cout << "╚════════════════════════════════════════════╝\n\n";
    
    // ========================================
    // TEST SUITE 1: Data Structures
    // ========================================
    
    cout << "TEST SUITE 1: Data Structures\n";
    cout << "========================================\n";
    
    SystemList list;
    
    // Test 1.1: Add systems
    System* s1 = new System();
    s1->name = "TestSys1";
    s1->ip = "10.0.0.1";
    s1->password_strength = 7;
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
    s2->name = "TestSys2";
    s2->ip = "10.0.0.2";
    s2->password_strength = 3;
    s2->open_ports = 8;
    s2->firewalls = false;
    s2->encryption_enabled = false;
    s2->malware_detected = true;
    s2->port_count = 0;
    s2->vuln_count = 0;
    s2->is_vulnerable = false;
    calculate_risk(s2);
    list.add_system(s2);
    
    System* s3 = new System();
    s3->name = "TestSys3";
    s3->ip = "10.0.0.3";
    s3->password_strength = 9;
    s3->open_ports = 1;
    s3->firewalls = true;
    s3->encryption_enabled = true;
    s3->malware_detected = false;
    s3->port_count = 0;
    s3->vuln_count = 0;
    s3->is_vulnerable = false;
    calculate_risk(s3);
    list.add_system(s3);
    
    test_result("Add 3 systems", list.get_count() == 3);
    
    // Test 1.2: Search system
    System* found = list.search_system("TestSys2");
    test_result("Search existing system", found != NULL && found->name == "TestSys2");
    
    // Test 1.3: Search non-existent
    System* not_found = list.search_system("NonExistent");
    test_result("Search non-existent system", not_found == NULL);
    
    // Test 1.4: Delete system
    bool deleted = list.delete_system("TestSys2");
    test_result("Delete system", deleted && list.get_count() == 2);
    
    // Test 1.5: Delete non-existent
    bool not_deleted = list.delete_system("NonExistent");
    test_result("Delete non-existent system", !not_deleted);
    
    // ========================================
    // TEST SUITE 2: Stack and Queue
    // ========================================
    
    cout << "\nTEST SUITE 2: Stack and Queue\n";
    cout << "========================================\n";
    
    // Test 2.1: Stack LIFO
    TaskStack stack;
    stack.push("A");
    stack.push("B");
    stack.push("C");
    string popped = stack.pop();
    test_result("Stack LIFO order", popped == "C");
    
    // Test 2.2: Stack empty
    stack.pop();
    stack.pop();
    test_result("Stack empty check", stack.is_empty());
    
    // Test 2.3: Queue FIFO
    ScanQueue queue;
    queue.enqueue("X");
    queue.enqueue("Y");
    queue.enqueue("Z");
    string dequeued = queue.dequeue();
    test_result("Queue FIFO order", dequeued == "X");
    
    // Test 2.4: Queue size
    test_result("Queue size", queue.size() == 2);
    
    // ========================================
    // TEST SUITE 3: Binary Search Tree
    // ========================================
    
    cout << "\nTEST SUITE 3: Binary Search Tree\n";
    cout << "========================================\n";
    
    RiskBST bst;
    bst.insert(s1);
    bst.insert(s3);
    
    test_result("BST insertion", true); // If no crash, passed
    
    System* bst_found = bst.search_by_risk(s1->risk_score);
    test_result("BST search", bst_found != NULL);
    
    // ========================================
    // TEST SUITE 4: Sorting Algorithms
    // ========================================
    
    cout << "\nTEST SUITE 4: Sorting Algorithms\n";
    cout << "========================================\n";
    
    // Create array for testing
    System* sys_array[2] = {s1, s3};
    
    // Test 4.1: Selection Sort
    selection_sort(sys_array, 2);
    test_result("Selection Sort", sys_array[0]->risk_score >= sys_array[1]->risk_score);
    
    // Reset array
    sys_array[0] = s3;
    sys_array[1] = s1;
    
    // Test 4.2: Bubble Sort
    bubble_sort(sys_array, 2);
    test_result("Bubble Sort", sys_array[0]->risk_score >= sys_array[1]->risk_score);
    
    // Reset array
    sys_array[0] = s3;
    sys_array[1] = s1;
    
    // Test 4.3: Insertion Sort
    insertion_sort(sys_array, 2);
    test_result("Insertion Sort", sys_array[0]->risk_score >= sys_array[1]->risk_score);
    
    // Reset array
    sys_array[0] = s3;
    sys_array[1] = s1;
    
    // Test 4.4: Quick Sort
    quick_sort(sys_array, 0, 1);
    test_result("Quick Sort", sys_array[0]->risk_score >= sys_array[1]->risk_score);
    
    // Reset array
    sys_array[0] = s3;
    sys_array[1] = s1;
    
    // Test 4.5: Merge Sort
    merge_sort(sys_array, 0, 1);
    test_result("Merge Sort", sys_array[0]->risk_score >= sys_array[1]->risk_score);
    
    // ========================================
    // TEST SUITE 5: Searching Algorithms
    // ========================================
    
    cout << "\nTEST SUITE 5: Searching Algorithms\n";
    cout << "========================================\n";
    
    // Test 5.1: Linear Search
    System* linear_found = linear_search(sys_array, 2, s1->name);
    test_result("Linear Search - found", linear_found != NULL);
    
    System* linear_not_found = linear_search(sys_array, 2, "NonExistent");
    test_result("Linear Search - not found", linear_not_found == NULL);
    
    // Test 5.2: Binary Search (on sorted array)
    System* binary_found = binary_search_by_risk(sys_array, 2, s1->risk_score);
    test_result("Binary Search", binary_found != NULL);
    
    // ========================================
    // TEST SUITE 6: Risk Calculation
    // ========================================
    
    cout << "\nTEST SUITE 6: Risk Calculation\n";
    cout << "========================================\n";
    
    // Test 6.1: High risk system
    System* high_risk = new System();
    high_risk->name = "HighRisk";
    high_risk->ip = "10.0.0.99";
    high_risk->password_strength = 1;
    high_risk->open_ports = 10;
    high_risk->firewalls = false;
    high_risk->encryption_enabled = false;
    high_risk->malware_detected = true;
    high_risk->port_count = 0;
    high_risk->vuln_count = 0;
    high_risk->is_vulnerable = false;
    calculate_risk(high_risk);
    
    test_result("High risk calculation", high_risk->risk_score >= 80);
    
    // Test 6.2: Low risk system
    System* low_risk = new System();
    low_risk->name = "LowRisk";
    low_risk->ip = "10.0.0.100";
    low_risk->password_strength = 10;
    low_risk->open_ports = 0;
    low_risk->firewalls = true;
    low_risk->encryption_enabled = true;
    low_risk->malware_detected = false;
    low_risk->port_count = 0;
    low_risk->vuln_count = 0;
    low_risk->is_vulnerable = false;
    calculate_risk(low_risk);
    
    test_result("Low risk calculation", low_risk->risk_score < 50);
    
    delete high_risk;
    delete low_risk;
    
    // ========================================
    // TEST SUITE 7: Input Validation
    // ========================================
    
    cout << "\nTEST SUITE 7: Input Validation\n";
    cout << "========================================\n";
    
    // Test 7.1: Valid IP
    test_result("Valid IP: 192.168.1.1", is_valid_ip("192.168.1.1"));
    
    // Test 7.2: Invalid IP - out of range
    test_result("Invalid IP: 256.1.1.1", !is_valid_ip("256.1.1.1"));
    
    // Test 7.3: Invalid IP - wrong format
    test_result("Invalid IP: 192.168.1", !is_valid_ip("192.168.1"));
    
    // Test 7.4: Valid name
    test_result("Valid name: Server1", is_valid_name("Server1"));
    
    // Test 7.5: Invalid name - special chars
    test_result("Invalid name: Server@#", !is_valid_name("Server@#"));
    
    // Test 7.6: Invalid name - empty
    test_result("Invalid name: empty", !is_valid_name(""));
    
    // ========================================
    // TEST SUITE 8: File I/O
    // ========================================
    
    cout << "\nTEST SUITE 8: File I/O\n";
    cout << "========================================\n";
    
    // Test 8.1: Save to file
    bool saved = save_systems_to_file(list, "test_integration.txt");
    test_result("Save to file", saved);
    
    // Test 8.2: Load from file
    SystemList list2;
    bool loaded = load_systems_from_file(list2, "test_integration.txt");
    test_result("Load from file", loaded);
    
    // Test 8.3: Verify loaded data
    test_result("Loaded correct count", list2.get_count() == list.get_count());
    
    // Test 8.4: Generate report
    generate_report(list, "test_integration_report.txt");
    test_result("Generate report", true);  // If no crash, passed
    
    // ========================================
    // TEST SUITE 9: Port Scanning
    // ========================================
    
    cout << "\nTEST SUITE 9: Port Scanning\n";
    cout << "========================================\n";
    
    // Test 9.1: Port scan
    scan_ports(s1);
    test_result("Port scan executed", s1->port_count >= 0);
    
    // Test 9.2: Vulnerability check
    check_vulnerabilities(s1);
    test_result("Vulnerability check executed", true);
    
    // ========================================
    // FINAL RESULTS
    // ========================================
    
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║          TEST RESULTS SUMMARY             ║\n";
    cout << "╚════════════════════════════════════════════╝\n\n";
    
    int total_tests = tests_passed + tests_failed;
    double pass_rate = (double)tests_passed / total_tests * 100;
    
    cout << "Total Tests:   " << total_tests << "\n";
    cout << "✅ Passed:     " << tests_passed << "\n";
    cout << "❌ Failed:     " << tests_failed << "\n";
    cout << "Pass Rate:     " << pass_rate << "%\n\n";
    
    if (tests_failed == 0) {
        cout << "╔════════════════════════════════════════════╗\n";
        cout << "║   🎉 ALL TESTS PASSED! 🎉                ║\n";
        cout << "║   Project is ready for submission!       ║\n";
        cout << "╚════════════════════════════════════════════╝\n\n";
    } else {
        cout << "⚠️  Some tests failed. Please review and fix.\n\n";
    }
    
    cout << "Generated files:\n";
    cout << "  • test_integration.txt (test data)\n";
    cout << "  • test_integration_report.txt (test report)\n\n";
    
    return 0;
}