#include "Railway.h"
#include "TimeTable.h"
#include "Train.h"
#include "Station.h"

class Simulation {
    public:
        Simulation(std::string line_description_file, std::string timetables_file);
        bool simulate();        //return 0 se ha fallito, 1 se tutto apposto


    private:
        TimeTable going_timetable;
        TimeTable return_timetable;
        Railway going_railway;
        Railway return_railway;
        std::vector<Train> going_trains;
        std::vector<Train> return_trains;

        int current_time {0};
        void update_current_time(int incrememt);

        void park_train(Train& Tr, Station& St);
        void train_to_platform(Train& Tr, Station& St);
        void leave_platform(Train& Tr, Station& St);
        void leave_park(Train& Tr, Station& St);

        void notice_entering_station_area(Train& Tr, Station& St);
        void notice_entering_station_platform(Train& Tr, Station& St);
        void notice_leaving_station_platform(Train& Tr, Station& St);

        //sarebbe meglio metterle in railway così non serve un altro parametro per sapere se si vuole effettuare il calcolo in andata o ritorno
        int distance_check(Train& a, Train& b); 
        int calculate_delay(Train& a);

};

std::string minute_to_our(int minute);