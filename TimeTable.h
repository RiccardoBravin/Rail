//Author: elia feltrin

#include <vector>
#include <string>
#include <iostream>
#include "Railway.h"

/**
 * @brief contains time informations for each train
 * 
 */
struct timetable_element{
    int train_number;
    bool departure_from_beginning;
    int train_type;
    std::vector<int> time_at_station;
};

/**
 * @brief split timetable file: one time table for gone, one for return
 * 
 * @param time_table 
 * @return std::vector<TimeTable> 
 */
std::vector<TimeTable> split_timeTable(std::string time_tablem, Railway& ref);

class TimeTable{
    public:
        /**
         * @brief Construct a new Time Table object
         * 
         * @param time_table input file
         */
        TimeTable(std::vector<timetable_element> elemets, Railway& ref);
        /**
         * @brief copy constructor
         * 
         */
        /*TimeTable(const TimeTable& TT);
        /**
         * @brief move constructor
         * 
         */
        TimeTable(TimeTable&& TT);
        /**
         * @brief destroyer
         * 
         */
        ~TimeTable() {};

        /**
         * @brief 
         * 
         */
        void modify_Timetable(const timetable_element& Tte);

        void delete_station_time(int i);

        /**
         * @brief comparison operator
         * 
         */
        bool operator==(const TimeTable& TT);
        /**
         * @brief move operator
         * 
         */
        TimeTable& operator=(TimeTable&& TT);
        /**
         * @brief copy operator
         * 
         */
        TimeTable operator=(const TimeTable& TT);

        /**
         * @brief Get the time table element by train number
         * 
         * @param train_number 
         * @return time_table_element 
         */
        const timetable_element& get_timetable_element(int train_number);
        /**
         * @brief container for time informations
         * 
         */
        std::vector<timetable_element> time_table;

        Railway& get_railway_reference();
        

    private:
        Railway* reference;
};

/**
 * @brief output stream operator
 * 
 */
std::ostream& operator<<(std::ostream& os, const TimeTable& TT);