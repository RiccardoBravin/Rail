//Author: elia feltrin

#include <fstream>
#include <exception>
#include <cstring>

#include "Railway.h"
#include "TimeTable.h"
#include "Station.h"

using namespace std;

Railway::Railway(string line_description, TimeTable* ref){
    //cout << "using railway constructor\n";
    reference_to_TimeTable = ref;
    line_description_file_name = line_description;
    ifstream line_description_file (line_description_file_name);
    if(line_description_file.is_open()){
        string s;
        
        getline(line_description_file, s);
        stations.push_back(unique_ptr<Principal> (new Principal(s, 0)));

        while(!line_description_file.eof()){
            string temp;
            string name;
            vector<string> tokens;
            int distance {-1};
            int type {-1};

            getline(line_description_file, temp);
            for (auto i = strtok(&temp[0], " "); i != NULL; i = strtok(NULL, " ")){
                tokens.push_back(i);
            }

            /*for(int i=0; i<tokens.size(); i++) cout << tokens[i] << "|";
            cout << endl;*/
            distance = stoi(tokens[tokens.size() - 1]);
            type = stoi(tokens[tokens.size() - 2]);
            for(int i=0; i<tokens.size() - 2; i++) 
                name += tokens[i];

            if(type == 0){
                stations.push_back(unique_ptr<Principal> (new Principal(name, distance)));
            } else if(type == 1) {
                stations.push_back(unique_ptr<Secondary> (new Secondary(name, distance)));
            } 
        }
    } else throw runtime_error("enable to open file");
    line_description_file.close();
}

Railway::Railway(const Railway& rw){
    //cout << "using railway copy constructor\n";
    line_description_file_name = rw.line_description_file_name;
    reference_to_TimeTable = rw.reference_to_TimeTable;
    reverse_railway = rw.reverse_railway;    
    stations.clear();
    for(int i=0; i<rw.get_station_count(); i++) {
        if(rw.get_station(i).get_type() == 0) {
            stations.push_back(unique_ptr<Principal> (new Principal(rw.get_station(i).get_name(), rw.get_station(i).get_distance())));
        } else {
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.get_station(i).get_name(), rw.get_station(i).get_distance())));
        }    
    }
}

Railway& Railway::operator=(const Railway& rw){
    //cout << "using railway copy operator\n";
    if(this != &rw) return*this;
    line_description_file_name = rw.line_description_file_name;
    reverse_railway = rw.reverse_railway;
    reference_to_TimeTable = rw.reference_to_TimeTable;
    stations.clear();
    for(int i=0; i<rw.get_station_count(); i++) {
        if(rw.stations[i]->get_type() == 0)
            stations.push_back(unique_ptr<Principal> (new Principal(rw.stations[i]->get_name(), rw.stations[i]->get_distance())));
        else 
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.stations[i]->get_name(), rw.stations[i]->get_distance())));
    }
    return *this;
}

Railway::Railway(Railway&& rw){
    //cout << "using railway move constructor\n";
    if(this == & rw) return;

    line_description_file_name = rw.line_description_file_name;
    rw.line_description_file_name = "";

    reverse_railway = rw.reverse_railway;
    rw.reverse_railway = nullptr;
    
    reference_to_TimeTable = rw.reference_to_TimeTable;
    rw.reference_to_TimeTable = nullptr;

    stations.clear();
    for(int i=0; i<rw.get_station_count(); i++){
        stations.push_back(move(rw.stations[i]));
    }
    rw.stations.clear();    
}

Railway& Railway::operator=(Railway&& rw){
    //cout << "using railway move operator\n";
    if(this == &rw) return *this;

    line_description_file_name = rw.line_description_file_name;
    rw.line_description_file_name = "";

    reverse_railway = rw.reverse_railway;
    rw.reverse_railway = nullptr;
    
    reference_to_TimeTable = rw.reference_to_TimeTable;
    rw.reference_to_TimeTable = nullptr;

    stations.clear();
    for(int i=0; i<rw.get_station_count(); i++){
        stations.push_back(move(rw.stations[i]));
    }
    rw.stations.clear();

    return *this;
}

bool Railway::operator==(const Railway& rw){
    if(line_description_file_name != rw.get_source_file_name())
        return false;
    if(stations.size() != rw.get_station_count())
        return false;
    for(int i=0; i<stations.size(); i++) {
        *(stations[i]) != rw.get_station(i);
    }
    return true;
}

void Railway::reverse (Railway& rw, TimeTable* tt) {
    line_description_file_name = rw.get_source_file_name();
    rw.set_reverse_railway(this);
    reference_to_TimeTable = tt;
    
    for(int i=rw.stations.size() - 1; i>-1; i--) {
        int temp = rw.get_railway_length();
        if(rw.get_station(i).get_type() == 0)
            stations.push_back(unique_ptr<Principal> (new Principal(rw.get_station(i).get_name(), temp - rw.get_station(i).get_distance())));
        else    
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.get_station(i).get_name(), temp - rw.get_station(i).get_distance())));
    }
}

void Railway::verify_railway(){
    int num_principal {0};
    bool was_removed {false};
    for(int i=0; i<get_station_count()-1; ){
        was_removed = false;
        bool is_principal = stations[i+1]->get_type() == Station::type::Principal;
        
        if(is_principal) num_principal++;
        
        if(stations[i+1]->get_distance() - stations[i]->get_distance() <= MIN_STATION_DISTANCE) {
            cout << "stazioni troppo vicine. elimino\n";
            was_removed = true;
            remove_station(i+1);
            reference_to_TimeTable->delete_regionals_station_time(i+1);
            
            if(has_reverse()){
                reverse_railway->remove_station(get_station_count() - i - 1);
                reverse_railway->reference_to_TimeTable->delete_regionals_station_time(reverse_railway->get_station_count() - i - 1);
            }

            if(is_principal) {
                reference_to_TimeTable->delete_fast_superFast_station_time(num_principal - 1);
                if(has_reverse())
                    reverse_railway->reference_to_TimeTable->delete_fast_superFast_station_time(reverse_railway->get_principal_count() - num_principal);
            }
        }
        if(!was_removed)i++;
    }   

    verify_correct_timing(reference_to_TimeTable);    
    if(has_reverse())
        verify_correct_timing(reverse_railway->reference_to_TimeTable);
}

void Railway::verify_correct_timing(TimeTable* tt) {
    constexpr int CROSS_STATION_TIME =  60 / 8;
    bool mod {false};

    for(int i=0; i<tt->get_timetable_size(); i++) {
        for(int j=0; j<tt->get_timetable_element(i).time_at_station.size() - 1; j++) {
            int min_temp {0};
            if(tt->get_timetable_element(i).train_type == Train::type::Regional) {
                min_temp = (int)((double)((secondary_treats_length(j, tt->is_going())) - 10 ) / Regional::MAXSPEED * 60.0 + 10.0 + CROSS_STATION_TIME);
            } else  if (tt->get_timetable_element(i).train_type == Train::type::HighSpeed){
                min_temp = (int)((double)((principal_treats_length(j, tt->is_going())) - 10 ) / HighSpeed::MAXSPEED * 60.0 + 10.0 + CROSS_STATION_TIME);
            } else {
                min_temp = (int)((double)((principal_treats_length(j, tt->is_going())) - 10 ) / SuperHighSpeed::MAXSPEED*  60.0 + 10.0 + CROSS_STATION_TIME);
            }
            
            if(min_temp > tt->get_timetable_element(i).time_at_station[j+1] - tt->get_timetable_element(i).time_at_station[j]) {
                mod = true;
                tt->modify_arrival_time(i, j+1, tt->get_timetable_element(i).time_at_station[j] + min_temp);
                cout << "TIME TABLE non compatile: orari del treno " << tt->get_timetable_element(i).train_number << " modificati." << endl; 
            }
        }
    }
    if(mod) cout << "TIME TABLE AGGIORNATA:" << endl << *tt << endl;
}

int Railway::secondary_treats_length(int ind, bool fw) {
    if(fw)
        return (stations[ind+1]->get_distance() - stations[ind]->get_distance());
    else 
        return (reverse_railway->stations[ind+1]->get_distance() - reverse_railway->stations[ind]->get_distance());
}

int Railway::principal_treats_length(int ind, bool fw) {
    
    if(fw){
        int length {0};
        int j {ind}; 
        do {
            length += secondary_treats_length(j,  true);
            j++;
        } while(stations[j]->get_type() == Station::type::Secondary);

        return length;
    } else {
        int length {0};
        int j {ind}; 
        do {
            length += secondary_treats_length(j,  false);
            j++;
        } while(reverse_railway->stations[j]->get_type() == Station::type::Secondary);

        return length;
    }
}

void Railway::remove_station(int i){
    cout << "This station was removed:\n" << *(stations[i]); 
    stations.erase(stations.begin() + i);
}

Station& Railway::get_beginning_station() const{
    return *(stations[0]);
}

Station& Railway::get_terminal_station() const{
    return *(stations[stations.size()-1]);
}

Station& Railway::get_station(int i) const{
    return *(stations[i]);
}

Station& Railway::get_next_principal(int this_station_index) const {
    int i = this_station_index + 1;
    while(stations[i]->get_type() == Station::type::Secondary) {
        i++;
    }

    return *stations[i];
}

string Railway::get_source_file_name() const{
    return line_description_file_name;
}

int Railway::get_railway_length() const{
    return stations[stations.size()-1]->get_distance();
}

int Railway::get_station_count() const{
    return stations.size();
}

int Railway::get_principal_count() const {
    int count {0};
    for(int i=0; i<stations.size(); i++) {
        if(stations[i]->get_type() == 0)
            count ++;
    }
    return count;
}

int Railway::principal_index(int this_pricipal_index) const {
    int count {0};
    int i {0};
    do {
        if(stations[i]->get_type() == Station::type::Principal)
            count ++;
        i++;
    } while (i <= this_pricipal_index);

    return count - 1;
}

Railway* Railway::get_reverse_reference() {
    return reverse_railway;
}

void Railway::set_reverse_railway(Railway* ref) {
    reverse_railway = ref;
}


TimeTable* Railway::get_timetable_reference() {
    return reference_to_TimeTable;
}

void Railway::set_source_file(string line_description){
    line_description_file_name= line_description;
}

ostream& operator<<(ostream& os, Railway& rw){
    os << "Railway generated from " << rw.get_source_file_name() << ".\n";
    if(rw.get_reverse_reference() == nullptr)
        os << "This is the returning railway ";
    else 
        os << "This is the going railway ";
    os << rw.get_beginning_station().get_name() << "   -   " << rw.get_terminal_station().get_name() << endl;
    for(int i=0; i<rw.get_station_count(); i++)
        os << rw.get_station(i);

    return os;
}