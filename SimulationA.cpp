//Author: Angelo Turris

#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std;

void Simulation::step()
{
    for(vector<unique_ptr<Train>> &trainsVec : trains)
    {
        for(unique_ptr<Train> &t : trainsVec)
        {
            t->step();
        }
    }
}

bool Simulation::slowing_down_trains(int k, int tr_index) const{
    int prev_index = prev_train_index(k, tr_index);
    if(prev_index != -1 && trains[k][tr_index]->get_distance() - 10 == trains[k][prev_index]->get_distance()){
        return true;
    } 
    return false;
}

//mette il treno nel parcheggio della stazione
void Simulation::park_train(Station& st, Train* tr)
{
    st.add_train_to_park(tr);
    tr->park(st.get_distance() - 5);
    cout << "Il treno numero " << tr->get_number() << " e' entrato nel parcheggio della\n" << st << endl;
    cout << *tr << endl;
}
        
void Simulation::leave_park(Station& st, Train* tr)
{
    st.remove_train_from_park(tr);
    tr->set_speed(80);
    cout << "Il treno numero " << tr->get_number() << " e' uscito dal parcheggio della\n" << st << endl;
    cout << *tr << endl;
}

//rimuove un treno dal parcheggio della stazione

void Simulation::add_train_transit(Station& st, Train* tr)
{
    st.add_train_to_transit(tr);
    cout << "Il treno numero " << tr->get_number() << " sta transitando nella\n" << st << endl;
    cout << *tr << endl;
}
        
//toglie il treno dal binario di transito
void Simulation::remove_train_transit(Station& st, Train* tr)
{
    st.remove_train_from_transit();
    cout << "Il treno numero " << tr->get_number() << " e' uscito dal binario di transito della\n" << st << endl;
    cout << *tr << endl;
}

//mette il treno nella banchina libera
void Simulation::entering_station_area(Station& st, Train* tr)
{
    st.add_train_to_stop(tr);
    if(tr->prev_distance() < st.get_distance() - 3.666666)
    {
        tr->set_distance(st.get_distance() - 5);
        tr->set_speed(80);
    }else
    {
        tr->set_distance(st.get_distance() - 6.333333);
        tr->set_speed(80);
    }
    
    cout << "Il treno numero " << tr->get_number() << " e' entrato nell'area della\n" << st << endl;
    cout << *tr << endl;
}

//toglie il treno dalla banchina
void Simulation::exiting_station_area(Station& st, Train* tr)
{
    st.remove_train_to_stop(tr);
    tr->set_speed(1000);
    cout << "Il treno numero " << tr->get_number() << " sta uscendo dall'area della\n" << st << endl;
    cout << *tr << endl;
}