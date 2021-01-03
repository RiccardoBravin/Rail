#include "TimeTable.h"
#include <fstream>
#include <exception>
#include <string>
#include <iostream>

TimeTable::TimeTable(std::vector<timetable_element> elements) {
    for(int i=0; i<elements.size(); i++){
        time_table.push_back(elements[i]);
    }
}

std::vector<TimeTable> split_timeTable(std::string time_table) {
    std::ifstream timetable_file (time_table);
    if(timetable_file.is_open()) {
        timetable_element temp;
        std::vector<timetable_element> gones;
        std::vector<timetable_element> returns;
        while(!timetable_file.eof()) {
            bool returning {false};
            std::string s;
            std::getline(timetable_file, s);
            std::vector<std::string> tokens;
            for (auto i = strtok(&s[0], " "); i != NULL; i = strtok(NULL, " "))
                tokens.push_back(i);
            temp.train_number = std::stoi(tokens[0]);
            returning = (bool)(stoi(tokens[1]));
            temp.train_type = std::stoi(tokens[2]);
            for(int i=0; ref.get_station_number(); i++) {
                temp.time_at_station[i] = std::stoi(tokens[i+3]);
            }
            if(returning) returns.push_back(&temp);
            else gones.push_back(&temp);
        }
    } else throw std::runtime_error("enable to open file");
