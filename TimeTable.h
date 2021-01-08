//Author: elia feltrin

#ifndef TimeTable_h
#define TimeTable_h

#include <vector>
#include <string>
#include <iostream>



struct timetable_element{
    int train_number {0};
    int train_type {0};
    std::vector<int> time_at_station;
};


class TimeTable{
    public:
        
        TimeTable(std::vector<timetable_element> elemets, bool is_going);
        
        TimeTable(const TimeTable& tt);

        TimeTable& operator=(const TimeTable& tt);

        TimeTable(TimeTable&& tt);

        TimeTable& operator=(TimeTable&& tt);

        TimeTable() {};
        
        //~TimeTable() {};
        
        bool adjust_timetable(int number_principal_stations, int number_secondary_station);

        void modify_arrival_time(int time_table_index, int station_index, int arrival_time);
        
        //void modify_Timetable(const timetable_element& tte);

        void delete_regionals_station_time(int ind);

        void delete_fast_superFast_station_time(int ind);

        bool operator==(const TimeTable& tt) const;

        timetable_element search_timetable_element(int train_number) const;

        timetable_element get_timetable_element(int ind) const;

        int get_timetable_size() const;

        bool is_going() const { return going_line; }
        

    private:
        
        bool going_line {true};
        std::vector<timetable_element> time_table;

};


std::ostream& operator<<(std::ostream& os, const TimeTable& tt);
std::ostream& operator<<(std::ostream& os, const timetable_element& tte);

std::vector<TimeTable> split_timeTable(std::string time_table);

#endif //TimeTable_h