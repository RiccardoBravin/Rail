#include "Railway.h"
#include "TimeTable.h"
#include "Train.h"
#include "Station.h"
#include <memory>

class Simulation {
    public:
        Simulation(std::string line_description_file, std::string timetables_file);
        bool simulate();        //return 0 se ha fallito, 1 se tutto apposto


    private:
        TimeTable going_timetable;
        TimeTable return_timetable;
        Railway going_railway;
        Railway return_railway;
        std::vector<std::unique_ptr<Train>> going_trains;
        std::vector<std::unique_ptr<Train>> return_trains;

        int current_time {0};
        void update_current_time(int incrememt); //non ha molto senso un metodo privato che aggiorna una variabile privata, è un int, puoi fare direttamente "x + 10"

        //chiede ad una stazione di inserire il treno nei suoi parcheggi
        void park_train(Train& tr, Station& st);
        //chiede ad una stazione di inserire il treno nella banchina
        void train_to_platform(Train& tr, Station& st);
        //chiede ad una stazione di far uscire il treno dalla banchina
        void leave_platform(Train& tr, Station& st);
        //chiede alla stazione di far uscire il treno dal parcheggio
        void leave_park(Train& tr, Station& st);

        //segnale che il treno manda alla stazione quando è a venti chilometri
        void notice_entering_station_area(Train& tr, Station& st);
        void notice_entering_station_platform(Train& tr, Station& st);
        void notice_leaving_station_platform(Train& tr, Station& st);

        
        void fix_time_rail


        
};

std::string minute_to_hour(int minute);