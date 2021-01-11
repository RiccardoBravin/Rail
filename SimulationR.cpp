#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <exception>


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
    for(int i=0; i<railway.size(); i++)  cout << railway[i] << endl << *railway[i].get_timetable_reference() << endl << endl;
    
    
        RAILWAYS = railway.size();
    
    for(int i = 0; i < railway.size(); i++){
        trains.push_back(std::vector<std::unique_ptr<Train>> ());
    }

    
    
}

void Simulation::simulate(){
    while(current_time < 100){
        cout << "~~~~~~      " << current_time << "      ~~~~~~\n";
        
        start_trains();
        
        exit_station();
        
        in_station();
        sort_trains();
        
        parked_trains();

        check_distance();
        
        stop_trains();
        
        step();

        //cout << railway[0];

        current_time++;
        cout << endl;
    };

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
        //partenza dalla prima stazione all'orario prestabilito
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
                        cout << "Il treno numero " << trains[k][0]->get_number() << " e' in partenza dalla\n" << railway[k].get_station(0) << endl;
                        cout << *trains[k][0] << endl;
                        break;
                    }
                }
            }
        }
        //partenza dalle stazioni intermedie
        for(int i = 0; i < railway[k].get_station_count(); i++){
            for(unique_ptr<Train> &t : trains[k]){
                if(t->can_start() && free_to_start(&railway[k].get_station(i), k) && !t->running() && !t->parked() && best_train_in_station(&railway[k].get_station(i), t.get())){
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
        if(!trains[trains_index][i]->stationary() && !trains[trains_index][i]->parked())
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
                    //cout << endl << "controllo treno in entrata"<<*trains[k][i]<< endl;
                    
                    if(railway[k].get_station(j).get_type() == Station::Principal){ //se la stazione è una principale
                        int delay = calc_delay(k, i, j);
                        trains[k][i]->set_delay(delay);
                        if(delay < 0 ){ // e sei in anticipo vai nel parcheggio (con questo treno poi hai finito)
                            
                            park_train(railway[k].get_station(j), trains[k][i].get());
                            
                            break;

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 1){ //se non sei in anticipo e hai solo una banchina libera
                            
                            if(trains[k][i]->get_type() == Train::Regional || trains[k][i]->get_type() == Train::HighSpeed){ //se il treno è reg o hs e sta rallentando un treno 
                                
                                if(false /*treno in culo*/){//va nel parcheggio
                                    park_train(railway[k].get_station(j), trains[k][i].get());

                                }else{//altrinmenti prosegue alla banchina
                                    entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                    
                                }
                                
                            }else if(trains[k][i]->get_type() == Train::SuperHighSpeed){
                                entering_station_area(railway[k].get_station(j), trains[k][i].get());
                                
                            }

                        }else if(delay >= 0 && railway[k].get_station(j).get_count_in_stop_train() == railway[k].get_station(j).get_stop_tracks() - 2){ //se non sei in ancicipo e hai almeno due banchine libere
                            
                            if(trains[k][i]->get_type() == Train::Regional){ //se il treno è regionale e sta rallentando un treno che ne rallenta un altro
                                
                                if(false/*treno in culo con treno in culo*/){//DA FIXARRRRRREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
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
                                
                                if(false /*treno in culo */){
                                    if(true/*e funzione magica che decide chi passa prima dice che posso andare*/){
                                        add_train_transit(railway[k].get_station(j), trains[k][i].get());

                                    }else{
                                        park_train(railway[k].get_station(j), trains[k][i].get());

                                    }
                                }else{
                                    add_train_transit(railway[k].get_station(j), trains[k][i].get());
                                    
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



int Simulation::calc_delay(int k, int tr_index, int st_index){
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


int Simulation::prev_train_index(int k, int tr_index){
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

bool Simulation::smart_train_function(int k, int tr_index, int st_index){
    int prev_train = prev_train_index(k, tr_index);
    if(prev_train == -1)
        return true;
    if(st_index != 0 && trains[k][prev_train]->get_distance() /*il treno che mi sta dietro è nella stessa tratta in cui sono io*/){

    }

}


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

                            if(true/*ho un treno in culo e funzione magica che decide chi passa prima dice che posso andare*/){
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

int Simulation::best_train_in_park(int k, int st_index){//ritorna il miglior treno per quella stazione
    
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

int Simulation::best_regional_in_park(int k , int st_index){
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


//mette il treno nel parcheggio della stazione
void Simulation::park_train(Station& st, Train* tr){
    st.add_train_to_park(tr);
    tr->park(st.get_distance() - 5);
    cout << "Il treno numero " << tr->get_number() << " e' entrato nel parcheggio della\n" << st << endl;
    cout << *tr << endl;
}
        
void Simulation::leave_park(Station& st, Train* tr){
    st.remove_train_from_park(tr);
    tr->set_speed(80);
    cout << "Il treno numero " << tr->get_number() << " e' uscito dal parcheggio della\n" << st << endl;
    cout << *tr << endl;
}

//rimuove un treno dal parcheggio della stazione

void Simulation::add_train_transit(Station& st, Train* tr){
    st.add_train_to_transit(tr);
    cout << "Il treno numero " << tr->get_number() << " sta transitando nella\n" << st << endl;
    cout << *tr << endl;
}
        
//toglie il treno dal binario di transito
void Simulation::remove_train_transit(Station& st, Train* tr){
    st.remove_train_from_transit();
    cout << "Il treno numero " << tr->get_number() << " e' uscito dal binario di transito della\n" << st << endl;
    cout << *tr << endl;
}
//mette il treno nella banchina libera
void Simulation::entering_station_area(Station& st, Train* tr){
    st.add_train_to_stop(tr);
    if(tr->prev_distance() < st.get_distance() - 3.666666){
        tr->set_distance(st.get_distance() - 5);
        tr->set_speed(80);
    }else{
        tr->set_distance(st.get_distance() - 6.333333);
        tr->set_speed(80);
    }
    
    cout << "Il treno numero " << tr->get_number() << " e' entrato nell'area della\n" << st << endl;
    cout << *tr << endl;
}
//toglie il treno dalla banchina
void Simulation::exiting_station_area(Station& st, Train* tr){
    st.remove_train_to_stop(tr);
    tr->set_speed(1000);
    cout << "Il treno numero " << tr->get_number() << " sta uscendo dall'area della\n" << st << endl;
    cout << *tr << endl;
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