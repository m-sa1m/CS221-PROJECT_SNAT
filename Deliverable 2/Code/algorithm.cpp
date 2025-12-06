cd#include <iostream>
using namespace std;

#include "algorithm.h"
#include "structure.h"

int calculate_risk(System* sys) {
    int score = 0;
    
    // Password risk
    score += (10 - sys->password_strength) * 3;
    
    // Open ports risk
    score += sys->open_ports * 8;
    
    // Firewall risk
    if(!sys->firewalls) score += 25;
    
    sys->risk_score = (score > 100) ? 100 : score;
    return sys->risk_score;
}

//  Selection Sort For Ranking
void sort_systems(System* systems[], int n) {
    for(int i = 0; i < n-1; i++) {
        int max_index = i;
        for(int j = i+1; j < n; j++) {
            if(systems[j]->risk_score > systems[max_index]->risk_score)
                max_index = j;
        }
        if(max_index != i) {
            System* temp = systems[i];
            systems[i] = systems[max_index];
            systems[max_index] = temp;
        }
    }
}
