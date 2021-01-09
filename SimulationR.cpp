#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>


using namespace std;


Simulation::Simulation(string line_description_file, string timetables_file){
    try{
        timetable = split_timeTable(timetables_file);
    }catch(runtime_error e){cout << e.what();}
    
    for(int i = 0; i < RAILWAYS; i = i+2){
        railway.push_back(Railway(line_description_file, &timetable[i]));
        Railway bw;
        bw.reverse(railway.back(), &timetable[i+1]);
        railway.push_back(bw);
        
        timetable[i].adjust_timetable(railway[i].get_principal_count(), railway[i].get_station_count());
        timetable[i+1].adjust_timetable(railway[i+1].get_principal_count(), railway[i+1].get_station_count());

        railway[i].verify_railway();

        cout << railway[i] << endl << timetable[i] << endl;
        cout << railway[i+1] << endl << timetable[i+1] << endl;
    }
    
    
}

bool Simulation::simulate(){
    while(current_time < 200){
        cout << "~~~~~~      " << current_time << "      ~~~~~~\n";
        start_trains();
        exit_station();
        step();
        current_time++;
        cout << endl;
    };
    return true;
}


void Simulation::step(){
    for(vector<unique_ptr<Train>> &trainsVec : trains){
        for(unique_ptr<Train> &t : trainsVec){
        	//cout << *t.get() << endl;
            t->step();
        }
    }
}




void Simulation::start_trains(){
    for(int k = 0; k < RAILWAYS; k++){

        if(free_to_start(&railway[k].get_beginning_station(), k) && railway[k].get_station(0).can_add_train_to_stop()){ 
            
            for(int i = 0; i < timetable[k].get_timetable_size(); i++){
                if(current_time >= timetable[k].get_timetable_element(i).time_at_station[0]){
                    
                    bool found = false;
                    for(unique_ptr<Train> &t : trains[k]){
                        if(t->get_number() == timetable[k].get_timetable_element(i).train_number){
                            
                            found = true; 
                            break;
                        }          
                    }
                    
                    if(!found){
                        push_front_train(timetable[k].get_timetable_element(i), &trains[k]);
                        railway[k].get_beginning_station().add_train_to_stop(trains[k][0].get());
                        trains[k][0]->set_speed(80);
                        cout << "Il treno numero " << trains[k][0]->get_number() << " e' in partenza dalla\n" << railway[k].get_station(i) << endl;
                        cout << *trains[k][0];
                    }
                }
                
            }
        }
        
    }
}


bool Simulation::free_to_start(Station* st,  int trains_index) const{  //MANCA IL CONTROLLO A SECONDA DELLA STAZIONE PER VERIFICARE CHE IL BINARIO DI TRANSITO SIA LIBBERO
    
    
    for(int i = 0; i < trains[trains_index].size(); i++){
        if(!trains[trains_index][i]->stationary())
            if(st->get_distance() < trains[trains_index][i]->get_distance() && st->get_distance() + 10 > trains[trains_index][i]->get_distance()){
                return false;
            }
            if(st->get_type() == Station::Secondary){
                if(trains[trains_index][i]->get_type() == Train::SuperHighSpeed){
                    if(st->get_distance() - 25 > trains[trains_index][i]->get_distance() && st->get_distance() - 8 > trains[trains_index][i]->get_distance())
                        return false;
                }else if(trains[trains_index][i]->get_type() == Train::HighSpeed){
                    if(st->get_distance() - 21 > trains[trains_index][i]->get_distance() && st->get_distance() - 5 > trains[trains_index][i]->get_distance())
                        return false;
                }
            }
    }

    
    return true;
}



void Simulation::exit_station(){//se un treno sta uscendo dalla stazione allora va alla velocità massima
    for(int k = 0; k < RAILWAYS; k++){
        for(int i = 0; i < railway[k].get_station_count(); i++){ //cicla sulla dimensione della railway
            //cout << endl<< trains[k].size() <<endl;
            for(int j = 0; j < trains[k].size(); j++){
                if(trains[k][j]->prev_distance() < railway[k].get_station(i).get_distance() + 5 && trains[k][j]->get_distance() > railway[k].get_station(i).get_distance() + 5){
                    
                    if(railway[k].get_station(i).remove_train_to_stop(trains[k][j].get())){
                        trains[k][j]->set_speed(300);
                        cout << "Il treno numero " << trains[k][j]->get_number() << " e' uscito dalla\n" << railway[k].get_station(i) << endl;
                        cout << *trains[k][j];
                        break;
                    }else{
                        //railway[k].get_station(i).remove_train_to_transit(trains[k][i].get())
                    }

                }
            }
        }
    }
}


void push_front_train(const timetable_element& a, vector<unique_ptr<Train>>* tr){
    if(a.train_type == Train::Regional){
        tr->insert(tr->begin(), unique_ptr<Regional>(new Regional(a.train_number)));
    }else if(a.train_type == Train::HighSpeed){
        tr->insert(tr->begin(), unique_ptr<HighSpeed>(new HighSpeed(a.train_number)));
    }else if(a.train_type == Train::SuperHighSpeed){
        tr->insert(tr->begin(), unique_ptr<SuperHighSpeed>(new SuperHighSpeed(a.train_number)));
    }
}