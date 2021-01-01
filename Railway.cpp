#include "Railway.h"
#include "Station.h"
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <cstring>

Railway::Railway(std::string line_description){
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
            stations.push_back(&rw.get_station(i));
        } else {
            stations.push_back(&rw.); 
        }    
    }
}

Railway::Railway(Railway&& rw){

}

Railway reverse (const Railway& rw){
    Railway temp;
    temp.set_source_file(rw.get_source_file_name());
    
    
    for(int i=rw.get_station_number()-1; i>-1; i--) {
        temp.add_station(rw.get_station(i));
    }
}

Railway::bool operator==(const Railway& rw){

}

Railway::Railway& operator=(Railway&& rw){

}

Railway::Railway operator=(const Railway& rw){

}

void Railway::verify_railway(){

}

Railway::Station remove_station(int i){

}

Railway::Station get_beginning_station() const{

}

Railway::Station get_terminal_station() const{

}

Railway::Station get_station(int i) const{

}

Railway::Station get_station_at_distance(int distance) const{

}

Railway::int get_station_number() const{

}

std::string get_source_file_name() const{

}

Railway::void add_station(const Station& st){

}

Railway::void set_source_file(std::string line_description){

}

std::ostream& operator<<(std::ostream& os, Railway& rw){

}