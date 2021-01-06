#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>

//Per testing
#include <iostream>


using namespace std;

Simulation::Simulation(string line_description_file, string timetables_file){
    vector<TimeTable> timetables = split_timeTable(timetables_file);

    fw_timetable = timetables[0];
    bw_timetable = timetables[1];
    
    fw_railway = Railway(line_description_file, &fw_timetable);
    bw_railway.reverse(fw_railway, &bw_timetable);
}

void Simulation::step(){
    for(list<unique_ptr<Train>> &lst : fw_trains){
        for(unique_ptr<Train> &t : lst){
            t->step();
        }
    }
    for(list<unique_ptr<Train>> &lst : fw_trains){
        for(unique_ptr<Train> &t : lst){
            t->step();
        }
    }
}

bool Simulation::simulate(){
    step();
    return true;
}