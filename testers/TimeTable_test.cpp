#include "TimeTable.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<TimeTable> temp;
    string line_description = "line_description.txt";
    string timetables = "timetables.txt";

    try{
        temp = split_timeTable(timetables);
    } catch(runtime_error e) {cout << e.what();}

    for(int i=0; i<temp.size(); i++) {
        temp[i].adjust_timetable(7);
    }

    if(temp.size() == 2) {  
        cout << "E' presnte una linea di andata e una di ritorno. Creo due linee e due due orari.\n";
        TimeTable going_tt = temp[0];
        TimeTable returning_tt = temp[1];
        temp.clear();
        //going_tt.delete_regionals_station_time(0);
        cout << "TABELLA ORARI DI ANDATA:\n" << going_tt << endl << endl;
        cout << "TABELLA ORARI DI RITORNO:\n" << returning_tt << endl << endl;
        //cout << going_tt.search_timetable_element(6780);
        
    } else {
        if(temp[0].is_going()) {
            cout << "E' presenete solamente la linea di andata. Creo una linea e una tabella di orari.\n";
            TimeTable going_tt = temp[0];
            cout << "TABELLA ORARI:\n" << going_tt << endl << endl;
        } else {
            cout << "E' presente solamente la linea di ritorno. Creo una linea e una sola tabella di orari\n";
            TimeTable returning_tt = temp[0];
            cout << "TABELLA ORARI:\n" << returning_tt << endl << endl;
        }
    }

    


    cout << "ho finito";
    return 0;
}