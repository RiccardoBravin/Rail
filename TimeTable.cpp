#include "TimeTable.h"
#include <fstream>
#include <exception>
#include <string>
#include <iostream>

using namespace std;

vector<TimeTable> split_timeTable(string time_table) {
    ifstream timetable_file (time_table);
    vector<TimeTable> tables;
    if(timetable_file.is_open()) {
        timetable_element temp;
        vector<timetable_element> gones;
        vector<timetable_element> returns;
        while(!timetable_file.eof()) {
            bool returning {false};
            string s;
            getline(timetable_file, s);
            vector<string> tokens;
            for (auto i = strtok(&s[0], " "); i != NULL; i = strtok(NULL, " "))
                tokens.push_back(i);
            temp.train_number = stoi(tokens[0]);
            returning = (bool)(stoi(tokens[1]));
            temp.train_type = stoi(tokens[2]);
            for(int i=0; ref.get_station_number(); i++) {
                temp.time_at_station[i] = stoi(tokens[i+3]);
            }
            if(returning) returns.push_back(&temp);
            else gones.push_back(&temp);
        }
        tables.push_back(TimeTable(gones));
        tables.push_back(TimeTable(returns));
    } else throw runtime_error("enable to open file");
    return tables;
}

TimeTable::TimeTable(vector<timetable_element> elements) {
    for(int i=0; i<elements.size(); i++){
        time_table.push_back(elements[i]);
    }
}

TimeTable::TimeTable(const TimeTable& tt) {
    for(int i=0; i<tt.time_table-size()) {
        
    }
}
