#include "Simulation.h"
#include <iostream>

using namespace std;

int main()
{
    Simulation sim("data\\line_description.txt", "data\\timetables.txt");
    sim.simulate();
    return 0;
}
