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

// Search system by name
System* SystemList::search_system(string name) {
    if (!head) return NULL;
    
    Node* current = head;
    Node* start = head;
    
    do {
        if (current->data->name == name) {
            return current->data;
        }
        current = current->next;
    } while (current != start);
    
    return NULL;
}

// Get total count
int SystemList::get_count() {
    return count;
}

// Display all systems
void SystemList::display_all() {
    if (!head) {
        cout << "No systems in the network.\n";
        return;
    }
    
    Node* temp = head;
    int index = 1;
    
    cout << "\n========== ALL SYSTEMS ==========\n";
    do {
        System* s = temp->data;
        string level = (s->risk_score < 50) ? "LOW" : 
                      (s->risk_score < 80) ? "MEDIUM" : "HIGH";
        
        cout << index++ << ". " << s->name << " (" << s->ip << ")\n";
        cout << "   Risk Score: " << s->risk_score << "/100 (" << level << ")\n";
        cout << "   Open Ports: " << s->open_ports << " | Firewall: " 
             << (s->firewalls ? "ON" : "OFF") << "\n";
        cout << "   --------------------------------\n";
        
        temp = temp->next;
    } while (temp != head);
}


// Display only high-risk systems
void SystemList::display_high_risk() {
    if (!head) {
        cout << "No systems in the network.\n";
        return;
    }
    
    Node* temp = head;
    bool found = false;
    
    cout << "\n========== HIGH RISK SYSTEMS (≥80) ==========\n";
    do {
        if (temp->data->risk_score >= 80) {
            System* s = temp->data;
            cout << "- " << s->name << " (" << s->ip << ") - Risk: " 
                 << s->risk_score << "/100\n";
            found = true;
        }
        temp = temp->next;
    } while (temp != head);
    
    if (!found) {
        cout << "No high-risk systems found.\n";
    }
}

// Display system by IP
void SystemList::display_by_ip(string ip) {
    if (!head) {
        cout << "No systems in the network.\n";
        return;
    }
    
    Node* temp = head;
    Node* start = head;
    System* sys = NULL;
    
    do {
        if (temp->data->ip == ip) {
            sys = temp->data;
            break;
        }
        temp = temp->next;
    } while (temp != start);
    
    if (sys) {
        cout << "\n=== System Details ===\n";
        cout << "Name: " << sys->name << "\n";
        cout << "IP: " << sys->ip << "\n";
        cout << "Risk Score: " << sys->risk_score << "/100\n";
        cout << "Password Strength: " << sys->password_strength << "/10\n";
        cout << "Firewall: " << (sys->firewalls ? "ON" : "OFF") << "\n";
    } else {
        cout << "System with IP " << ip << " not found.\n";
    }
}

// Get head pointer
Node* SystemList::get_head() {
    return head;
}

// Forward traversal
void SystemList::traverse_forward() {
    if (!head) {
        cout << "List is empty.\n";
        return;
    }
    
    Node* temp = head;
    cout << "\nForward Traversal: ";
    do {
        cout << temp->data->name << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to start)\n";
}

// Backward traversal
void SystemList::traverse_backward() {
    if (!head) {
        cout << "List is empty.\n";
        return;
    }
    
    Node* temp = head->prev;
    cout << "\nBackward Traversal: ";
    do {
        cout << temp->data->name << " -> ";
        temp = temp->prev;
    } while (temp != head->prev);
    cout << temp->data->name << "\n";
}

// ============ TaskStack Implementation ============

TaskStack::TaskStack() {
    top = -1;
}

void TaskStack::push(string task) {
    if (!is_full()) {
        tasks[++top] = task;
    } else {
        cout << "[ERROR] Stack is full!\n";
    }
}

string TaskStack::pop() {
    if (!is_empty()) {
        return tasks[top--];
    }
    return "";
}

bool TaskStack::is_empty() {
    return top == -1;
}

bool TaskStack::is_full() {
    return top >= 19;
}

int TaskStack::size() {
    return top + 1;
}

// ScanQueue Implementation 

ScanQueue::ScanQueue() {
    front = 0;
    rear = -1;
    count = 0;
}

void ScanQueue::enqueue(string task) {
    if (!is_full()) {
        rear = (rear + 1) % 20;
        tasks[rear] = task;
        count++;
    } else {
        cout << "[ERROR] Queue is full!\n";
    }
}

string ScanQueue::dequeue() {
    if (!is_empty()) {
        string task = tasks[front];
        front = (front + 1) % 20;
        count--;
        return task;
    }
    return "";
}

bool ScanQueue::is_empty() {
    return count == 0;
}

bool ScanQueue::is_full() {
    return count >= 20;
}

int ScanQueue::size() {
    return count;
}


// RiskBST Implementation 

RiskBST::RiskBST() {
    root = NULL;
}

RiskBST::~RiskBST() {
    destroy_tree(root);
}

void RiskBST::destroy_tree(BSTNode* node) {
    if (node) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

BSTNode* RiskBST::insert_helper(BSTNode* node, System* sys) {
    if (!node) {
        BSTNode* newNode = new BSTNode();
        newNode->data = sys;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    
    if (sys->risk_score < node->data->risk_score) {
        node->left = insert_helper(node->left, sys);
    } else {
        node->right = insert_helper(node->right, sys);
    }
    
    return node;
}

void RiskBST::insert(System* sys) {
    root = insert_helper(root, sys);
}

void RiskBST::inorder_helper(BSTNode* node) {
    if (node) {
        inorder_helper(node->left);
        cout << node->data->name << " (Risk: " << node->data->risk_score << ") -> ";
        inorder_helper(node->right);
    }
}

void RiskBST::inorder_traversal() {
    cout << "\nInorder Traversal (Sorted by Risk - Ascending): ";
    if (!root) {
        cout << "Empty tree\n";
        return;
    }
    inorder_helper(root);
    cout << "END\n";
}

void RiskBST::preorder_helper(BSTNode* node) {
    if (node) {
        cout << node->data->name << " (Risk: " << node->data->risk_score << ") -> ";
        preorder_helper(node->left);
        preorder_helper(node->right);
    }
}

void RiskBST::preorder_traversal() {
    cout << "\nPreorder Traversal: ";
    if (!root) {
        cout << "Empty tree\n";
        return;
    }
    preorder_helper(root);
    cout << "END\n";
}

void RiskBST::postorder_helper(BSTNode* node) {
    if (node) {
        postorder_helper(node->left);
        postorder_helper(node->right);
        cout << node->data->name << " (Risk: " << node->data->risk_score << ") -> ";
    }
}

void RiskBST::postorder_traversal() {
    cout << "\nPostorder Traversal: ";
    if (!root) {
        cout << "Empty tree\n";
        return;
    }
    postorder_helper(root);
    cout << "END\n";
}

BSTNode* RiskBST::search_helper(BSTNode* node, int risk_score) {
    if (!node || node->data->risk_score == risk_score) {
        return node;
    }
    
    if (risk_score < node->data->risk_score) {
        return search_helper(node->left, risk_score);
    }
    return search_helper(node->right, risk_score);
}

System* RiskBST::search_by_risk(int risk_score) {
    BSTNode* result = search_helper(root, risk_score);
    return result ? result->data : NULL;
}