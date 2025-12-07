#include <iostream>
using namespace std;
#include "structure.h"


int risk_weight[3]={30,25,35};

SystemList::SystemList()
{
    head = NULL;
}

void SystemList::add_system(System * sys)
{
    Node *newNode= new Node();
    newNode->data= sys;
    newNode->next= head;
    head = newNode;
}