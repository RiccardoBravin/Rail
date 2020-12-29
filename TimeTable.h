//Author: elia feltrin

#include <vector>
#include <string>
#include <iostream>
#include "Railway.h"

/**
 * @brief contains time informations for each train
 * 
 */
struct time_table_element{
    int train_number;
    bool departure_from_beginning;
    int train_type;
    std::vector<int> time_at_station;
};

class TimeTable{
    public:
        /**
         * @brief Construct a new Time Table object
         * 
         * @param time_table input file
         * @param reference to belonging railway istance
         */
        TimeTable(std::string time_table, const Railway& reference);
        /**
         * @brief copy constructor
         * 
         */
        TimeTable(const TimeTable& TT);
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
        time_table_element get_time_table_element(int train_number);
        /**
         * @brief container for time informations
         * 
         */
        std::vector<time_table_element> time_table;
        

    private:
        /**
         * @brief refernce to belonging railway istance
         * 
         */
        Railway& rw_reference;
};

/**
 * @brief output stream operator
 * 
 */
std::ostream& operator<<(std::ostream& os, const TimeTable& TT);