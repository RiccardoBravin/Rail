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

void Station::add_train_to_park(Train t)
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

void Station::add_train_to_stop(Train t )
{   
    stop_tracks.push_back(t);
}

void Station::remove_train_to_stop()
{
    stop_tracks.pop_back();
}

int Station::get_stop_tracks() const
{
    return N_STOP_TRACK;
}


//*** Secondary ***//
Secondary::Secondary(string _name, const int _distance) :
    name{_name}, distance{_distance} {}

int Secondary::get_station_type() const{ return Station::Secondary;}


void Secondary::add_train_to_transit(Train t)
{
    transit_tracks.push_back(t); 
}

void Secondary::remove_train_to_transit()
{
    transit_tracks.pop_back();
}

int Secondary::get_stop_tracks() const
{
    return N_STOP_TRACK;
}

int Secondary::get_transit_tracks() const
{
    return N_TRANS_TRACK;
}


//*** Principal ***//

Principal::Principal(string _name, const int _distance) :
    name{_name}, distance{_distance} {}


int Principal::get_station_type() const{ return Station::Principal;}

void Principal::add_train_to_park(Train t)
{
    parking.push_back(t);
}

vector<Train> Principal::get_parking_train() const
{
    return parking;  
}

int Principal::get_count_parking_train() const
{
    return parking.size();
}

void Principal::remove_train_from_park()
{
    parking.pop_back();
}

void Principal::add_train_to_transit(Train t)
{
    stop_tracks.push_back(t);  // Lo sovrascrivo cosi? non ha treni in transito
}

void Principal::add_train_to_stop(Train t )
{   
    stop_tracks.push_back(t);
}

void Principal::remove_train_to_transit()
{
    transit_tracks.pop_back();
}

void Principal::remove_train_to_stop()
{
    stop_tracks.pop_back();
}

int Principal::get_stop_tracks() const
{
    return N_STOP_TRACK;
}