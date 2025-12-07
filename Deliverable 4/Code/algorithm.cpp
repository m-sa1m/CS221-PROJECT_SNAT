#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "algorithm.h"
#include "structure.h"
using namespace std;

// Risk weights array
int risk_weights[5] = {25, 30, 15, 20, 10}; // Password, Ports, Encryption, Malware, Firewall


// SECTION 1: Risk Calculation

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


// SECTION 2: Sorting Algorithms

// Selection Sort - O(n²)
// Best for: Small datasets
void selection_sort(System* systems[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        
        // Find maximum in remaining array
        for (int j = i + 1; j < n; j++) {
            if (systems[j]->risk_score > systems[max_idx]->risk_score) {
                max_idx = j;
            }
        }
        
        // Swap if needed
        if (max_idx != i) {
            System* temp = systems[i];
            systems[i] = systems[max_idx];
            systems[max_idx] = temp;
        }
    }
}

// Bubble Sort - O(n²)
// Best for: Nearly sorted data
void bubble_sort(System* systems[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (systems[j]->risk_score < systems[j + 1]->risk_score) {
                System* temp = systems[j];
                systems[j] = systems[j + 1];
                systems[j + 1] = temp;
                swapped = true;
            }
        }
        
        // Optimization: break if no swaps
        if (!swapped) break;
    }
}

// Insertion Sort - O(n²) worst case, O(n) best case
// Best for: Small or nearly sorted datasets
void insertion_sort(System* systems[], int n) {
    for (int i = 1; i < n; i++) {
        System* key = systems[i];
        int j = i - 1;
        
        // Move elements greater than key
        while (j >= 0 && systems[j]->risk_score < key->risk_score) {
            systems[j + 1] = systems[j];
            j--;
        }
        
        systems[j + 1] = key;
    }
}

// Quick Sort Helper - Partition function
int partition(System* systems[], int low, int high) {
    int pivot = systems[high]->risk_score;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (systems[j]->risk_score >= pivot) {
            i++;
            System* temp = systems[i];
            systems[i] = systems[j];
            systems[j] = temp;
        }
    }
    
    System* temp = systems[i + 1];
    systems[i + 1] = systems[high];
    systems[high] = temp;
    
    return i + 1;
}

// Quick Sort - O(n log n) average, O(n²) worst case
// Best for: Large datasets, general purpose
void quick_sort(System* systems[], int low, int high) {
    if (low < high) {
        int pi = partition(systems, low, high);
        
        quick_sort(systems, low, pi - 1);
        quick_sort(systems, pi + 1, high);
    }
}

// Merge Sort Helper - Merge function
void merge(System* systems[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temp arrays
    System** L = new System*[n1];
    System** R = new System*[n2];
    
    // Copy data
    for (int i = 0; i < n1; i++)
        L[i] = systems[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = systems[mid + 1 + j];
    
    // Merge arrays
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i]->risk_score >= R[j]->risk_score) {
            systems[k] = L[i];
            i++;
        } else {
            systems[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining
    while (i < n1) {
        systems[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        systems[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

// Merge Sort - O(n log n) guaranteed
// Best for: Large datasets requiring stable sort
void merge_sort(System* systems[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(systems, left, mid);
        merge_sort(systems, mid + 1, right);
        merge(systems, left, mid, right);
    }
}


// SECTION 3: Searching Algorithms

// Linear Search - O(n)
System* linear_search(System* systems[], int n, string name) {
    for (int i = 0; i < n; i++) {
        if (systems[i]->name == name) {
            return systems[i];
        }
    }
    return NULL;
}

// Binary Search - O(log n) - requires sorted array
System* binary_search_by_risk(System* systems[], int n, int risk_score) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (systems[mid]->risk_score == risk_score) {
            return systems[mid];
        }
        
        // Since sorted in descending order
        if (systems[mid]->risk_score > risk_score) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return NULL;
}


// SECTION 4: Port Scanning & Vulnerability

void scan_ports(System* sys) {
    cout << "\n[SCANNING] Ports for " << sys->name << " (" << sys->ip << ")...\n";
    
    int common_ports[] = {21, 22, 23, 80, 443, 3389, 8080, 53, 110, 25};
    string port_services[] = {"FTP", "SSH", "Telnet", "HTTP", "HTTPS", 
                             "RDP", "HTTP-Alt", "DNS", "POP3", "SMTP"};
    
    sys->port_count = 0;
    
    for (int i = 0; i < 10; i++) {
        if (rand() % 2) {  // 50% chance port is open
            sys->port_list[sys->port_count] = common_ports[i];
            sys->services[sys->port_count] = port_services[i];
            sys->port_count++;
            cout << "  [OPEN] Port " << common_ports[i] 
                 << " (" << port_services[i] << ")\n";
        }
    }
    
    sys->open_ports = sys->port_count;
    
    if (sys->port_count == 0) {
        cout << "  [INFO] No open ports detected\n";
    }
}

void check_vulnerabilities(System* sys) {
    cout << "\n[CHECKING] Vulnerabilities for " << sys->name << "...\n";
    
    sys->vuln_count = 0;
    sys->is_vulnerable = false;
    
    for (int i = 0; i < sys->port_count; i++) {
        if (sys->port_list[i] == 21 && rand() % 2) {
            sys->vulnerabilities[sys->vuln_count++] = "FTP Anonymous Login";
            sys->is_vulnerable = true;
            cout << "  [!] FTP Anonymous Login Enabled\n";
        }
        if (sys->port_list[i] == 23) {
            sys->vulnerabilities[sys->vuln_count++] = "Telnet Unencrypted";
            sys->is_vulnerable = true;
            cout << "  [!] Telnet Service (Unencrypted)\n";
        }
        if (sys->port_list[i] == 80 && rand() % 2) {
            sys->vulnerabilities[sys->vuln_count++] = "HTTP No HTTPS";
            sys->is_vulnerable = true;
            cout << "  [!] HTTP without HTTPS redirect\n";
        }
        if (sys->port_list[i] == 3389 && rand() % 2) {
            sys->vulnerabilities[sys->vuln_count++] = "RDP Exposed";
            sys->is_vulnerable = true;
            cout << "  [!] RDP exposed to internet\n";
        }
    }
    
    if (sys->vuln_count == 0) {
        cout << "  [✓] No vulnerabilities found\n";
    }
}

// ============================================
// SECTION 5: Performance Analysis
// ============================================

double measure_sorting_time(void (*sort_func)(System*[], int), System* systems[], int n) {
    // Create copy to not modify original
    System** copy = new System*[n];
    for (int i = 0; i < n; i++) {
        copy[i] = systems[i];
    }
    
    auto start = chrono::high_resolution_clock::now();
    sort_func(copy, n);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, micro> duration = end - start;
    delete[] copy;
    
    return duration.count();
}

void compare_sorting_algorithms(System* systems[], int n) {
    cout << "\n========================================\n";
    cout << "  SORTING ALGORITHM PERFORMANCE\n";
    cout << "========================================\n";
    cout << "Dataset size: " << n << " systems\n\n";
    
    double time_selection = measure_sorting_time(selection_sort, systems, n);
    double time_bubble = measure_sorting_time(bubble_sort, systems, n);
    double time_insertion = measure_sorting_time(insertion_sort, systems, n);
    
    cout << "1. Selection Sort: " << time_selection << " μs (O(n²))\n";
    cout << "2. Bubble Sort:    " << time_bubble << " μs (O(n²))\n";
    cout << "3. Insertion Sort: " << time_insertion << " μs (O(n²))\n";
    
    cout << "\n[NOTE] Quick Sort and Merge Sort (O(n log n))\n";
    cout << "       would be significantly faster for n > 100\n";
    
    // Determine fastest
    string fastest = "Selection Sort";
    double min_time = time_selection;
    
    if (time_bubble < min_time) {
        fastest = "Bubble Sort";
        min_time = time_bubble;
    }
    if (time_insertion < min_time) {
        fastest = "Insertion Sort";
        min_time = time_insertion;
    }
    
    cout << "\n✓ Fastest for this dataset: " << fastest << "\n";
}