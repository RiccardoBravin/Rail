//Author: Riccardo Bravin

#include "Train.h"
#include <iostream>
 
using namespace std;

Regional::Regional(const int _number) : 
    number(_number), speed(0), delay(0), distance(0), state(Stationary), state_timer(0)
{
    //intentionally left blank
}

int Regional::get_number() const{   return number;}

int Regional::get_type() const {    return Train::Regional;} 

void Regional::set_delay(const int _delay){ 
    delay =_delay;
}

int Regional::get_delay() const{    return delay;}

void Regional::set_speed(const int _speed){
    speed =_speed;
    station_timer = 0;
}

int Regional::get_speed() const{    return speed;}

void Regional::set_distance(const double _distance){
    distance = _distance;
}

double Regional::get_distance() const{  return distance;}

double Regional::next_distance() const{
    return distance + speed * 0.0166;
}

bool Regional::stationary() const{
    if(state == Stationary && speed == 0)
        return true;
    return false;
}

bool Regional::parked() const{
    if(state == Parked && speed == 0)
        return true;
    return false;
}

bool Regional::running() const{
    if(state == Running && speed != 0)
        return true;
    return false;
}

void Regional::park(const double _distance){
    distance = _distance;
    speed = 0;
    state = Parked;
}

void Regional::stop(const double _distance){
    distance = _distance;
    speed = 0;
    state = Stationary;
}

bool Regional::can_start() const{
    if(stationary() && station_timer <= 5)
        return false;
    return true;
}

void Regional::step(){
    if(running()){
        distance = next_distance();
    }else if(parked()){
        delay++;
    }else if(stationary()){
        station_timer++;
    }
         
}


ostream& operator<<(ostream& os, const Train& obj){
    os << "Il treno " << obj.get_type() << " numero: " << obj.get_number() << endl;
    os << "A distanza " << obj.get_distance() << " ha subito un ritardo di " << obj.get_delay() << " minuti" << endl;
    os << "perche sta procedendo alla velocita di " << obj.get_speed() << " km/h" << endl;
    os << "Trenitalia si scusa per il disagio" << endl;
    return os; 
}

