#include <vector>
#include <string>
#include <iostream>
#include "Railway.h"

struct time_table_element{
    int train_number;
    bool departure_from_beginning;
    int train_type;
    std::vector<int> time_at_station;

};

class TimeTable{
    public:
        TimeTable(std::string time_table, const Railway& reference);
        TimeTable(const TimeTable& TT);
        TimeTable(TimeTable&& TT);
        bool operator==(const TimeTable& TT);

        time_table_element get_time_table_element(int train_number);
        std::vector<time_table_element> time_table;

    private:
        Railway& rw_reference;
};

std::ostream& operator<<(std::ostream& os, const TimeTable& TT);