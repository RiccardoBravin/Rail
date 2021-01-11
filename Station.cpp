//Author: Angelo Turris

#include "Station.h"
#include <iostream>
#include <vector>
#include <string>
#include "Train.h"
#include <algorithm>

using namespace std;

//*** Station ***//

string Station::get_name() const{ return name;}

double Station::get_distance() const{ return distance;}

void Station::add_train_to_park(Train* t)
{

    parking.push_back(t); 
}

vector<Train*> Station::get_parking_train() const
{
    return parking; 
}

int Station::get_count_parking_train() const
{
    return parking.size();
}

bool Station::train_in_park(Train* t) const
{
    auto iter = find(parking.begin(), parking.end(), t);
    if(iter != parking.end())
        return true;
    else
        return false;
}

void Station::remove_train_from_park(Train* t)
{
     parking.erase(find(parking.begin(), parking.end(), t));
}

vector<Train*> Station::get_stop_train() const
{
    return stop_tracks;
}

int Station::get_stop_tracks() const
{
    return N_STOP_TRACK;
}

bool Station::add_train_to_stop(Train* t)
{   
    if(can_add_train_to_stop())
    {   
        vector<Train*>::iterator iter = find(stop_tracks.begin(), stop_tracks.end(), nullptr);
        stop_tracks.insert(iter,t); 
        return 1;
    }
    else{
        return 0;
    }
    
}

int Station::what_platform_train(Train* t)
{
    vector<Train*>::iterator iter = find(stop_tracks.begin(), stop_tracks.end(), t);
    if(iter == stop_tracks.end()) 
    {
        return 0;
    }
    int index = std::distance(stop_tracks.begin(), iter );
    return index+1;
    
}

bool Station::remove_train_to_stop(Train* t)
{
    vector<Train*>::iterator iter = find(stop_tracks.begin(), stop_tracks.end(), t);
    if(iter == stop_tracks.end()) 
    {
        //cout << "Non riesco a rimuovere" << endl;
        return false;

    }
    //cout << "riesco a rimuovere" << endl;
    int index = std::distance(stop_tracks.begin(), iter );
    stop_tracks[index] = nullptr; 
    return true;
    
}

int Station::get_count_in_stop_train() const
{
    int count = 0;
    for(int i =0; i < stop_tracks.size();  i++)
    {
        if(stop_tracks[i] != nullptr)
            count++;
    }
    return count;
}


bool Station::can_add_train_to_stop() const
{
    if(get_count_in_stop_train() < N_STOP_TRACK)
        return true;
    else
        return false;
}


//*** Secondary ***//
Secondary::Secondary(const string _name, const double _distance)
{
    name = _name;
    distance = _distance;
}

Secondary::Secondary(const Secondary& stn)
{
    name = stn.name;
    distance = stn. distance;    
}

Secondary& Secondary::operator=(const Secondary& stn)
{
    if(this == &stn)
        return *this;
    name = stn.name;
    distance = stn. distance;
    return *this;
}

Secondary::Secondary(Secondary&& stn)
{
    if(this == &stn)
        return;
    name = stn.name;
    distance = stn. distance;
}

Secondary& Secondary::operator=(Secondary&& stn)
{
    if(this == &stn)
        return *this;
    name = stn.name;
    distance = stn. distance;
    return *this;
}

int Secondary::get_type() const{ return Station::Secondary;}

int Secondary::get_transit_tracks() const
{
    return N_TRANS_TRACK;
}

bool Secondary::can_add_train_to_transit() const
{
    if(get_count_in_transit_train() < N_TRANS_TRACK)
        return true;
    else
        return false;
}

void Secondary::add_train_to_transit(Train* t)
{
    if(can_add_train_to_transit())
        transit_tracks.push_back(t);         
}

int Secondary::get_count_in_transit_train() const
{
   return transit_tracks.size();
}

void Secondary::remove_train_from_transit()
{
        if(!transit_tracks.empty())
            transit_tracks.pop_back();
    else
        cout << "Empty" << endl;  
}


//*** Principal ***//

Principal::Principal(const string _name, const double _distance)
{
    name = _name;
    distance = _distance;
}
    

Principal::Principal(const Principal& stn)
{
    name = stn.name;
    distance = stn. distance;
}

Principal& Principal::operator=(const Principal& stn)
{
    if(this == &stn) return *this;
    name = stn.name;
    distance = stn. distance;
    return *this;
}

Principal::Principal(Principal&& stn)
{
    if(this == &stn) return;
    name = stn.name;
    distance = stn. distance;

    stn.name = "";
    stn.distance = 0;
}

Principal& Principal::operator=(Principal&& stn)
{
    if(this == &stn)
        return *this;
    name = stn.name;
    distance = stn. distance;

    stn.name = "";
    stn.distance = 0;
    return *this;
}

int Principal::get_type() const{ return Station::Principal;}

int Principal::get_transit_tracks() const
{
    return N_TRANS_TRACK;
}

bool Principal::can_add_train_to_transit() const
{
        return false;
}

void Principal::add_train_to_transit(Train* t)
{
    if(can_add_train_to_transit())
        transit_tracks.push_back(t);         
}

int Principal::get_count_in_transit_train() const
{
   return transit_tracks.size();
}

void Principal::remove_train_from_transit()
{
    if(!transit_tracks.empty())
        transit_tracks.pop_back();  
}

//*** Operator << ***//
std::ostream& operator<<(std::ostream& os, const Station& stn)
{
    os << "Stazione ";
    if(stn.get_type() == Station::Principal)
    {
        os << "Principale";
    }
    else if(stn.get_type() == Station::Secondary)
    {
        os << "Locale";
    }
    os << " di: " << stn.get_name();
    os << " distanza: " << stn.get_distance() << " km " << endl;
    os << "ci sono: " << stn.get_count_parking_train() << " treni in sosta nel parcheggio " << endl;
    os << "ci sono: " << stn.get_count_in_stop_train() << " binari su 2 occupati " << endl;
    if(stn.get_type() == Station::Secondary)
    {
        os << "ci sono: " << stn.get_count_in_transit_train() << " in transito " << endl;
    }

    return os;
}

//** Operator == **//

bool operator== (const Station &stn1, const Station &stn2)
{
    return(stn1.get_type() == stn2.get_type() &&
        stn1.get_count_parking_train() == stn2.get_count_parking_train() &&
        stn1.get_count_in_stop_train() == stn2.get_count_in_stop_train());
}

//** Operator != **//
bool operator!= (const Station &stn1, const Station &stn2)
{
    return !(stn1 == stn2);
};