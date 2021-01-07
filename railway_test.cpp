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

    for(int i=0; i<tables.size(); i++) {
        tables[i].adjust_timetable(7);
    }

    TimeTable temp = tables[0];
    railways.push_back(Railway(line_description, &temp));
    railways.push_back(Railway());
    railways[1].reverse(railways[0], &tables[1]);

    for(int i=0; i<railways.size(); i+= 2) {
        railways[i].verify_railway();
    }
    
    for(int i=0; i<railways.size(); i++)  cout << endl << endl << railways[i] << endl << endl;

    cout << "ho finito";
    return 0;
}