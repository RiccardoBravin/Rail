#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>


using namespace std;

void Simulation::sort_trains() {
    for(int i=0; i<trains.size(); i++) {
        vector<unique_ptr<Train>> replacer;
        while(trains[i].size() > 0) {
            int min_index {0};
            for(int j=0; j<trains[i].size(); j++) {
                if(trains[i][min_index]->get_distance() > trains[i][j]->get_distance())
                    min_index = j;
            }
            replacer.push_back(move(trains[i][min_index]));
            trains[i].erase(trains[i].begin() + min_index);
        }
        trains[i] = move(replacer);
    }
}

void Simulation::notice_20_km_mark() {
    for(int i=0; i<trains.size(); i++){                                     //ciclo sulle  railway
        for(int j=0; j<trains[i].size(); j++){                              //ciclo sui treni
            for(int k=1; k<railway[i].get_station_count(); k++){            //ciclo sulle stazioni (parto dalla seconda perchè devo verificare la distaznza mai prima della prima)
                //cout << "ci sto provando" << endl;
                if(trains[i][j]->get_type() == Train::type::Regional){
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 22.7 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout << endl << "Il treno regionale n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                } else if(trains[i][j]->get_type() == Train::type::HighSpeed) {
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 24 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout << endl << "Il treno alta velocita n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                } else {
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 25 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout << endl << "Il treno super alta velocita n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                }
            } 
        }
    }
}

void Simulation::ending_station() {
    for(int i=0; i<trains.size(); i++){                                     
        for(int j=0; j<trains[i].size(); j++){
            if(trains[i][j]->get_distance() > railway[i].get_terminal_station().get_distance() + 5){
                trains[i].erase(trains[i].begin() + j);
                trains_at_terminal++;
            }
        }
    }
}

bool Simulation::end_simulation(){
    for(int i=0; i<timetable.size(); i++){
        if(trains_at_terminal < timetable[i].get_timetable_size())
            return false;
    }

    return true;
}