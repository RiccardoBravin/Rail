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


    railways.push_back(Railway(line_description, &tables[0]));
    railways.push_back(Railway());
    railways[1].reverse(railways[0], &tables[1]);

    //cout << railways[0] << tables[0] << endl << endl << railways[1] << tables[1] <<  endl;

    
    cout << "____________ADJUST_TIMETABLE__________" << endl;
    for(int i=0; i<tables.size(); i++) {
        tables[i].adjust_timetable(railways[0].get_principal_count(), railways[0].get_station_count());
    }
    //cout << railways[0] << tables[0] << endl << endl << railways[1] << tables[1] <<  endl;

    cout << "____________VERIFY_RAILWAY__________" << endl;
        railways[0].verify_railway();
    //cout << railways[0] << tables[0] << endl << endl << railways[1] << tables[1] <<  endl;
    

    
    cout << "_______RAILWAY & TIMETABLEs CORRETTE_______" << endl << endl;
    for(int i=0; i<railways.size(); i++)  cout << railways[i] << endl << tables[i] << endl << endl;

    cout << "ho finito";
    return 0;
}