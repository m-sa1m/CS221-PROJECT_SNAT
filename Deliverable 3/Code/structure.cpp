#include <iostream>
#include "structure.h"
using namespace std;

// SystemList Implementation

// Constructor - Initialize empty list
SystemList::SystemList() {
    head = NULL;
    count = 0;
}

// Destructor - Free all memory
SystemList::~SystemList() {
    if (!head) return;
    
    Node* current = head;
    Node* start = head;
    
    // Traverse and delete all nodes
    do {
        Node* temp = current;
        current = current->next;
        delete temp->data;  // Delete system data
        delete temp;        // Delete node
    } while (current != start);
}

// Add system to circular doubly linked list
void SystemList::add_system(System* sys) {
    Node* newNode = new Node();
    newNode->data = sys;
    
    if (!head) {
        // First node - point to itself
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        // Insert at end (before head)
        Node* last = head->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = head;
        head->prev = newNode;
    }
    count++;
}
