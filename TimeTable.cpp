#include "TimeTable.h"
#include "Train.h"
#include <fstream>
#include <exception>
#include <string>
#include <iostream>
#include <cstring>

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
            for (auto i = strtok(&s[0], " "); i != NULL; i = strtok(NULL, " ")){
                tokens.push_back(i);
            }
            if(tokens.size() > 2) {
                temp.train_number = stoi(tokens[0]);
                returning = (bool)(stoi(tokens[1]));
                temp.train_type = stoi(tokens[2]);
                for(int i=3; i<tokens.size(); i++) {
                    temp.time_at_station.push_back(stoi(tokens[i]));
                }
                if(returning == true) {
                    returns.push_back(temp);         
                } else {
                    gones.push_back(temp); 
                }
            }
        }

        if(gones.size() == 0 && returns.size() == 0){
            throw runtime_error("file empty");
        }
        
        if(!gones.empty()){
            tables.push_back(TimeTable(gones, true));
        }
        if(!returns.empty()){
            tables.push_back(TimeTable(returns, false));
        }
    } else throw runtime_error("enable to open file");
    timetable_file.close();
    return tables;
}



TimeTable::TimeTable(vector<timetable_element> elements, bool is_going) {
    //cout << "using constructor\n";
    for(int i=0; i<elements.size(); i++){
        time_table.push_back(elements[i]);
    }
    going_line = is_going;
}

TimeTable::TimeTable(const TimeTable& tt) {
    //cout << "using copy constructor\n";
    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); j++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[j]);
        }
        time_table.push_back(copy);
    }

    going_line = tt.is_going();
}

TimeTable& TimeTable::operator=(const TimeTable& tt) {
    //cout << "using copy operator\n";
    if(this == &tt) return *this;
    time_table.clear();

    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); j++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[j]);
        }
        time_table.push_back(copy);
    }
    going_line = tt.is_going();
    return *this;
}

TimeTable::TimeTable(TimeTable&& tt) {
    //cout << "using move constructor\n";
    if(this == &tt) return;

    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;

        for(int j=0; j<tt.time_table[i].time_at_station.size(); j++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[j]);
        }
        time_table.push_back(copy);
    }
    going_line = tt.going_line;
    tt.time_table.clear();
    tt.going_line = false;
}

TimeTable& TimeTable::operator=(TimeTable&& tt) {
    if(this == &tt) return *this;
    //cout << "using move operator\n";
    for(int i=0; i<tt.time_table.size(); i++) {
        timetable_element copy;
        copy.train_number = tt.time_table[i].train_number;
        copy.train_type =  tt.time_table[i].train_type;
        for(int j=0; j<tt.time_table[i].time_at_station.size(); j++) {
            copy.time_at_station.push_back(tt.time_table[i].time_at_station[j]);
        }
        time_table.push_back(copy);
    }

    tt.time_table.clear();
    going_line = tt.going_line;
    tt.going_line = false;
    return *this;
}

bool TimeTable::adjust_timetable(int number_principal_stations, int number_stations){
    bool added {false};
    bool deleted {false};
    
    
    for(int i=0; i<time_table.size(); i++) {
        if(time_table[i].train_type == Train::type::Regional) {
            if(time_table[i].time_at_station.size() > number_stations){
                time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + number_stations, time_table[i].time_at_station.end());
                deleted = true;

                //cout << number_stations << " =? " << time_table[i].time_at_station.size() << endl;
            }
            for(int j=time_table[i].time_at_station.size(); j<number_stations; j++){
                time_table[i].time_at_station.push_back(0);
                added = true;
            }
        } else {
            if(time_table[i].time_at_station.size() > number_principal_stations){
                time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + number_principal_stations, time_table[i].time_at_station.end());
                deleted = true;

                //cout << number_stations << " =? " << time_table[i].time_at_station.size() << endl;
            }
            for(int j=time_table[i].time_at_station.size(); j<number_principal_stations; j++){
                time_table[i].time_at_station.push_back(0);
                added = true;
            }
        }
    }

    if(deleted) cout << "Il file contiene orari di arrivo in eccedenza. Non vengono conteggiati" << endl;
    return added;
}

void TimeTable:: modify_arrival_time(int time_table_index, int station_index, int arrival_time){
    time_table[time_table_index].time_at_station[station_index] = arrival_time;
}

/*void TimeTable::modify_Timetable(const timetable_element& tte) {

}*/

void TimeTable::delete_regionals_station_time(int ind) {
    
    //cout <<  time_table[0] << endl;
    for(int i=0; i<time_table.size(); i++) {
        //cout << "fin qua\n";
        if(time_table[i].train_type == Train::type::Regional)
            time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + ind);
    }
}

void TimeTable::delete_fast_superFast_station_time(int ind){
    for(int i=0; i<time_table.size(); i++) {
        if(time_table[i].train_type == Train::type::HighSpeed || time_table[i].train_type == Train::type::SuperHighSpeed) {
            time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + ind);
        }
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

int TimeTable::get_timetable_size() const {
    return time_table.size();
}


std::ostream& operator<<(std::ostream& os, const TimeTable& tt) {
    for(int i=0; i<tt.get_timetable_size(); i++) {
        os << tt.get_timetable_element(i) << "\n\n\n";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const timetable_element& tte){
    os << "Train " << tte.train_number << endl;

    if(tte.train_type == 1) {
         os << "Regional\n";
         os << "arrive at station [station_index] at:\n";
    }
    else {
        if(tte.train_type == 2) os << "Fast\n";
        else if(tte.train_type == 3) os << "Super fast\n";
        os << "arrives at principal station [principal_station_index] at:\n";
    }

    for(int i=0; i< tte.time_at_station.size(); i++){
        os << "[" << i << "]: " << tte.time_at_station[i] << endl;
    }

    return os;
}


