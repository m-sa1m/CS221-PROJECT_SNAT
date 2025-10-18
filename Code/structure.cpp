#include <iostream>
using namespace std; 
struct System
{
    string name;
    int password_strength;
    int open_ports;
    bool firewalls;
    int risk_core;

};

int risk_weight[3]={30,25,35};

struct Node
{
    System*data;
    Node*next;  
};

struct SystemList
{
    Node* head;
    SystemList()
    {
        head = NULL;
    }

    void add_system(System * sys)
    {
        Node *newNode= new Node();
        newNode->data= sys;
        newNode->next= head;
        head = newNode;
    }

};