#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>


using namespace std;


Simulation::Simulation(string line_description_file, string timetables_file){
    vector<TimeTable> timetables;
    try{
        timetables = split_timeTable(timetables_file);
    }catch(runtime_error e){cout << e.what();}
    
    fw_timetable = timetables[0];
    bw_timetable = timetables[1];

    fw_railway = Railway(line_description_file, &fw_timetable);
    bw_railway.reverse(fw_railway, &bw_timetable);

    cout << fw_railway << endl << bw_railway <<  endl;
}

void Simulation::step(){
    for(unique_ptr<Train> &t : fw_trains){
        	t->step();
    }
    for(unique_ptr<Train> &t : bw_trains){
        	t->step();
    }
}

bool Simulation::simulate(){
    while(!fw_trains.empty() && !bw_trains.empty())
        step();
    return true;
}


//deve ciclare su tutti i treni presenti in timetable, se è arrivata l'ora di partire e non sono già 
//stati messi in trains allora fallo partire se possibile (una linea libera e free_to_start) e inseriscilo nella banchina della prima stazione
void Simulation::start_trains(){
    if(fw_railway.get_beginning_station().can_add_train_to_stop()){
        
        for(int i = 0; i < fw_timetable.get_timetable_size(); i++){
            if(current_time > fw_timetable.get_timetable_element(i).time_at_station[0]){
                bool found = false;
                for(unique_ptr<Train> &t : fw_trains){
                    if(t->get_number() == fw_timetable.get_timetable_element(i).train_number){
                        found = true; 
                        break;
                    }          
                }
                if(!found){
                    
                    push_front_train(fw_timetable.get_timetable_element(i), &fw_trains);
                    fw_railway.get_beginning_station().add_train_to_stop(fw_trains[0].get());

                }
            }
        }

    }
    
}







void push_front_train(const timetable_element& a, vector<unique_ptr<Train>>* trains){
    if(a.train_type == Train::Regional){
        trains->push_back(unique_ptr<Regional>(new Regional(a.train_number)));
    }else if(a.train_type == Train::HighSpeed){
        trains->push_back(unique_ptr<HighSpeed>(new HighSpeed(a.train_number)));
    }else if(a.train_type == Train::SuperHighSpeed){
        trains->push_back(unique_ptr<SuperHighSpeed>(new SuperHighSpeed(a.train_number)));
    }
}