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
         * @brief Get the beginning station of this railway
         * 
         * @return Station 
         */
        Station get_beginning_station() const;
        /**
         * @brief Get the terminal station of this railway
         * 
         * @return Station 
         */
        Station get_terminal_station() const;
        /**
         * @brief Get the station by index
         * 
         * @param i 
         * @return Station 
         */
        Station get_station(int i) const;
        /**
         * @brief Get the station by distance (rounded)
         * 
         * @param distance 
         * @return Station 
         */
        Station get_station_at_distance(int distance) const;
        /**
         * @brief how many station in this railway
         * 
         * @return int 
         */
        int get_station_number() const;

    private:
        /**
         * @brief standard vector containing all station in this railway
         * 
         */
        std::vector<Station> stations;
        /**
         * @brief input file
         * 
         */
        std::string line_description_file;
        /**
         * @brief how many station in this railway
         * 
         */
        int station_number;
};

/**
 * @brief output stream operator
 * 
 */
std::ostream& operator<<(std::ostream& os, Railway& rw);