#include "Station.h"
#include <string>
#include "Train.h"

using namespace std;

int main() {
    string s = "Sacile";
    Principal test_principal = Principal(s, 10);
    string p = "Mirano";
    Secondary test_secondary = Secondary(p, 25);
    bool b = (test_principal != test_secondary);
    cout << b << endl;
    
    cout << test_principal.get_station_type()<< endl;
    cout << test_secondary.get_station_type() << endl; 
    cout << test_principal << endl;
    return 0;
}