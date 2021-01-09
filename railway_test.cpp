#include "Railway.h"
#include "TimeTable.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<TimeTable> tables;
    vector<Railway> railways;
    string line_description = "line_description.txt";
    string timetables = "timetables.txt";

    try{
        tables = split_timeTable(timetables);
        
    } catch(runtime_error e) {cout << e.what();}

    if(tables.size() == 2) {
    railways.push_back(Railway(line_description, &tables[0]));
    railways.push_back(Railway());
    railways[1].reverse(railways[0], &tables[1]);
    } else if(tables[0].is_going()) {
        railways.push_back(Railway(line_description, &tables[0]));
    } else {
        railways.push_back(Railway(line_description, &tables[0]));
        railways[0].reverse(railways[0], &tables[0]);
    }

    //for(int i=0; i<railways.size(); i++)  cout << railways[i] << endl << tables[i] << endl << endl;

    
    cout << "____________ADJUST_TIMETABLE__________" << endl;
    for(int i=0; i<tables.size(); i++) {
        tables[i].adjust_timetable(railways[0].get_principal_count(), railways[0].get_station_count());
    }
    for(int i=0; i<railways.size(); i++)  cout << railways[i] << endl << tables[i] << endl << endl;

    cout << "____________VERIFY_RAILWAY__________" << endl;
        railways[0].verify_railway();
    //for(int i=0; i<railways.size(); i++)  cout << railways[i] << endl << tables[i] << endl << endl;
    

    
    cout << "_______RAILWAY & TIMETABLEs CORRETTE_______" << endl << endl;
    for(int i=0; i<railways.size(); i++)  cout << railways[i] << endl << tables[i] << endl << endl;

    cout << "ho finito";
    return 0;
}