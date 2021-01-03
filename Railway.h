//Author: elia feltrin

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "Station.h"
#include "TimeTable.h"


class Railway {
    public:
        
        Railway(std::string line_description, TimeTable* ref);
        
        Railway(const Railway& rw);

        Railway& operator=(const Railway& rw);

        Railway(Railway&& rw);

        Railway& operator=(Railway&& rw);
        
        ~Railway() {};

        bool operator==(const Railway& rw);
       
        void reverse (Railway& rw, TimeTable* tt);
       
        void verify_railway(); 
       
        void remove_station(int i);

        void add_station(Principal& st);

        void add_station(Secondary& st);
        
        Station& get_beginning_station() const;
        
        Station& get_terminal_station() const;
        
        Station& get_station(int i) const;
        
        std::string get_source_file_name() const;

        int get_railway_length() const;
        
        int get_station_number() const;

        Railway* get_reverse_reference();

        TimeTable* get_timetable_reference();

        
        void set_source_file(std::string line_description);

        int distance_check(const Train& a, const Train& b);
        
        static constexpr int MIN_STATION_DISTANCE = 20;

    private:
        
        Railway();

        std::vector<std::unique_ptr<Station>> stations;
        
        std::string line_description_file_name;

        Railway* reverse_railway {nullptr};
        
        TimeTable* reference_to_TimeTable;

};


std::ostream& operator<<(std::ostream& os, Railway& rw);

