#include <iostream>
using namespace std;

#include"algorithm.h"
#include "structure.h"

int main()
{
    cout << "\nSecure Netwok Assessment Tool (SNAT) \n";
    
    // harcoded inputs :
    System sys1 = {"webserver", 7, 2, true, 0};
    System sys2 = {"database", 3, 5, false, 0};
    System sys3 = {"pc", 9, 1, true, 0};

    System* systems[] = {&sys1, &sys2, &sys3};
    int count = 3;


    //to calculate risks
    cout << "\nCalculating Risk score...\n"; 
    for(int i = 0; i < count; i++) {
        calculate_risk(systems[i]);
    }
    

    // to sort by risks
    sort_systems(systems, count);


    //ouput
    cout << "\n   RANKED SYSTEM \n\n";
    for(int i = 0; i < count; i++) {
        string level = (systems[i]->risk_score < 50) ? "LOW" : 
                      (systems[i]->risk_score < 80) ? "MEDIUM" : "HIGH";
        cout << i+1 << ". " << systems[i]->name << " - " 
             << systems[i]->risk_score << "/100 (" << level << ")\n";
    }
    

   // linked-list 
    SystemList network;
    network.add_system(&sys1);
    network.add_system(&sys2);
    network.add_system(&sys3);
    
    cout << "\nLinked List: 3 systems stored \n";
    
    return 0;
}


