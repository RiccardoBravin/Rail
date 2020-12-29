#include "Train.h"
 
using namespace std;

ostream& operator<<(ostream& os, const Train& obj){
    os << "Il treno " << obj.get_type() << " numero: " << obj.get_number() << endl;
    os << "A distanza " << obj.get_distance() << " ha subito un ritardo di " << obj.get_delay() << " ," << endl;
    os << "perche' sta procedendo alla velocità di " << obj.get_speed() << " km/h" << endl;
    os << "Trenitalia si scusa per il disagio" << endl;
    return os; 
}