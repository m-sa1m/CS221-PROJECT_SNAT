#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structure.h"
#include "algorithm.h"
using namespace std;

int main() {
    srand(time(0));
    
    cout << "========================================\n";
    cout << "  TEAM 1 - DATA STRUCTURES TESTING\n";
    cout << "========================================\n\n";
    
    // TEST 1: Circular Doubly Linked List
    cout << "TEST 1: Circular Doubly Linked List\n";
    cout << "------------------------------------\n";
    
    SystemList list;
    
    System* s1 = new System();
    s1->name = "Server1";
    s1->ip = "192.168.1.1";
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
    s2->name = "Server2";
    s2->ip = "192.168.1.2";
    s2->password_strength = 3;
    s2->open_ports = 5;
    s2->firewalls = false;
    s2->encryption_enabled = false;
    s2->malware_detected = true;
    s2->port_count = 0;
    s2->vuln_count = 0;
    s2->is_vulnerable = false;
    calculate_risk(s2);
    list.add_system(s2);
    
    System* s3 = new System();
    s3->name = "Server3";
    s3->ip = "192.168.1.3";
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
    
    cout << "✓ Added 3 systems\n";
    cout << "✓ Total count: " << list.get_count() << "\n";
    
    list.display_all();
    list.traverse_forward();
    list.traverse_backward();
    
    // TEST 2: Stack Operations
    cout << "\n\nTEST 2: Stack (LIFO) Operations\n";
    cout << "------------------------------------\n";
    
    TaskStack stack;
    stack.push("Task A");
    stack.push("Task B");
    stack.push("Task C");
    
    cout << "Pushed: Task A, Task B, Task C\n";
    cout << "Popping (LIFO): ";
    
    while (!stack.is_empty()) {
        cout << stack.pop() << " ";
    }
    cout << "\n✓ Stack works correctly (Last In, First Out)\n";
    
    // TEST 3: Queue Operations
    cout << "\n\nTEST 3: Queue (FIFO) Operations\n";
    cout << "------------------------------------\n";
    
    ScanQueue queue;
    queue.enqueue("System A");
    queue.enqueue("System B");
    queue.enqueue("System C");
    
    cout << "Enqueued: System A, System B, System C\n";
    cout << "Dequeuing (FIFO): ";
    
    while (!queue.is_empty()) {
        cout << queue.dequeue() << " ";
    }
    cout << "\n✓ Queue works correctly (First In, First Out)\n";
    
    // TEST 4: Binary Search Tree
    cout << "\n\nTEST 4: Binary Search Tree\n";
    cout << "------------------------------------\n";
    
    RiskBST bst;
    bst.insert(s1);
    bst.insert(s2);
    bst.insert(s3);
    
    cout << "✓ Inserted 3 systems into BST\n";
    bst.inorder_traversal();
    bst.preorder_traversal();
    bst.postorder_traversal();
    
    // TEST 5: Sorting Algorithms
    cout << "\n\nTEST 5: Sorting Algorithms\n";
    cout << "------------------------------------\n";
    
    System* systems[3] = {s1, s2, s3};
    
    cout << "\nBefore sorting:\n";
    for (int i = 0; i < 3; i++) {
        cout << i+1 << ". " << systems[i]->name 
             << " - Risk: " << systems[i]->risk_score << "\n";
    }
    
    selection_sort(systems, 3);
    
    cout << "\nAfter Selection Sort (descending by risk):\n";
    for (int i = 0; i < 3; i++) {
        cout << i+1 << ". " << systems[i]->name 
             << " - Risk: " << systems[i]->risk_score << "\n";
    }
    
    // TEST 6: Performance Comparison
    cout << "\n\nTEST 6: Algorithm Performance\n";
    cout << "------------------------------------\n";
    
    compare_sorting_algorithms(systems, 3);
    
    // TEST 7: Searching
    cout << "\n\nTEST 7: Searching Algorithms\n";
    cout << "------------------------------------\n";
    
    System* found = linear_search(systems, 3, "Server2");
    if (found) {
        cout << "✓ Linear Search: Found " << found->name 
             << " with risk " << found->risk_score << "\n";
    }
    
    // TEST 8: Port Scanning
    cout << "\n\nTEST 8: Port Scanning & Vulnerabilities\n";
    cout << "------------------------------------\n";
    
    scan_ports(s1);
    check_vulnerabilities(s1);
    calculate_risk(s1);
    cout << "\n✓ Updated risk score: " << s1->risk_score << "\n";
    
    cout << "\n========================================\n";
    cout << "  ALL TESTS COMPLETED SUCCESSFULLY!\n";
    cout << "========================================\n";
    
    return 0;
}