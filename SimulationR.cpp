/**
 * @file SimulationR.cpp
 * @author Bravin Riccardo
 * @brief manages part of the simulation functions
 * @version 0.1
 * @date 2021-01-12
 * 
 * @copyright Copyright (c) 2021
 */

#include "Simulation.h"
#include "utility.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <exception>


using namespace std;



void Simulation::simulate(){
    while(!end_simulation()){
        cout << "~~~~~~      " << mtoh(current_time) << "      ~~~~~~\n";
        
        //cout << 1 << endl;
        notice_20_km_mark();
        cout << endl;

        //cout << 2 << endl;
        start_trains();
        
        //cout << 3 << endl;
        exit_station();
        
        //cout << 4 << endl;
        in_station();
        //cout << 5 << endl;
        sort_trains();
        
        //cout << 6 << endl;
        parked_trains();

        //cout << 7 << endl;
        check_distance();
        
        //cout << 8 << endl;
        stop_trains();
        
        //cout << 9 << endl;
        step();

        //cout << 10 << endl;
        ending_station();

        current_time++;
        cout << endl;
    };
    cout << "Simulazione terminata\n";
}





void Simulation::start_trains(){
    for(int k = 0; k < RAILWAYS; k++){
        //partenza dalla prima stazione all'orario prestabilito
        if(free_to_start(&railway[k].get_beginning_station(), k) && railway[k].get_station(0).can_add_train_to_stop()){ 
            
            for(int i = 0; i < timetable[k].get_timetable_size(); i++){
                if(current_time >= timetable[k].get_timetable_element(i).time_at_station[0]){
                    
                    bool found = false;
                    for(int &tr_num : simulated_trains){
                        if(tr_num == timetable[k].get_timetable_element(i).train_number){
                            found = true; 
                            break;
                        }          
                    }
                    if(!found){//se il treno non è gia stato inizzializzato crealo e fallo partire
                        simulated_trains.push_back(timetable[k].get_timetable_element(i).train_number);
                        push_front_train(timetable[k].get_timetable_element(i), &trains[k]);
                        railway[k].get_beginning_station().add_train_to_stop(trains[k][0].get());
                        trains[k][0]->set_speed(80);
                        cout << "Il treno numero " << trains[k][0]->get_number() << " e' in partenza dalla\n" << railway[k].get_station(0) << endl;
                        cout << *trains[k][0] << endl;
                        break;
                    }
                }
            }
        }
        //partenza dalle stazioni intermedie
        
        for(int i = 0; i < railway[k].get_station_count(); i++){
            for(Train* &t : railway[k].get_station(i).get_stop_train()){

                
                if(t!= nullptr && t->can_start() && free_to_start(&railway[k].get_station(i), k) && !t->running() && best_train_in_station(&railway[k].get_station(i), t)){
                    t->set_speed(80);
                    cout << "Il treno numero " << t->get_number() << " e' in partenza dalla\n" << railway[k].get_station(i) << endl;
                    cout << *t << endl;
                    break;
                }
            }
            
        }
        
    }
}

 
bool Simulation::best_train_in_station(Station* st, Train* t) const{
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


bool Simulation::free_to_start(Station* st,  int k) const{
     
    for(int i = 0; i < trains[k].size(); i++){
        if(!trains[k][i]->stationary() && !trains[k][i]->parked())
            if(st->get_distance() < trains[k][i]->get_distance() && st->get_distance() + 10 > trains[k][i]->get_distance()){
                return false;
            }
            if(st->get_type() == Station::Secondary){
                if(trains[k][i]->get_type() == Train::SuperHighSpeed){
                    if(st->get_distance() - 25 > trains[k][i]->get_distance() && st->get_distance() - 3 > trains[k][i]->get_distance())
                        return false;
                }else if(trains[k][i]->get_type() == Train::HighSpeed){
                    if(st->get_distance() - 21 > trains[k][i]->get_distance() && st->get_distance() > trains[k][i]->get_distance())
                        return false;
                }
            }
    }

    
    return true;
}



void Simulation::exit_station(){//se un treno sta uscendo dalla stazione allora va alla velocità massima
    for(int k = 0; k < RAILWAYS; k++){
        
        for(int i = 0; i < railway[k].get_station_count(); i++){ //cicla sulla dimensione della railway
            
            for(int j = 0; j < trains[k].size(); j++){
                if(trains[k][j]->prev_distance() < railway[k].get_station(i).get_distance() + 5 && trains[k][j]->get_distance() >= railway[k].get_station(i).get_distance() + 5){
                    if(railway[k].get_station(i).what_platform_train(trains[k][j].get()) != 0){ //se il treno è alla fine della stazione allora lo rimuovo
                        exiting_station_area(railway[k].get_station(i), trains[k][j].get());
                        
                    }else{//altrimenti è nel transito e quindi lo rimuovo da li
                        remove_train_transit(railway[k].get_station(i), trains[k][j].get());
                    }

                }
            }
        }
    }
}


//una volta fatta la funzione addtraintopark di simulation posso sostiuire un bel po di codice
void Simulation::in_station(){
    for(int k = 0; k < RAILWAYS; k++){
        for(int i = 0; i < trains[k].size(); i++){//per ogni treno
            for(int j = 0; j < railway[k].get_station_count(); j++){ //per ogni stazione
                
                if(trains[k][i]->prev_distance() < railway[k].get_station(j).get_distance() - 5 && trains[k][i]->get_distance() >= railway[k].get_station(j).get_distance() - 5 && !trains[k][i]->parked()){   
                    
                    if(railway[k].get_station(j).get_type() == Station::Principal){ //se la stazione è una principale
                        int delay = calc_delay(k, i, j);
                        trains[k][i]->set_delay(delay);
                        if(delay < 0 ){ // e sei in anticipo vai nel parcheggio (con questo treno poi hai finito)
                            
                            park_train(railway[k].get_station(j), trains[k][i].get());
                            
                            break;

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 1){ //se non sei in anticipo e hai solo una banchina libera
                            
                            if(trains[k][i]->get_type() == Train::Regional || trains[k][i]->get_type() == Train::HighSpeed){ //se il treno è reg o hs e sta rallentando un treno 
                                int prev_index = prev_train_index(k, i);
                                if(prev_index != -1 && slowing_down_trains(k, i)){
                                    park_train(railway[k].get_station(j), trains[k][i].get());

                                }else{//altrinmenti prosegue alla banchina
                                    entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                    
                                }
                                
                            }else if(trains[k][i]->get_type() == Train::SuperHighSpeed){
                                entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                
                            }

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 2){ //se non sei in ancicipo e hai almeno due banchine libere
                            
                            if(trains[k][i]->get_type() == Train::Regional){ //se il treno è regionale e sta rallentando un treno che ne rallenta un altro
                                int prev_index = prev_train_index(k, i);
                                if(prev_index != -1 && slowing_down_trains(k, i) && slowing_down_trains(k, prev_index)){//DA FIXARRRRRREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
                                    park_train(railway[k].get_station(j), trains[k][i].get());
                                    
                                }else{
                                    entering_station_area(railway[k].get_station(j), trains[k][i].get());
                            
                                }

                            }else{
                                entering_station_area(railway[k].get_station(j), trains[k][i].get());

                            }

                        }else{//se non ci sono banchine parcheggia sennò entra
                            
                            if(railway[k].get_station(j).can_add_train_to_stop()){
                                entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                
                            }else{
                                park_train(railway[k].get_station(j), trains[k][i].get());
                                
                            }

                        }

                    }else if(railway[k].get_station(j).get_type() == Station::Secondary){
                        
                        if(trains[k][i]->get_type() == Train::Regional){
                            int delay = calc_delay(k, i, j);
                            trains[k][i]->set_delay(delay);
                            if(delay < 0){
                                park_train(railway[k].get_station(j), trains[k][i].get());
                            }else if(railway[k].get_station(j).can_add_train_to_stop()){
                                entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                
                            }else{
                                park_train(railway[k].get_station(j), trains[k][i].get());
                                
                            }

                        }else if(trains[k][i]->get_type() == Train::HighSpeed){
                            if(railway[k].get_station(j).can_add_train_to_transit()){
                                
                                if(smart_train_function(k, i, j)){
                                    add_train_transit(railway[k].get_station(j), trains[k][i].get());
                                }else{
                                    park_train(railway[k].get_station(j), trains[k][i].get());

                                }
                                    
                                
                            }else{
                                park_train(railway[k].get_station(j), trains[k][i].get());

                            }

                        }else if(trains[k][i]->get_type() == Train::SuperHighSpeed){
                            if(railway[k].get_station(j).can_add_train_to_transit()){
                                add_train_transit(railway[k].get_station(j), trains[k][i].get());
                            }else{
                                park_train(railway[k].get_station(j), trains[k][i].get());
                            }
                            
                        }

                    }

                }
                
            }
        }
    }
}


//se è in anticipo calcola l'anticipo metti nel parcheggio
//se la stazione è principale e il treno che sto guardando ha un treno in culo mettilo se c'è solo una banchina libera
//mettilo nel parcheggio altrimenti se è un regionale con due treni in culo mettilo nel parcheggio, altrimenti metti in una banchina
//se la stazione è secondaria e il treno in analisi è Regionale se ho almeno una banchina libera va altrimenti nel parcheggio,
//se il treno è un hs che ha un shs dietro e c'è solo una banchina libera allora decidi con la funzione se parcheggiarlo o farlo andare
//in tutti gli altri casi fai passare il treno



int Simulation::calc_delay(int k, int tr_index, int st_index) const{
    int time_of_arrival {0};
    if(trains[k][tr_index]->get_type() == Train::Regional)
        time_of_arrival = timetable[k].search_timetable_element(trains[k][tr_index]->get_number()).time_at_station[st_index];
    else
        time_of_arrival = timetable[k].search_timetable_element(trains[k][tr_index]->get_number()).time_at_station[railway[k].principal_index(st_index)];
    //occhio almeno uno qui sopra che elia dobrebbe averlo corretto
    return current_time - time_of_arrival + 3;
}

void Simulation::check_distance(){
    for(int k = 0; k < RAILWAYS; k++){

        //se il treno è lungo una tratta allora deve andare alla velocità massima
        for(int i = trains[k].size() - 1; i >= 0; i--){
            bool found {false};
            for(int j = 0; j < railway[k].get_station_count(); j++){
                if(railway[k].get_station(j).what_platform_train(trains[k][i].get()) != 0 || railway[k].get_station(j).train_in_park(trains[k][i].get())){
                    found = true;
                    break;
                }
            }

            if(!found){
                trains[k][i]->set_speed(1000);
                
                int prev_index = prev_train_index(k, i);
                if(prev_index != -1){
                    if(trains[k][prev_index]->get_distance() >= trains[k][i]->get_distance() - 10){
                        trains[k][prev_index]->set_distance(trains[k][i]->get_distance() - 10);
                        trains[k][prev_index]->set_speed(trains[k][i]->get_speed());
                        cout << "E' in corso un rallentamento causato da" <<  endl << *trains[k][i] << endl << *trains[k][prev_index] << endl;
                    }
                }
            }
        }

    }
}




int Simulation::prev_train_index(int k, int tr_index) const{
    for(int i = tr_index - 1; i >= 0; i--){
        bool found {false};
            for(int j = 0; j < railway[k].get_station_count(); j++){
                if(railway[k].get_station(j).what_platform_train(trains[k][i].get()) != 0 || trains[k][i]->parked()){
                    found = true;
                    break;
                }
            }
        if(!found){
            return i;
        }
    }
    return -1;
} 



bool Simulation::smart_train_function(int k, int tr_index, int st_index) const{
    int prev_index = prev_train_index(k, tr_index);
    
    if(prev_index == -1)
        return true;
    Train* tr = trains[k][tr_index].get();
    Train* prev = trains[k][prev_index].get();

    if(st_index != 0 && prev->get_distance() > railway[k].get_station(st_index - 1).get_distance() + 5 && prev->get_distance() > railway[k].get_station(st_index ).get_distance() - 5){
    
        if(prev->get_type() <= tr->get_type()){
            return true;
        }else{
            if(st_index != railway[k].get_station_count() - 1){
                int next_length = railway[k].get_station(st_index).get_distance() - railway[k].get_station(st_index + 1).get_distance();
                if(tr->get_delay() + (tr->get_distance() - prev->get_distance()) / prev->get_speed() > next_length / prev->get_speed() - next_length / tr->get_speed() + prev->get_delay()){
                    return true;
                }else{
                    return false;
                }
            }
        }
            
    }
    return false;
}

//se il ritardo di a + (a.pos - b.pos)/b.vel > (next_station.lenght/b.vel)-(next_station.lenght/a.vel)+ ritardo di b
//allora fai procedere a altrimenti metti a nel parcheggio


void Simulation::parked_trains(){
    for(int k = 0; k < RAILWAYS; k++){
        for(int j = 0; j < railway[k].get_station_count(); j++){
            
            if(railway[k].get_station(j).get_count_parking_train() != 0){
        
                //se la stazione è principale allora tutti i treni potendo andranno sulla banchina
                if(railway[k].get_station(j).get_type() == Station::Principal){
                    int best_train_index = best_train_in_park(k, j);
                    

                    //se il ritardo è negativo o le banchine sono piene non faccio nulla
                    if(railway[k].get_station(j).can_add_train_to_stop() && trains[k][best_train_index]->get_delay() >= 0 ){
                        //se hai una sola banchina libera allora controlla di non avere treni in arrivo 
                        if(railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 1){ //se hai una sola banchina libera

                            if(smart_train_function(k, best_train_index, j)){
                                leave_park(railway[k].get_station(j), trains[k][best_train_index].get());
                                entering_station_area(railway[k].get_station(j), trains[k][best_train_index].get());
                            }//altrimenti il treno rimane nel parcheggio
                        //se ho due banchine libere il treno di tier piu alto può entrare in stazione
                        }else if(railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 2){//se hai due banchine libere
                            leave_park(railway[k].get_station(j), trains[k][best_train_index].get());
                            entering_station_area(railway[k].get_station(j), trains[k][best_train_index].get());
                        }
                    }
                //se la stazione è secondaria allora devo effettuare controlli sul tipo di treno
                }else if(railway[k].get_station(j).get_type() == Station::Secondary){//nelle stazioni secondarie devo diversificare a seconda del tipo di treno
                    //se posso aggiungere un treno alla banchina ne cerco uno che ci possa andare e lo mando 
                    if(railway[k].get_station(j).can_add_train_to_stop()){
                        int best_regional_index = best_regional_in_park(k, j);
                        if(best_regional_index != -1 && trains[k][best_regional_index]->get_delay() >= 0){
                            leave_park(railway[k].get_station(j), trains[k][best_regional_index].get());
                            entering_station_area(railway[k].get_station(j), trains[k][best_regional_index].get());
                        }
                    }
                    int best_train_index = best_train_in_park(k, j);
                    //se il treno non è un regionale devo metterlo nel binario di transito
                    if(best_train_index != -1 && trains[k][best_train_index]->get_type() != Train::Regional){
                        if(railway[k].get_station(j).can_add_train_to_transit()){
                            if(true /*funzione magica che decide chi passa prima dice che posso andare*/){
                                leave_park(railway[k].get_station(j), trains[k][best_train_index].get());
                                trains[k][best_train_index]->set_speed(1000);
                                add_train_transit(railway[k].get_station(j), trains[k][best_train_index].get());
                            }
                        }

                    }

                }
            }
        }
    }
}
        //se ho esattamente una banchina libera prendo il treno con il maggior ritardo e di tier piu alto e se la funzione magica dice 
        //che può passare entra nella banchina altrimenti stanno tutti li. se hai due banchine libere manda il treno più "figo"

int Simulation::best_train_in_park(int k, int st_index) const{//ritorna il miglior treno per quella stazione
    
    vector<Train*> aux = railway[k].get_station(st_index).get_parking_train();
    
    Train* tr = {nullptr};
    
    for(int i = 0; i < aux.size(); i++){
        if(tr == nullptr){
            tr = aux[i];
        }else if(aux[i]->get_type() > tr->get_type()){
            tr = aux[i];
        }else if(aux[i]->get_type() == tr->get_type() && aux[i]->get_delay() > tr->get_delay()){
            tr = aux[i];
        }
    }

    for(int i = 0; i < trains[k].size(); i++){
        if(trains[k][i].get() == tr)
            return i;
    }
    
    return -1;
}

int Simulation::best_regional_in_park(int k , int st_index) const{
    vector<Train*> aux = railway[k].get_station(st_index).get_parking_train();

    Train* tr {nullptr};
    
    for(int i = 0; i < aux.size(); i++){
        if(tr == nullptr){
            if(aux[i]->get_type() == Train::Regional)
                tr = aux[i];
        }else if(aux[i]->get_type() == tr->get_type() && aux[i]->get_delay() > tr->get_delay()){
            tr = aux[i];
        }
    }

    if(tr ==  nullptr){
        return -1;
    }

    for(int i = 0; i < trains[k].size(); i++){
        if(trains[k][i].get() == tr)
            return i;
    }

    return -1;
}


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