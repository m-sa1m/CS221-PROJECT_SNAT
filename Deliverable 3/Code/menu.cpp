#include <iostream>
#include <cstdlib>
#include "menu.h"
#include "algorithm.h"
#include "input.h"
#include "fileio.h"
using namespace std;

// Utility Functions


void print_header(string title) {
    cout << "\n===================\n";
    cout << "  " << title << "\n";
    cout << "====================\n";
}

void pause_screen() {
    cout << "\nPress Enter to continue.";
    cin.ignore();
    cin.get();
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Display Menu Functions


void display_main_menu() {
    print_header("SECURE NETWORK ASSESSMENT TOOL (SNAT)");
    cout << "1.  Add New System\n";
    cout << "2.  Delete System\n";
    cout << "3.  Search System\n";
    cout << "4.  Scan & Assess System\n";
    cout << "5.  Sort Systems\n";
    cout << "6.  Display Options\n";
    cout << "7.  Performance Analysis\n";
    cout << "8.  File Operations\n";
    cout << "9.  Exit\n";
    cout << "\nEnter choice: ";
}

void display_sort_menu() {
    print_header("SORTING OPTIONS");
    cout << "1. Selection Sort (O(n²))\n";
    cout << "2. Bubble Sort (O(n²))\n";
    cout << "3. Insertion Sort (O(n²))\n";
    cout << "4. Quick Sort (O(n log n))\n";
    cout << "5. Merge Sort (O(n log n))\n";
    cout << "6. Compare All Algorithms\n";
    cout << "7. Back to Main Menu\n";
    cout << "\nEnter choice: ";
}

void display_search_menu() {
    print_header("SEARCH OPTIONS");
    cout << "1. Search by Name (Linear Search)\n";
    cout << "2. Search by IP Address\n";
    cout << "3. Search by Risk Score (Binary Search)\n";
    cout << "4. Back to Main Menu\n";
    cout << "\nEnter choice: ";
}

void display_analysis_menu() {
    print_header("PERFORMANCE ANALYSIS");
    cout << "1. Time Complexity Analysis\n";
    cout << "2. View BST Traversals\n";
    cout << "3. Stack/Queue Operations Demo\n";
    cout << "4. Back to Main Menu\n";
    cout << "\nEnter choice: ";
}


// Handler: Add System


void handle_add_system(SystemList& list) {
    clear_screen();
    print_header("ADD NEW SYSTEM");
    
    System* sys = new System();
    
    cout << "Enter system details:\n\n";
    
    sys->name = get_string_input("System Name");
    sys->ip = get_ip_input("IP Address");
    sys->password_strength = get_int_input("Password Strength", 1, 10);
    sys->open_ports = get_int_input("Number of Open Ports", 0, 10);
    sys->firewalls = get_bool_input("Firewall Enabled");
    sys->encryption_enabled = get_bool_input("Encryption Enabled");
    sys->malware_detected = get_bool_input("Malware Detected");
    
    // Initialize arrays
    sys->port_count = 0;
    sys->vuln_count = 0;
    sys->is_vulnerable = false;
    
    // Calculate risk
    calculate_risk(sys);
    
    // Add to list
    list.add_system(sys);
    
    string level = (sys->risk_score < 50) ? "LOW" : 
                  (sys->risk_score < 80) ? "MEDIUM" : "HIGH";
    
    cout << "\n✅ SUCCESS!\n";
    cout << "System '" << sys->name << "' added successfully.\n";
    cout << "Risk Score: " << sys->risk_score << "/100 [" << level << "]\n";
    
    pause_screen();
}


// Handler: Delete System


void handle_delete_system(SystemList& list) {
    clear_screen();
    print_header("DELETE SYSTEM");
    
    if (list.get_count() == 0) {
        cout << "❌ No systems to delete.\n";
        pause_screen();
        return;
    }
    
    // Show current systems
    list.display_all();
    
    string name = get_string_input("\nEnter system name to delete");
    
    if (list.delete_system(name)) {
        cout << "\n✅ System '" << name << "' deleted successfully!\n";
    } else {
        cout << "\n❌ System '" << name << "' not found.\n";
    }
    
    pause_screen();
}


// Handler: Search System


void handle_search_system(SystemList& list) {
    clear_screen();
    int choice;
    
    if (list.get_count() == 0) {
        cout << "❌ No systems to search.\n";
        pause_screen();
        return;
    }
    
    display_search_menu();
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: {
            string name = get_string_input("Enter system name");
            System* sys = list.search_system(name);
            
            if (sys) {
                cout << "\n✅ FOUND!\n";
                cout << "----------------------------------------\n";
                cout << "Name:              " << sys->name << "\n";
                cout << "IP:                " << sys->ip << "\n";
                cout << "Risk Score:        " << sys->risk_score << "/100\n";
                cout << "Password Strength: " << sys->password_strength << "/10\n";
                cout << "Firewall:          " << (sys->firewalls ? "ON" : "OFF") << "\n";
                cout << "Encryption:        " << (sys->encryption_enabled ? "ON" : "OFF") << "\n";
            } else {
                cout << "\n❌ System '" << name << "' not found.\n";
            }
            break;
        }
        case 2: {
            string ip = get_ip_input("Enter IP address");
            list.display_by_ip(ip);
            break;
        }
        case 3: {
            int risk = get_int_input("Enter risk score", 0, 100);
            cout << "\n[INFO] Binary search requires sorted data.\n";
            cout << "Please use 'Sort Systems' menu first.\n";
            break;
        }
        case 4:
            return;
        default:
            cout << "❌ Invalid choice.\n";
    }
    
    pause_screen();
}

// ============================================
// Handler: Scan System
// ============================================

void handle_scan_system(SystemList& list) {
    clear_screen();
    print_header("SCAN & ASSESS SYSTEM");
    
    if (list.get_count() == 0) {
        cout << "❌ No systems to scan.\n";
        pause_screen();
        return;
    }
    
    list.display_all();
    
    string name = get_string_input("\nEnter system name to scan");
    System* sys = list.search_system(name);
    
    if (sys) {
        cout << "\n🔍 Starting comprehensive scan...\n";
        
        scan_ports(sys);
        check_vulnerabilities(sys);
        calculate_risk(sys);
        
        string level = (sys->risk_score < 50) ? "LOW" : 
                      (sys->risk_score < 80) ? "MEDIUM" : "HIGH";
        
        cout << "\n✅ SCAN COMPLETE!\n";
        cout << "Updated Risk Score: " << sys->risk_score << "/100 [" << level << "]\n";
        
        if (sys->is_vulnerable) {
            cout << "\n⚠️  VULNERABILITIES DETECTED!\n";
            cout << "Please review the system immediately.\n";
        }
    } else {
        cout << "\n❌ System not found.\n";
    }
    
    pause_screen();
}


// Handler: Sort Systems

void handle_sort_systems(SystemList& list) {
    clear_screen();
    
    if (list.get_count() == 0) {
        cout << "❌ No systems to sort.\n";
        pause_screen();
        return;
    }
    
    display_sort_menu();
    int choice;
    cin >> choice;
    cin.ignore();
    
    // Convert linked list to array for sorting
    int count = list.get_count();
    System** systems = new System*[count];
    
    Node* temp = list.get_head();
    for (int i = 0; i < count; i++) {
        systems[i] = temp->data;
        temp = temp->next;
    }
    
    switch (choice) {
        case 1:
            cout << "\n⏳ Sorting with Selection Sort...\n";
            selection_sort(systems, count);
            cout << "✅ Sorted using Selection Sort (O(n²))\n";
            break;
        case 2:
            cout << "\n⏳ Sorting with Bubble Sort...\n";
            bubble_sort(systems, count);
            cout << "✅ Sorted using Bubble Sort (O(n²))\n";
            break;
        case 3:
            cout << "\n⏳ Sorting with Insertion Sort...\n";
            insertion_sort(systems, count);
            cout << "✅ Sorted using Insertion Sort (O(n²))\n";
            break;
        case 4:
            cout << "\n⏳ Sorting with Quick Sort...\n";
            quick_sort(systems, 0, count - 1);
            cout << "✅ Sorted using Quick Sort (O(n log n))\n";
            break;
        case 5:
            cout << "\n⏳ Sorting with Merge Sort...\n";
            merge_sort(systems, 0, count - 1);
            cout << "✅ Sorted using Merge Sort (O(n log n))\n";
            break;
        case 6:
            compare_sorting_algorithms(systems, count);
            delete[] systems;
            pause_screen();
            return;
        case 7:
            delete[] systems;
            return;
        default:
            cout << "❌ Invalid choice.\n";
            delete[] systems;
            pause_screen();
            return;
    }
    
    // Display sorted results
    cout << "\n=== SORTED SYSTEMS (Descending by Risk) ===\n";
    for (int i = 0; i < count; i++) {
        string level = (systems[i]->risk_score < 50) ? "LOW" : 
                      (systems[i]->risk_score < 80) ? "MEDIUM" : "HIGH";
        cout << i + 1 << ". " << systems[i]->name 
             << " - Risk: " << systems[i]->risk_score << "/100 [" << level << "]\n";
    }
    
    delete[] systems;
    pause_screen();
}



// Handler: Display Options


void handle_display_options(SystemList& list) {
    clear_screen();
    print_header("DISPLAY OPTIONS");
    
    if (list.get_count() == 0) {
        cout << "❌ No systems in the network.\n";
        pause_screen();
        return;
    }
    
    cout << "1. Display All Systems\n";
    cout << "2. Display High Risk Systems\n";
    cout << "3. Forward Traversal (Circular)\n";
    cout << "4. Backward Traversal (Circular)\n";
    cout << "5. Back to Main Menu\n";
    cout << "\nEnter choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1:
            list.display_all();
            break;
        case 2:
            list.display_high_risk();
            break;
        case 3:
            list.traverse_forward();
            break;
        case 4:
            list.traverse_backward();
            break;
        case 5:
            return;
        default:
            cout << "❌ Invalid choice.\n";
    }
    
    pause_screen();
}


// Handler: Performance Analysis


void handle_analysis(SystemList& list) {
    clear_screen();
    
    display_analysis_menu();
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: {
            if (list.get_count() == 0) {
                cout << "❌ No systems for analysis.\n";
                break;
            }
            
            int count = list.get_count();
            System** systems = new System*[count];
            
            Node* temp = list.get_head();
            for (int i = 0; i < count; i++) {
                systems[i] = temp->data;
                temp = temp->next;
            }
            
            compare_sorting_algorithms(systems, count);
            delete[] systems;
            break;
        }
        case 2: {
            if (list.get_count() == 0) {
                cout << "❌ No systems to analyze.\n";
                break;
            }
            
            RiskBST bst;
            Node* temp = list.get_head();
            Node* start = temp;
            
            cout << "\n🌳 Building Binary Search Tree...\n";
            do {
                bst.insert(temp->data);
                temp = temp->next;
            } while (temp != start);
            
            cout << "✅ BST constructed!\n";
            bst.inorder_traversal();
            bst.preorder_traversal();
            bst.postorder_traversal();
            break;
        }
        case 3: {
            cout << "\n=== STACK DEMONSTRATION (LIFO) ===\n";
            TaskStack stack;
            
            cout << "Pushing tasks: A, B, C, D\n";
            stack.push("Task A");
            stack.push("Task B");
            stack.push("Task C");
            stack.push("Task D");
            
            cout << "\nPopping tasks (Last In, First Out):\n";
            while (!stack.is_empty()) {
                cout << "  ← " << stack.pop() << "\n";
            }
            
            cout << "\n=== QUEUE DEMONSTRATION (FIFO) ===\n";
            ScanQueue queue;
            
            cout << "Enqueueing: System-1, System-2, System-3\n";
            queue.enqueue("System-1");
            queue.enqueue("System-2");
            queue.enqueue("System-3");
            
            cout << "\nDequeuing (First In, First Out):\n";
            while (!queue.is_empty()) {
                cout << "  → " << queue.dequeue() << "\n";
            }
            
            cout << "\n✅ Stack and Queue working correctly!\n";
            break;
        }
        case 4:
            return;
        default:
            cout << "❌ Invalid choice.\n";
    }
    
    pause_screen();
}

