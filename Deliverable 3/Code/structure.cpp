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

// Delete system by name
bool SystemList::delete_system(string name) {
    if (!head) return false;
    
    Node* current = head;
    Node* start = head;
    
    do {
        if (current->data->name == name) {
            // Only one node
            if (current->next == current) {
                delete current->data;
                delete current;
                head = NULL;
            } else {
                // Update connections
                current->prev->next = current->next;
                current->next->prev = current->prev;
                
                // If deleting head, update head
                if (current == head) {
                    head = current->next;
                }
                
                delete current->data;
                delete current;
            }
            count--;
            return true;
        }
        current = current->next;
    } while (current != start);
    
    return false;
}
