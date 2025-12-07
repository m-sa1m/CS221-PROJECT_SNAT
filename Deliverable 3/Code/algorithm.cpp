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
