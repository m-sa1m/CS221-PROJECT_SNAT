#include <iostream>
using namespace std;

int main()
{
    cout << "=== Secure Netwok Assessment Tool (SNAT) - CORE IMPLEMENTATION ===\n";
    
    // harcoded inputs :
    System sys1 = {"webserver", 7, 2, true, 0};
    System sys2 = {"database", 3, 5, false, 0};
    System sys3 = {"pc", 9, 1, true, 0};

    System* systems[] = {&sys1, &sys2, &sys3};
    int count = 3;


    //to calculate risks
    cout << "\nCalculating Risk score...\n"; 
    for(int i = 0; i < count; i++) {
        calculateRisk(systems[i]);
    }
    

    // to sort by risks
    sortSystems(systems, count);


    //ouput
    cout << "\n=== RANKED SYSTEM ===\n";
    for(int i = 0; i < count; i++) {
        string level = (systems[i]->riskScore < 50) ? "LOW" : 
                      (systems[i]->riskScore < 80) ? "MEDIUM" : "HIGH";
        cout << i+1 << ". " << systems[i]->name << " - " 
             << systems[i]->riskScore << "/100 (" << level << ")\n";
    }
    

   //storing in linked-list 
    SystemList network;
    network.addSystem(&sys1);
    network.addSystem(&sys2);
    network.addSystem(&sys3);
    
    cout << "\nLinked List: 3 systems stored dynamically\n";
    
    return 0;
}


