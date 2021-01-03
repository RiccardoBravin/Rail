//Author: elia feltrin

#include <fstream>
#include <exception>
#include <cstring>

#include "Railway.h"
#include "Station.h"

using namespace std;

Railway::Railway(string line_description, TimeTable* ref){
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
            for (auto i = strtok(&s[0], " "); i != nullptr; i = strtok(nullptr, " "))
                tokens.push_back(i);

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
}

Railway::Railway(const Railway& rw){
    line_description_file_name = rw.get_source_file_name();
    
    stations.clear();
    for(int i=0; i<rw.get_station_number(); i++) {
        if(rw.get_station(i).get_station_type() == 0) {
            stations.push_back(unique_ptr<Principal> (new Principal(rw.get_station(i).get_station_name(), rw.get_station(i).get_station_distance())));
        } else {
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.get_station(i).get_station_name(), rw.get_station(i).get_station_distance())));
        }    
    }
}

Railway& Railway::operator=(const Railway& rw){
    if(this != &rw) return*this;
    line_description_file_name = rw.line_description_file_name;
    reverse_railway = rw.reverse_railway;
    reference_to_TimeTable = rw.reference_to_TimeTable;
    num_stations = rw.num_stations;
    stations.clear();
    for(int i=0; i<rw.get_station_number(); i++) {
        if(rw.stations[i]->get_station_type() == 0)
            stations.push_back(unique_ptr<Principal> (new Principal(rw.stations[i]->get_station_name(), rw.stations[i]->get_station_distance())));
        else 
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.stations[i]->get_station_name(), rw.stations[i]->get_station_distance())));
    }
    return *this;
}

Railway::Railway(Railway&& rw){
    if(this == & rw) return;

    line_description_file_name = rw.line_description_file_name;
    rw.line_description_file_name = "";

    reverse_railway = rw.reverse_railway;
    rw.reverse_railway = nullptr;
    
    reference_to_TimeTable = rw.reference_to_TimeTable;
    rw.reference_to_TimeTable = nullptr;

    num_stations = rw.num_stations;
    rw.num_stations = 0;

    stations.clear();
    for(int i=0; i<rw.get_station_number(); i++){
        stations.push_back(rw.stations[i]);
    }
    rw.stations.clear();    
}

Railway& Railway::operator=(Railway&& rw){
    if(this == &rw) return *this;

    line_description_file_name = rw.line_description_file_name;
    rw.line_description_file_name = "";

    reverse_railway = rw.reverse_railway;
    rw.reverse_railway = nullptr;
    
    reference_to_TimeTable = rw.reference_to_TimeTable;
    rw.reference_to_TimeTable = nullptr;

    stations.clear();
    for(int i=0; i<rw.get_station_number(); i++){
        stations.push_back(rw.stations[i]);
    }
    rw.stations.clear();

    return *this;
}

bool Railway::operator==(const Railway& rw){
    if(line_description_file_name != rw.get_source_file_name()))
        return false;
    if(num_stations != rw.get_station_number())
        return false;
    for(int i=0; i<num_stations; i++) {
        *(stations[i]) != rw.get_station(i);
    }
}

void Railway::reverse (Railway& rw, TimeTable* tt) {
    line_description_file_name = rw.get_source_file_name();
    reverse_railway = &rw;
    reference_to_TimeTable = tt;
    
    for(int i=rw.stations.size() - 1; i>-1; i--) {
        int temp = rw.get_railway_length();
        if(rw.get_station(i).get_station_type() == 0)
            stations.push_back(unique_ptr<Principal> (new Principal(rw.get_station(i).get_station_name(), temp - rw.get_station(i).get_station_distance())));
        else    
            stations.push_back(unique_ptr<Secondary> (new Secondary(rw.get_station(i).get_station_name(), temp - rw.get_station(i).get_station_distance())));
    }
}

int Railway::get_railway_length() const {
    return stations[stations.size() - 1]->get_station_distance();
}

void Railway::verify_railway(){
    int num_principal {0};
    for(int i=0; i<get_station_number()-1; i++){
        if(stations[i]->get_station_type() == 0) num_principal++;
        if(stations[i+1]->get_station_distance() - stations[i]->get_station_distance() < MIN_STATION_DISTANCE) {
            if(stations[i]->)
        }
    }
}

void Railway::remove_station(int i){
    cout << "This station was removed:\n" << *(stations[i]); 
    stations.erase(stations.begin() + i - 1);
}

void Railway::add_station(Principal& st){
    stations.push_back(unique_ptr<Principal> (&st));
}

void Railway::add_station(Secondary& st){
    stations.push_back(unique_ptr<Secondary> (&st));
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

string Railway::get_source_file_name() const{
    return line_description_file_name;
}

int Railway::get_railway_length() const{
    return stations[stations.size()-1]->get_station_distance();
}

int Railway::get_station_number() const{
    return stations.size();
}

Railway* Railway::get_reverse_reference() {
    return reverse_railway;
}

TimeTable* Railway::get_timetable_reference() {
    return reference_to_TimeTable;
}

void Railway::set_source_file(string line_description){
    line_description_file_name= line_description;
}

int distance_check(const Train& a, const Train& b) {

}

ostream& operator<<(ostream& os, Railway& rw){
    os << "Railway generated from " << rw.get_source_file_name() << ".\n";
    if(rw.get_reverse_reference() == nullptr)
        os << "This is the going railway ";
    else 
        os << "This is the returning railway ";
    os << rw.get_beginning_station() << "-" << rw.get_terminal_station();
    for(int i=0; i<rw.get_station_number(); i++)
        os << rw.get_station(i);
}




