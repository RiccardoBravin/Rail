#include <vector>
#include <string>
#include <iostream>
#include "Station.h"

class Railway {
    public:
        Railway(std::string line_description);
        Railway();
        Railway(const Railway& rw);
        Railway(Railway&& rw);

        Station get_beginning_station() const;
        Station get_terminal_station() const;
        Station get_station(int i) const;
        Station get_station_at_distance(int distance) const;
        int get_station_number() const;

    private:
        std::vector<Station> stations;
        std::string line_description_file;
        void update_line_description();
        int station_number;
};

std::ostream& operator<<(std::ostream& os, Railway& rw);