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


#endif