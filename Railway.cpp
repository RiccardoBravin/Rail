#include "Railway.h"
#include "Station.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <cstring>

Railway::Railway(std::string line_description, TimeTable* ref){
    reference_to_TimeTable = ref;
    line_description_file_name = line_description;
    std::ifstream line_description_file (line_description_file_name);
    if(line_description_file.is_open()){
        std::string s;
        
        std::getline(line_description_file, s);
        stations.push_back(new Principal(s, 0));

        while(!line_description_file.eof()){
            std::string temp;
            std::string name;
            std::vector<std::string> tokens;
            int distance {-1};
            int type {-1};

            std::getline(line_description_file, temp);
            for (auto i = strtok(&s[0], " "); i != nullptr; i = strtok(nullptr, " "))
                tokens.push_back(i);

            distance = std::stoi(tokens[tokens.size() - 1]);
            type = std::stoi(tokens[tokens.size() - 2]);
            for(int i=0; i<tokens.size() - 2; i++) 
                name += tokens[i];

            if(type == 0){
                stations.push_back(new Principal(name, distance));
            } else if(type == 1) {
                stations.push_back(new Secondary(name, distance));
            } 
        }
    } else throw std::runtime_error("enable to open file");
}

Railway::Railway(){

}

Railway::Railway(const Railway& rw){
    line_description_file_name = rw.get_source_file_name();
    
    stations.clear();
    for(int i=0; i<rw.get_station_number(); i++) {
        if(rw.get_station(i).get_station_type() == 0) {
            stations.push_back(new Principal(rw.get_station(i).get_station_name(), rw.get_station(i).get_station_distance()));
        } else {
            stations.push_back(new Secondary(rw.get_station(i).get_station_name(), rw.get_station(i).get_station_distance()));
        }    
    }
}

Railway::Railway(Railway&& rw){

}

void Railway::reverse (Railway& rw, TimeTable* tt) {
    line_description_file_name = rw.get_source_file_name();
    reverse_railway = &rw;
    reference_to_TimeTable = tt;
    
    
    for(int i=num_stations-1; i>-1; i--) {
        stations.push_back(&get_station(i));
    }

    

}



bool Railway::operator==(const Railway& rw){
    if(line_description_file_name != rw.get_source_file_name()))
        return false;
    if(num_stations != rw.get_station_number())
        return false;
    for(int i=0; i<num_stations; i++) {
        if(rw.get_station(i).get_station_type() != get_station(i).get_station_type())
            return false;
    }
    for(int i=0; i<num_stations; i++) {
        *(stations[i]) != rw.get_station(i);
    }
}

/*Railway& Railway::operator=(Railway&& rw){

}

Railway::Railway operator=(const Railway& rw){

}*/

void Railway::verify_railway(){

}

void Railway::remove_station(int i){
    std::cout << "This station was removed:\n" << get_station(i); 
    delete stations[i];
    stations.erase(stations.begin() + i - 1);
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

/*Station& Railway::get_station_at_distance(int distance) const{
    return 0;
}*/

/*Station& Railway::get_station(std::string name){
    for(int i=0; i<stations.size(); i++) {
        if(get_station(i).get_station_name() == name)
            return *stations[i];
    }
    return nullptr;
}*/

int Railway::get_station_number() const{
    return num_stations;
}

std::string Railway::get_source_file_name() const{
    return line_description_file_name;
}

void Railway::add_station(const Station& st){
    if(st.get_station_type() == Station::Secondary) {
        Principal *temp = new Principal(st.get_station_name(), st.get_station_distance());
        stations.push_back(temp);
    }
    else {
        Secondary *temp= new Secondary(st.get_station_name(), st.get_station_distance());
        stations.push_back(temp);
    }
}

void Railway::set_source_file(std::string line_description){
    line_description_file_name= line_description;
}

std::ostream& operator<<(std::ostream& os, Railway& rw){
    os << "Railway generated from " << rw.get_source_file_name() << ".\n";
    if(rw.get_reverse_reference() == nullptr)
        os << "This is the going railway ";
    else 
        os << "This is the returning railway ";
    os << rw.get_beginning_station() << "-" << rw.get_terminal_station();
    for(int i=0; i<rw.get_station_number(); i++)
        os << rw.get_station(i);
}


Railway* Railway::get_reverse_reference() {
    return reverse_railway;
}