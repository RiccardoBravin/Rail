//Author: elia feltrin

#ifndef TimeTable_h
#define TimeTable_h

#include <vector>
#include <string>
#include <iostream>
#include "Railway.h"


struct timetable_element{
    int train_number {0};
    int train_type {0};
    std::vector<int> time_at_station;
};

std::vector<TimeTable> split_timeTable(std::string time_table);

class TimeTable{
    public:
        
        TimeTable(std::vector<timetable_element> elemets);
        
        TimeTable(const TimeTable& tt);

        TimeTable& operator=(const TimeTable& tt);

        TimeTable(TimeTable&& tt);

        TimeTable& operator=(TimeTable&& tt);
        
        ~TimeTable() {};
        
        void adjust_timetable(int number_stations);
        
        //void modify_Timetable(const timetable_element& tte);

        void delete_regionals_station_time(int ind);

        void delete_fast_superFast_station_time(int ind);
       
        bool operator==(const TimeTable& tt) const;

        timetable_element search_timetable_element(int train_number) const;

        timetable_element get_timetable_element(int ind) const;

        int get_timetable_size() const;

        
        

    private:
        TimeTable() {};

        std::vector<timetable_element> time_table;

};


std::ostream& operator<<(std::ostream& os, const TimeTable& tt);
std::ostream& operator<<(std::ostream& os, const timetable_element& tte);
#endif //TimeTable_h