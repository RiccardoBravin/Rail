//Author: elia feltrin
#ifndef Railway_h
#define Railway_h


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

        Railway() { /*std::cout << "using railway default constructor\n";*/};

        
        //~Railway() {};

        bool operator==(const Railway& rw);
       
        void reverse (Railway& rw, TimeTable* tt);
       
        void verify_railway();

        void verify_correct_timing(TimeTable* tt);
       
        void remove_station(int i);

        int secondary_treats_length(int ind, bool fw);

        int principal_treats_length(int ind, bool fw);

        //void add_station(Principal& st);

        //void add_station(Secondary& st); 
        
        Station& get_beginning_station() const;
        
        Station& get_terminal_station() const;
        
        Station& get_station(int i) const;
        
        Station& get_next_principal(int this_principal_index) const;
        
        std::string get_source_file_name() const;

        int get_railway_length() const;
        
        int get_station_count() const;

        int get_principal_count() const;

        int principal_index(int this_pricipal_index) const;

        bool has_reverse() {if(reverse_railway == nullptr) return false; else return true;}

        Railway* get_reverse_reference();

        TimeTable* get_timetable_reference();

        void set_reverse_railway(Railway* ref);

        
        void set_source_file(std::string line_description);
        
        static constexpr int MIN_STATION_DISTANCE = 20;

    private:
        
        std::vector<std::unique_ptr<Station>> stations;
        
        std::string line_description_file_name;

        Railway* reverse_railway {nullptr};
        
        TimeTable* reference_to_TimeTable;
};


std::ostream& operator<<(std::ostream& os, Railway& rw);

#endif //Railway_h