/**
 * @file Train.cpp
 * @author Bravin Riccardo
 * @brief all functions implementation of train.h
 * @version 0.1
 * @date 2021-01-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Train.h"
#include <iostream>
 
using namespace std;

//**************    Train       ********************//

int Train::get_number() const{   return number;}

void Train::set_delay(const int _delay){ 
    delay =_delay;
}

int Train::get_delay() const{    return delay;}


int Train::get_speed() const{    return speed;}

void Train::set_distance(const double _distance){
    distance = _distance;
}

double Train::get_distance() const{  return distance;}

double Train::next_distance() const{
    return distance + speed / 60.0;
}

double Train::prev_distance() const{
    return distance - speed / 60.0;
}

bool Train::stationary() const{
    if(state == Stationary)
        return true;
    return false;
}

bool Train::parked() const{
    if(state == Parked)
        return true;
    return false;
}

bool Train::running() const{
    if(state == Running)
        return true;
    return false;
}

void Train::park(const double _distance){
    distance = _distance;
    speed = 0;
    state = Parked;
}

void Train::stop(const double _distance){
    distance = _distance;
    speed = 0;
    state = Stationary;
}

bool Train::can_start() const{
    if(stationary() && station_timer <= 5)
        return false;
    return true;
}

void Train::step(){
    if(running()){
        distance = next_distance();
    }else if(parked()){
        delay++; //molto probabilmente questo non andrà eseguito //e invece si
    }else if(stationary()){
        station_timer++;
    } 
}

//********************      Regional      *************************//


Regional::Regional(const int _number){
    number = _number; 
    speed = 0; 
    delay = 0; 
    distance = 0; 
    state = Running; 
    station_timer = 0;
}

Regional::Regional(const Regional& obj){
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
}

Regional& Regional::operator=(const Regional& obj){
    
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
    return *this;
}

Regional::Regional(Regional&& obj){
    if(this == &obj)
        return;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;
}

Regional& Regional::operator=(Regional&& obj){
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;

    return *this;
}


void Regional::set_speed(const int _speed){
    if(can_start()){
        if(_speed > MAXSPEED)
            speed = MAXSPEED;
        else
            speed =_speed;
        state = Running;
        station_timer = 0;
    }
}


int Regional::get_type() const {    return Train::Regional;} 






//******************        High Speed          *********************//

HighSpeed::HighSpeed(const int _number){
    number = _number; 
    speed = 0; 
    delay = 0; 
    distance = 0; 
    state = Running; 
    station_timer = 0;
}


HighSpeed::HighSpeed(const HighSpeed& obj){
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
}

HighSpeed& HighSpeed::operator=(const HighSpeed& obj){
    
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
    return *this;
}

HighSpeed::HighSpeed(HighSpeed&& obj){
    if(this == &obj)
        return;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;
}

HighSpeed& HighSpeed::operator=(HighSpeed&& obj){
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;

    return *this;
}


void HighSpeed::set_speed(const int _speed){
    if(can_start()){
        if(_speed > MAXSPEED)
            speed = MAXSPEED;
        else
            speed =_speed;
        state = Running;
        station_timer = 0;
    }
}


int HighSpeed::get_type() const {    return Train::HighSpeed;} 



//****************      Super High Speed        ***********************//

SuperHighSpeed::SuperHighSpeed(const int _number){
    number = _number; 
    speed = 0; 
    delay = 0; 
    distance = 0; 
    state = Running; 
    station_timer = 0;
}


SuperHighSpeed::SuperHighSpeed(const SuperHighSpeed& obj){
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
}

SuperHighSpeed& SuperHighSpeed::operator=(const SuperHighSpeed& obj){
    
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;
    return *this;
}

SuperHighSpeed::SuperHighSpeed(SuperHighSpeed&& obj){
    if(this == &obj)
        return;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;
}

SuperHighSpeed& SuperHighSpeed::operator=(SuperHighSpeed&& obj){
    if(this == &obj)
        return *this;
    
    number =  obj.number; 
    speed = obj.speed;
    delay = obj.delay;
    distance = obj.distance;
    state = obj.state;
    station_timer = obj.station_timer;

    obj.number = -1;
    obj.speed = -1;
    obj.delay =  -1;
    obj.distance = -1;
    obj.state = -1;
    obj.station_timer = -1;

    return *this;
}


void SuperHighSpeed::set_speed(const int _speed){
    if(can_start()){
        if(_speed > MAXSPEED)
            speed = MAXSPEED;
        else
            speed =_speed;
        state = Running;
        station_timer = 0;
    }
}


int SuperHighSpeed::get_type() const {    return Train::SuperHighSpeed;} 





//*******       External functions      *********//

ostream& operator<<(ostream& os, const Train& obj){
    os << "Il treno "; 
    if(obj.get_type() == Train::type::Regional){
        os << "regionale";
    }else if(obj.get_type() == Train::type::HighSpeed){
        os << "alta velocita'";
    }else if(obj.get_type() == Train::type::SuperHighSpeed){
        os << "alta velocita' super";
    }
    os << " numero: " << obj.get_number() << " a distanza " << obj.get_distance() << "km" << endl;
    
    if(obj.get_delay() > 0){
        os << "E' in ritardo di " << obj.get_delay() << " minuti. ";
    }else if(obj.get_delay() < 0){
        os << "E' in anticipo di " << obj.get_delay() << " minuti. ";
    }
    
    os << "Sta procedendo alla velocita di " << obj.get_speed() << " km/h. ";
    if(obj.parked()){
        os << "Il treno e' attualmente in sosta" << endl;
        os << "Trenitalia si scusa per il disagio" << endl;
    }else if(obj.stationary()){
        os << "Il treno e' attualmete in stazione" << endl;
    }
    
    return os; 
}

