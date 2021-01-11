#include "Simulation.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Benvenuto nel software di simulazione ERA (Elia-Riccardo-Angelo)\n";
    cout << "Per iniziare la simulazione premere INVIO\n";
    getchar();
    Simulation sim("data\\line_description.txt", "data\\timetables.txt");
    cout << "Una volta ulimata la visione degli orari e ferrovie premere INVIO\n";
    getchar();
    
    sim.simulate();

    return 0;
}
