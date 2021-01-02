#include "Station.h"
#include <string>
#include "Train.h"

using namespace std;

int main() {
    string s = "Sacile";
    Principal test_principal = Principal(s, 10);
    string p = "Mirano";
    Secondary test_secondary = Secondary(p, 25);
    Regional reg = Regional(0);
    Regional reg1 = Regional(1);
    Regional reg2 = Regional(2);
    Regional reg3 = Regional(3);
    Regional reg4 = Regional(4);
    test_principal.add_train_to_park(reg);
    test_principal.add_train_to_stop(reg1);
    test_principal.add_train_to_stop(reg2);
    bool b = (test_principal != test_secondary);
    if(b == true)
        cout << "Sono uguali" << endl;
    else 
        cout << "Sono diverse"<< endl;
    
    cout << test_principal.get_station_type()<< endl;
    cout << test_secondary.get_station_type() << endl; 
    cout << test_principal << endl;
    test_principal.remove_train_to_stop();
    test_principal.can_add_train_to_stop();
    test_principal.add_train_to_stop(reg3);
    test_principal.remove_train_to_stop();
    test_principal.remove_train_to_stop();
    cout << test_principal<< endl; 
}