#include "Simulation.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Benvenuto nel software di simulazione ERA (Elia-Riccardo-Angelo)\n";
    cout << "Per iniziare la simulazione premere INVIO";
    Simulation sim("data\\line_description.txt", "data\\timetables.txt");
    
    sim.simulate();
    return 0;
}
