#include "Train.h"
 
using namespace std;

Regional::Regional(){

}

Regional::Regional(const int _number) : number(_number), speed(0), delay(0), distance(0){

}

int Regional::get_number() const{   return number;}

int Regional::get_type() const {    return 0;} 

void Regional::set_delay(const int _delay){ 
    delay =_delay;
}

int Regional::get_delay() const{    return delay;}

void Regional::set_speed(const int _speed){
    speed =_speed;
}

int Regional::get_speed() const{    return speed;}

void Regional::set_distance(const double _distance){
    distance = _distance;
}

double Regional::get_distance() const{  return distance;}
double Regional::next_distance() const{
    return distance + speed * 0.0166;
}


ostream& operator<<(ostream& os, const Train& obj){
    os << "Il treno " << obj.get_type() << " numero: " << obj.get_number() << endl;
    os << "A distanza " << obj.get_distance() << " ha subito un ritardo di " << obj.get_delay() << " minuti" << endl;
    os << "perche sta procedendo alla velocita di " << obj.get_speed() << " km/h" << endl;
    os << "Trenitalia si scusa per il disagio" << endl;
    return os; 
}

