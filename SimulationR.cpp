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
    while(current_time < 300){
        cout << "~~~~~~      " << current_time << "      ~~~~~~\n";
        start_trains();
        exit_station();
        in_station();

        stop_trains();
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
                        cout << *trains[k][0] << endl;
                        break;
                    }
                }
            }
        }

        for(int i = 0; i < railway[k].get_station_count(); i++){
            for(unique_ptr<Train> &t : trains[k]){
                if(t->can_start() && free_to_start(&railway[k].get_station(i), k) && !t->running() && best_train_in_station(&railway[k].get_station(i), t.get())){ //&& best_train_in_station(&railway[k].get_station(i), &t)
                    t->set_speed(80);
                    cout << "Il treno numero " << t->get_number() << " e' in partenza dalla\n" << railway[k].get_station(i) << endl;
                    cout << *t << endl;
                    break;
                }

            }
        }
        
    }
}

 
bool Simulation::best_train_in_station(Station* st, Train* t){
    if(st->get_count_in_stop_train() == 1)
        return true;

    int tr_index = st->what_platform_train(t) - 1;

    if(tr_index == -1)
        return false;

    for(int i = 0; i < st->get_stop_train().size(); i++){
        if(st->get_stop_train()[i]->get_type() > st->get_stop_train()[tr_index]->get_type())
            return false;
        if(st->get_stop_train()[i]->get_type() == st->get_stop_train()[tr_index]->get_type() && st->get_stop_train()[i]->get_delay() > st->get_stop_train()[tr_index]->get_delay())
            return false;
    }

    return true;
}


bool Simulation::free_to_start(Station* st,  int trains_index) const{  //non MANCA IL CONTROLLO A SECONDA DELLA STAZIONE PER VERIFICARE CHE IL BINARIO DI TRANSITO SIA LIBBERO
     
    for(int i = 0; i < trains[trains_index].size(); i++){
        if(!trains[trains_index][i]->stationary())
            if(st->get_distance() < trains[trains_index][i]->get_distance() && st->get_distance() + 10 > trains[trains_index][i]->get_distance()){
                return false;
            }
            if(st->get_type() == Station::Secondary){
                if(trains[trains_index][i]->get_type() == Train::SuperHighSpeed){
                    if(st->get_distance() - 25 > trains[trains_index][i]->get_distance() && st->get_distance() - 3 > trains[trains_index][i]->get_distance())
                        return false;
                }else if(trains[trains_index][i]->get_type() == Train::HighSpeed){
                    if(st->get_distance() - 21 > trains[trains_index][i]->get_distance() && st->get_distance() > trains[trains_index][i]->get_distance())
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
                if(trains[k][j]->prev_distance() < railway[k].get_station(i).get_distance() + 5 && trains[k][j]->get_distance() >= railway[k].get_station(i).get_distance() + 5){
                    if(railway[k].get_station(i).remove_train_to_stop(trains[k][j].get())){
                        trains[k][j]->set_speed(300);
                        cout << "Il treno numero " << trains[k][j]->get_number() << " e' uscito dalla\n" << railway[k].get_station(i) << endl;
                        cout << *trains[k][j] << endl;
                    }else{
                        //railway[k].get_station(i).remove_train_to_transit(trains[k][i].get())
                    }

                }
            }
        }
    }
}


void Simulation::in_station(){
    for(int k = 0; k < RAILWAYS; k++){
        for(int i = 0; i < trains[k].size(); i++){//per ogni treno
            for(int j = 0; j < railway[k].get_station_count(); j++){ //per ogni stazione
                if(trains[k][i]->prev_distance() < railway[k].get_station(j).get_distance() - 5 && trains[k][i]->get_distance() >= railway[k].get_station(j).get_distance() - 5)    
                    
                    if(railway[k].get_station(j).get_type() == Station::Principal){ //se la stazione è una principale
                        int delay = calc_delay(k, i, j);

                        if(delay < 0 ){ // e sei in anticipo vai nel parcheggio (con questo treno poi hai finito)
                            railway[k].get_station(j).add_train_to_park(trains[k][i].get());
                            trains[k][i]->park(railway[k].get_station(j).get_distance());
                            cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nel parcheggio della\n" << railway[k].get_station(j) << endl;
                            cout << *trains[k][i] << endl;
                            break;

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 1){ //se non sei in anticipo e hai solo una banchina libera
                            
                            if(trains[k][i]->get_type() == Train::Regional || trains[k][i]->get_type() == Train::HighSpeed){ //se il treno è reg o hs e sta rallentando un treno 
                                if(false /*treno in culo*/){//va nel parcheggio
                                    railway[k].get_station(j).add_train_to_park(trains[k][i].get());
                                    trains[k][i]->park(railway[k].get_station(j).get_distance());
                                    cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nel parcheggio della\n" << railway[k].get_station(j) << endl;
                                    cout << *trains[k][i] << endl;
                                }else{//altrinmenti prosegue alla banchina
                                    railway[k].get_station(j).add_train_to_stop(trains[k][i].get());
                                    trains[k][i]->set_speed(80);
                                    cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nell'area della\n" << railway[k].get_station(j) << endl;
                                    cout << *trains[k][i] << endl;
                                }
                                
                            }else if(trains[k][i]->get_type() == Train::SuperHighSpeed){
                                railway[k].get_station(j).add_train_to_stop(trains[k][i].get());
                                trains[k][i]->set_speed(80);
                                cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nell'area della\n" << railway[k].get_station(j) << endl;
                                cout << *trains[k][i] << endl;
                            }

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 2){ //se non sei in ancicipo e hai almeno due banchine libere
                            if(trains[k][i]->get_type() == Train::Regional){ //se il treno è regionale e sta rallentando un treno che ne rallenta un altro
                                if(false/*treno in culo con treno in culo*/){//DA FIXARRRRRREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                                    railway[k].get_station(j).add_train_to_park(trains[k][i].get());
                                    trains[k][i]->park(railway[k].get_station(j).get_distance());
                                    cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nel parcheggio della\n" << railway[k].get_station(j) << endl;
                                    cout << *trains[k][i] << endl;
                                }else{
                                    railway[k].get_station(j).add_train_to_stop(trains[k][i].get());
                                    trains[k][i]->set_speed(80);
                                    cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nell'area della\n" << railway[k].get_station(j) << endl;
                                    cout << *trains[k][i] << endl;
                                }
                            }else{
                                railway[k].get_station(j).add_train_to_stop(trains[k][i].get());
                                trains[k][i]->set_speed(80);
                                cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nell'area della\n" << railway[k].get_station(j) << endl;
                                cout << *trains[k][i] << endl;
                            }
                        }else{//se non ci sono banchine parhcheggia senno entra
                            if(railway[k].get_station(j).add_train_to_stop(trains[k][i].get())){
                                trains[k][i]->set_speed(80);
                                cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nell'area della\n" << railway[k].get_station(j) << endl;
                                cout << *trains[k][i] << endl;
                            }else{
                                railway[k].get_station(j).add_train_to_park(trains[k][i].get());
                                trains[k][i]->park(railway[k].get_station(j).get_distance());
                                cout << "Il treno numero " << trains[k][i]->get_number() << " e' entrato nel parcheggio della\n" << railway[k].get_station(j) << endl;
                                cout << *trains[k][i] << endl;
                            }
                        }

                    }else if(railway[k].get_station(j).get_type() == Station::Secondary){

                        /*cout << *trains[k][i] << endl;
                        cout << railway[k].get_station(j).get_count_in_stop_train() << endl;
                        
                        trains[k][i]->set_speed(80);
                        railway[k].get_station(j).add_train_to_stop(trains[k][i].get());*/
                    }


                    if(trains[k][i]->get_type() == Train::Regional){

                    }else if(trains[k][i]->get_type() == Train::HighSpeed){

                    }else if(trains[k][i]->get_type() == Train::SuperHighSpeed){

                    }
            
            }


        }


    }
}

int Simulation::calc_delay(int k, int tr_index, int rw_index){
    //timetable[k].search_timetable_element(trains[k][tr_index]->get_number()).time_at_station[];
    return 0;
}


//se è in anticipo calcola l'anticipo metti nel parcheggio
//se la stazione è principale e il treno che sto guardando ha un treno in culo mettilo se c'è solo una banchina libera
//mettilo nel parcheggio altrimenti se è un regionale con due treni in culo mettilo nel parcheggio, altrimenti metti in una banchina
//se la stazione è secondaria e il treno in analisi è Regionale se ho almeno una banchina libera va altrimenti nel parcheggio,
//se il treno non è un hs che ha un shs dietro e c'è solo una banchina libera allora decidi con la funzione se parcheggiarlo o farlo andare
//in tutti gli altri casi fai passare il treno


void Simulation::stop_trains(){
    for(int k = 0; k < RAILWAYS; k++){
        for(int i = 0; i < trains[k].size(); i++){
            for(int j = 0; j < railway[k].get_station_count(); j++){
                if(trains[k][i]->get_type() == Train::Regional){

                    //cout << trains[k][i]->get_distance() << "<" << railway[k].get_station(j).get_distance() <<"&&" << trains[k][i]->next_distance() << ">=" << railway[k].get_station(j).get_distance() << endl;
                    if(trains[k][i]->get_distance() < railway[k].get_station(j).get_distance() && trains[k][i]->next_distance() >= railway[k].get_station(j).get_distance()){    
                        trains[k][i]->stop(railway[k].get_station(j).get_distance());
                        cout << "Il treno numero " << trains[k][i]->get_number() << " e' arrivato alla\n" << railway[k].get_station(j);
                        cout << *trains[k][i] << endl;
                    }
                }else{
                    if(railway[k].get_station(j).get_type() == Station::Principal){
                        if(trains[k][i]->get_distance() < railway[k].get_station(j).get_distance() && trains[k][i]->next_distance() >= railway[k].get_station(j).get_distance()){    
                            trains[k][i]->stop(railway[k].get_station(j).get_distance());
                            cout << "Il treno numero " << trains[k][i]->get_number() << " e' arrivato alla\n" << railway[k].get_station(j);
                            cout << *trains[k][i] << endl;
                        }
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