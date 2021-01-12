#include "TimeTable.h"
#include "Train.h"
#include "utility.h"
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

        while(!timetable_file.eof()) {                                                          //leggo il file
            timetable_element temp;                                                             //elementi necessari per costruire un timetable_element
            bool returning {false};
            string s;
            getline(timetable_file, s);
            vector<string> tokens;
            for (auto i = strtok(&s[0], " "); i != NULL; i = strtok(NULL, " ")){
                tokens.push_back(i);
            }

            if(tokens.size() >= 4) {                                                             //al minimo devo avere numero del treno, tipo, verso di percorrenza e orario di partenza dalla prima stazione
                temp.train_number = stoi(tokens[0]);                                             //leggo le varie "parole"
                returning = (bool)(stoi(tokens[1]));
                temp.train_type = stoi(tokens[2]);
                for(int i=3; i<tokens.size(); i++) {                                           
                    temp.time_at_station.push_back(stoi(tokens[i]));
                }
                if(returning == true) {                                                         //a seconda del verso, memorizzo in andata o ritorno
                    returns.push_back(temp);         
                } else {
                    gones.push_back(temp); 
                }
            }
        }

        if(gones.size() == 0 && returns.size() == 0){                                           //se non ho costruiro nessun timetable_element, il file è vuoto o contine scarse o errate informazioni
            throw runtime_error("empty or bad file");
        }
        
        if(!gones.empty()){                                                                     //costruisco due istanze di TimeTable: una per verso di percorrenza (se vengono effettivamente percorsi)
            tables.push_back(TimeTable(gones, true));
        }
        if(!returns.empty()){
            tables.push_back(TimeTable(returns, false));
        }
    } else throw runtime_error("enable to open file");                                          
    timetable_file.close();                                                                     //rilascio delle risorse
    return tables;                                                                              //restituisco il vettore contente TimeTable
}



TimeTable::TimeTable(vector<timetable_element> elements, bool is_going) {                       //costruisco memorizzando i timetable_elements e il verso di percorrenza
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

void TimeTable::adjust_timetable(int number_principal_stations, int number_stations){                   //standardizza la dimensione dei vettori contenenti gli orari di arrivo nella stazione,
    bool deleted {false};                                                                               //cancellando quelli in eccesso, aggiungendo 0 dove mancanti in base al tipo di treno
    
    for(int i=0; i<time_table.size(); i++) {                                                            //se l'orario di partenza è oltre la mezzanotte non compete alla simulazione, viene eliminato
        if(time_table[i].time_at_station[0] >= 1440) {
            time_table.erase(time_table.begin() + i);
            i--;
            continue;
        }
        if(time_table[i].train_type == Train::type::Regional) {
            if(time_table[i].time_at_station.size() > number_stations){
                time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + number_stations, time_table[i].time_at_station.end());
                deleted = true;
            }
            for(int j=time_table[i].time_at_station.size(); j<number_stations; j++){
                time_table[i].time_at_station.push_back(0);
            }
        } else {
            if(time_table[i].time_at_station.size() > number_principal_stations){
                time_table[i].time_at_station.erase(time_table[i].time_at_station.begin() + number_principal_stations, time_table[i].time_at_station.end());
                deleted = true;
            }
            for(int j=time_table[i].time_at_station.size(); j<number_principal_stations; j++){
                time_table[i].time_at_station.push_back(0);
            }
        }
    }

    if(deleted) cout << "Il file contiene orari di arrivo in eccedenza. Non vengono conteggiati" << endl;           
}

void TimeTable:: modify_arrival_time(int time_table_index, int station_index, int arrival_time){                        
    time_table[time_table_index].time_at_station[station_index] = arrival_time;
}


void TimeTable::delete_regionals_station_time(int ind) {                                            
    for(int i=0; i<time_table.size(); i++) {
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

void TimeTable::set_as_going() {
    going_line = true;
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
        os << "[" << i << "]: " << mtoh(tte.time_at_station[i]) << endl;
    }

    return os;
}


