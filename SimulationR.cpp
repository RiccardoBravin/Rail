#include "Simulation.h"
#include <string>

//Per testing
#include <iostream>

using namespace std;

Simulation::Simulation(string line_description_file, std::string timetables_file){
    vector<TimeTable> timetables = split_timeTable(timetables_file);

    going_timetable = timetables[0];
    return_timetable = timetables[1];
    
    going_railway = Railway(line_description_file, &going_timetable);
    return_railway.reverse(going_railway, &return_timetable);

}