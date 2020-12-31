//Author: Angelo Turris

#include "Station.h"
#include <iostream>
#include <vector>
#include <string>
#include "Train.h"

using namespace std;

Secondary::Secondary(string _name, const int _distance) :
    name{_name}, distance{_distance} {}

string Secondary::get_station_name() const{ return name;}

int Secondary::get_station_distance() const{ return distance;}

int Secondary::get_station_type() const{ return Secondary::Secondary;}

void Secondary::add_train_to_park(Train t)
{
    parking.push_back(t);
}

vector<Train> Secondary::get_parking_train() const
{
    return parking; //ha senso? 
}

int Secondary::get_count_parking_train() const
{
    return parking.size();
}

void Secondary::remove_train_from_park()
{
    parking.pop_back();
}

void Secondary::add_train_to_transit(Train t)
{
    transit_tracks.push_back(t); 
}

void Secondary::add_train_to_stop(Train t )
{   
    stop_tracks.push_back(t);
}

void Secondary::remove_train_to_transit()
{
    transit_tracks.pop_back();
}

void Secondary::remove_train_to_stop()
{
    stop_tracks.pop_back();
}

int Secondary::get_transit_tracks() const
{
    return N_TRANS_TRACK;
}

int Secondary::get_stop_tracks() const
{
    return N_STOP_TRACK;
}