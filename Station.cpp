//Author: Angelo Turris

#include "Station.h"
#include <iostream>
#include <vector>
#include <string>
#include "Train.h"

using namespace std;

//*** Station ***//

string Station::get_station_name() const{ return name;}

int Station::get_station_distance() const{ return distance;}

void Station::add_train_to_park(Train& t)
{
    parking.push_back(t);
}

vector<Train> Station::get_parking_train() const
{
    return parking; 
}

int Station::get_count_parking_train() const
{
    return parking.size();
}

void Station::remove_train_from_park()
{
    parking.pop_back();
}

void Station::add_train_to_stop(Train& t )
{   
    stop_tracks.push_back(t);
}

void Station::remove_train_to_stop()
{
    stop_tracks.pop_back();
}


//*** Secondary ***//
Secondary::Secondary(const string _name, const int _distance)
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
    if(this == &stn) return *this;
    name = stn.name;
    distance = stn. distance;
    return *this;
}

Secondary::Secondary(Secondary&& stn)
{
    if(this == &stn) return;
    name = stn.name;
    distance = stn. distance;
}

Secondary& Secondary::operator=(Secondary&& stn)
{
    if(this == &stn) return;
    name = stn.name;
    distance = stn. distance;
    return *this;
}

int Secondary::get_station_type() const{ return Station::Secondary;}


void Secondary::add_train_to_transit(Train& t)
{
    transit_tracks.push_back(t); 
}

void Secondary::remove_train_to_transit()
{
    transit_tracks.pop_back();
}

int Secondary::get_transit_tracks() const
{
    return N_TRANS_TRACK;
}


//*** Principal ***//

Principal::Principal(const string _name, const int _distance)
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
    if(this == &stn) return;
    name = stn.name;
    distance = stn. distance;

    stn.name = "";
    stn.distance = 0;
    return *this;
}


int Principal::get_station_type() const{ return Station::Principal;}

int Principal::get_stop_tracks() const
{
    return N_STOP_TRACK;
}


//*** Operator << ***//
std::ostream& operator<<(std::ostream& os, const Station& stn)
{
    os << "Stazione ";
    if(stn.get_station_type() == 0){
        os << "Principale";
    }
    else if(stn.get_station_type() == 1){
        os << "Locale";
    }
    os << " di: " << stn.get_station_name();
    os << " distanza: " << stn.get_station_distance() << endl;
    os << " ci sono: " << stn.get_count_parking_train() << " treni in sosta " << endl;
}