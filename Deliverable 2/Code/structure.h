#ifndef STRUCTURE_H
#define STRUCTURE_H
#pragma once

#include<string>
using namespace std;

struct System
{
    string name;
    int password_strength;
    int open_ports;
    bool firewalls;
    int risk_score;

};

struct Node
{
    System*data;
    Node*next;  
};

struct SystemList
{
    Node* head;
    SystemList();

    void add_system(System *);

};

#endif