#include <iostream>
using namespace std;

#include "structure.h"


int calculateRisk(System* sys) {
    int score = 0;
    
    // Password risk
    score += (10 - sys->passwordStrength) * 3;
    
    // Open ports risk
    score += sys->openPorts * 8;
    
    // Firewall risk
    if(!sys->firewallOn) score += 25;
    
    sys->riskScore = (score > 100) ? 100 : score;
    return sys->riskScore;
}

//  Selection Sort For Ranking
void sortSystems(System* systems[], int n) {
    for(int i = 0; i < n-1; i++) {
        int maxIndex = i;
        for(int j = i+1; j < n; j++) {
            if(systems[j]->riskScore > systems[maxIndex]->riskScore)
                maxIndex = j;
        }
        if(maxIndex != i) {
            System* temp = systems[i];
            systems[i] = systems[maxIndex];
            systems[maxIndex] = temp;
        }
    }
}
