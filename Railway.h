//Author: elia feltrin

#include <vector>
#include <string>
#include <iostream>
#include "Station.h"

class Railway {
    public:
        /**
         * @brief Construct a new Railway object
         * 
         * @param line_description input file
         */
        Railway(std::string line_description);
        /**
         * @brief default constructor (useless)
         * 
         */
        Railway();
        /**
         * @brief copy constructor
         * 
         * @param reverse 1 to reverse the railway
         */
        Railway(const Railway& rw);
        /**
         * @brief move constructor
         * 
         */
        Railway(Railway&& rw);
        /**
         * @brief destroyer
         * 
         */
        ~Railway() {};

        
        /**
         * @brief reverse railway stations
         * 
         * @param rw 
         * @return Railway 
         */
        Railway reverse (Railway& rw);
        /**
         * @brief coparison operator
         * 
         */
        bool operator==(const Railway& rw);
        /**
         * @brief move operator
         * 
         */
        Railway& operator=(Railway&& rw);
        /**
         * @brief copy operator
         * 
         */
        Railway operator=(const Railway& rw);
        /**
         * @brief remove impossible station
         * 
         */
        void verify_railway();
        /**
         * @brief remove station at index i
         * 
         * @param i 
         * @return Station 
         */
        void remove_station(int i);
         /**
         * @brief Get the beginning station of this railway
         * 
         * @return Station 
         */
        Station& get_beginning_station() const;
        /**
         * @brief Get the terminal station of this railway
         * 
         * @return Station 
         */
        Station& get_terminal_station() const;
        /**
         * @brief Get the station by index
         * 
         * @param i 
         * @return Station 
         */
        Station& get_station(int i) const;
        /**
         * @brief Get the station by distance (rounded)
         * 
         * @param distance 
         * @return Station 
         */
        Station& get_station_at_distance(int distance) const;
        Station& get_station(std::string name);
        /**
         * @brief how many station in this railway
         * 
         * @return int 
         */
        int get_station_number() const;

        void add_station(const Station& st);
        void set_source_file(std::string line_description);

        int distance_check(Train& a, Train& b);
        
        std::string get_source_file_name() const;

        void set_reverse_reference(Railway* ref);
        Railway* get_reverse_reference();

    private:
        /**
         * @brief standard vector containing all station in this railway
         * 
         */
        std::vector<Station*> stations;
        /**
         * @brief input file
         * 
         */
        std::string line_description_file_name;

        Railway* reverse_railway {nullptr};

        int num_stations {0};
};

/**
 * @brief output stream operator
 * 
 */
std::ostream& operator<<(std::ostream& os, Railway& rw);

void erase_station(int i);

