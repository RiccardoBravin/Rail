#include "Simulation.h"
#include <string>

//Per testing
#include <iostream>

using namespace std;

Simulation::Simulation(string line_description_file, std::string timetables_file){
    going_railway = Railway(line_description_file);
    return_railway = going_railway.reverse(return_railway); //andra tolto return_railway da uno dei due posti

    going_timetable = TimeTable(timetables_file); //?
    return_timetable = ?
    

}