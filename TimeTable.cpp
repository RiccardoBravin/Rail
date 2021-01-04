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
        vector<timetable_element> gones;
        vector<timetable_element> returns;
        while(!timetable_file.eof()) {
            timetable_element temp;
            bool returning {false};
            string s;
            getline(timetable_file, s);
            vector<string> tokens;
            for (auto i = strtok(&s[0], " "); i != NULL; i = strtok(NULL, " "))
                tokens.push_back(i);
            temp.train_number = stoi(tokens[0]);
            returning = (bool)(stoi(tokens[1]));
            temp.train_type = stoi(tokens[2]);
            for(int i=3; tokens.size(); i++) {
                temp.time_at_station.push_back(stoi(tokens[i]));
            }
            if(returning) returns.push_back(temp);
            else gones.push_back(temp);
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
    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); i++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[i]);
        }
        time_table.push_back(copy);
    }
}

TimeTable& TimeTable::operator=(const TimeTable& tt) {
    time_table.clear();

    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); i++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[i]);
        }
        time_table.push_back(copy);
    }

    return *this;
}

TimeTable::TimeTable(TimeTable&& tt) {
    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); i++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[i]);
        }
        time_table.push_back(copy);
    }

    tt.time_table.clear();
}

TimeTable& TimeTable::operator=(TimeTable&& tt) {
    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); i++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[i]);
        }
        time_table.push_back(copy);
    }

    tt.time_table.clear();
    return *this;
}

void TimeTable::adjust_timetable(int number_stations){
    for(int i=0; i<time_table.size(); i++) {
        if(time_table[i].time_at_station.size() > number_stations){
            time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + number_stations, time_table[i].time_at_station.end());
        }
        for(int i=time_table[i].time_at_station.size(); i<number_stations; i++){
            time_table[i].time_at_station.push_back(0);
        }
    }
}

/*void TimeTable::modify_Timetable(const timetable_element& tte) {

}*/

void TimeTable::delete_regionals_station_time(int ind) {
    for(int i=0; i<time_table.size(); i++) {
        time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + ind - 1);
    }
}

void TimeTable::delete_fast_superFast_station_time(int ind){
    for(int i=0; i<time_table.size(); i++) {
        time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + ind - 1);
    }
}

bool TimeTable::operator==(const TimeTable& tt) const {
    if(time_table.size() != tt.time_table.size())
        return false;
    for(int i=0; i<time_table.size(); i++) {
        if(time_table[i].train_number != tt.time_table[i].train_number)
            return false;
        if(time_table[i].train_type != tt.time_table[i].train_type)
            return false;
    }

    for(int i=0; i<time_table.size(); i++) {
        for(int j=0; j<time_table[i].time_at_station.size(); i++) {
            if(time_table[i].time_at_station[j] != tt.time_table[i].time_at_station[j])
                return false;
        }
    }

    return true;
}

timetable_element TimeTable::search_timetable_element(int train_number) const {
    for(int i=0; i<time_table.size(); i++) {
        if(time_table[i].train_number == train_number) 
        return time_table[i];
    }
    timetable_element error;
    return error;
}

timetable_element TimeTable::get_timetable_element(int ind) const {
    return time_table[ind];
}

std::ostream& operator<<(std::ostream& os, const TimeTable& tt) {
    for(int i=0; i<tt.get_timetable_size(); i++) {
        os << tt.get_timetable_element(i) << "\n\n\n";
    }
}

std::ostream& operator<<(std::ostream& os, const timetable_element& tte){
    os << "Train " << tte.train_number << endl;

    if(tte.train_number == 1) {
         os << "Regional\n";
         os << "arrive at station [station_index] at:\n";
    }
    else {
        if(tte.train_number == 2) os << "Fast\n";
        else os << "Super fast\n";
        os << "arrives at principal station [principal_station_index] at:\n";
    }

    for(int i=0; i< tte.time_at_station.size(); i++){
        os << "[" << i << "]: " << tte.time_at_station[i] << endl;
    }
}


