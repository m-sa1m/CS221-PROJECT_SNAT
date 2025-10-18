#include <iostream>
using namespace std; 
struct System
{
    string name;
    int PasswordStrength;
    int OpenPorts;
    bool FireWallsON;
    int RiskScore;

};

int RiskWeight[3]={30,25,35};

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

    void AddSystem(System * sys)
    {
        Node *newNode= new Node();
        newNode->data= sys;
        newNode->next= head;
        head = newNode;
    }
    
};