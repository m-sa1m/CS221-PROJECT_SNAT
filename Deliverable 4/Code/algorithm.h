#ifndef ALGORITHM_H
#define ALGORITHM_H
#pragma once


// Risk Calculation Algorithms
int calculate_risk(System* sys);
void calculate_all_risks(SystemList& list);


// Sorting Algorithms with Time Complexity

// O(n²) Algorithms
void selection_sort(System* systems[], int n);
void bubble_sort(System* systems[], int n);
void insertion_sort(System* systems[], int n);

// O(n log n) Algorithms
void quick_sort(System* systems[], int low, int high);
void merge_sort(System* systems[], int left, int right);

// Helper functions
int partition(System* systems[], int low, int high);
void merge(System* systems[], int left, int mid, int right);

// Searching Algorithms
System* linear_search(System* systems[], int n, string name);
System* binary_search_by_risk(System* systems[], int n, int risk_score);


// Port Scanning & Vulnerability Detection
void scan_ports(System* sys);
void check_vulnerabilities(System* sys);

// Performance Analysis
void compare_sorting_algorithms(System* systems[], int n);
double measure_sorting_time(void (*sort_func)(System*[], int), System* systems[], int n);



#endif