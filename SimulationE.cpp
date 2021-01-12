#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>


using namespace std;

Simulation::Simulation(string line_description_file, string timetables_file){
    
    bool cancel {false};

    timetable = split_timeTable(timetables_file);

    if(timetable.size() == 2) {
    railway.push_back(Railway(line_description_file, &timetable[0]));
    railway.push_back(Railway());
    railway[1].reverse(railway[0], &timetable[1]);
    } else if(timetable[0].is_going()) {
        railway.push_back(Railway(line_description_file, &timetable[0]));
    } else {

        TimeTable temp;
        railway.push_back(Railway(line_description_file, &temp));
        railway.push_back(Railway());
        timetable[0].set_as_going();
        railway[1].reverse(railway[0], &timetable[0]);
        cancel = true;
    }

    cout << "____________ADJUST_TIMETABLE__________" << endl;
    for(int i=0; i<timetable.size(); i++) {
        timetable[i].adjust_timetable(railway[0].get_principal_count(), railway[0].get_station_count());
    }

    cout << "____________VERIFY_RAILWAY__________" << endl;
    railway[0].verify_railway();
    if(cancel){
        railway.erase(railway.begin());
    }

    cout << "_______RAILWAY & TIMETABLEs CORRETTE_______" << endl << endl;
    for(int i=0; i<railway.size(); i++) {
        cout << "Nella tratta sono presenti " << railway[i].get_station_count() << " stazioni delle quali " <<  railway[i].get_principal_count() << " sono principali." << endl; 
        cout << railway[i] << endl << *railway[i].get_timetable_reference() << endl << endl;
    }  
    
        RAILWAYS = railway.size();
    
    for(int i = 0; i < railway.size(); i++){
        trains.push_back(std::vector<std::unique_ptr<Train>> ());
    }

    for(int i=0; i<timetable.size(); i++){
        total_train_count += timetable[i].get_timetable_size();    
    }
    
}

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
                if(trains[i][j]->prev_distance() < railway[i].get_station(k).get_distance() - 20 && trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 20){
                    cout  << "Il treno "; //regionale n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                    if(trains[i][j]->get_type() == Train::type::Regional) cout << "regionale ";
                    else if(trains[i][j]->get_type() == Train::type::HighSpeed) cout << "alta velocita'";
                    else cout << "super alta velocita' ";

                    cout << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                
                }
                /*if(trains[i][j]->get_type() == Train::type::Regional){
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 22.7 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout  << "Il treno regionale n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                } else if(trains[i][j]->get_type() == Train::type::HighSpeed) {
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 24 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout  << "Il treno alta velocita n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                } else {
                    if(trains[i][j]->get_distance() > railway[i].get_station(k).get_distance() - 25 && trains[i][j]->get_distance() <= railway[i].get_station(k).get_distance() - 20){
                        cout  << "Il treno super alta velocita n. " << trains[i][j]->get_number() << " si trova a 20 km dalla stazione " << railway[i].get_station(k).get_name() << endl;
                        //cout << "[temp]...   train distance: " << trains[i][j]->get_distance() << "    station distance: " <<  railway[i].get_station(k).get_distance() << endl;
                        break;
                    }
                }*/
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
    if(trains_at_terminal < total_train_count)
        return false;
    return true;
}