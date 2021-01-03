//Author: elia feltrin

#include <vector>
#include <string>
#include <iostream>
#include "Railway.h"


struct timetable_element{
    int train_number;
    bool departure_from_beginning;
    int train_type;
    std::vector<int> time_at_station;
};

std::vector<TimeTable> split_timeTable(std::string time_tablem);

class TimeTable{
    public:
        
        TimeTable(std::vector<timetable_element> elemets);
        
        TimeTable(const TimeTable& tt);

        TimeTable& operator=(const TimeTable& TT);

        TimeTable(TimeTable&& TT);

        TimeTable& operator=(TimeTable&& TT);
        
        ~TimeTable() {};
        
        void modify_Timetable(const timetable_element& Tte);

        void delete_regionals_station_time(int i);

        void delete_fast_superFast_station_time(int i);
       
        bool operator==(const TimeTable& TT);

        const timetable_element& get_timetable_element(int train_number);
        
        std::vector<timetable_element> time_table;

    private:
        TimeTable() {};

};


std::ostream& operator<<(std::ostream& os, const TimeTable& TT);