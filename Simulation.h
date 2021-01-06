#include "Railway.h"
#include "TimeTable.h"
#include "Train.h"
#include "Station.h"
#include <memory>
#include <vector>
#include <list>

class Simulation {
    public:
        Simulation(std::string line_description_file, std::string timetables_file);
        bool simulate();        //return 0 se ha fallito, 1 se tutto apposto


    private:
        TimeTable fw_timetable;
        TimeTable bw_timetable;
        Railway fw_railway;
        Railway bw_railway;
        std::vector<std::list<std::unique_ptr<Train>>> fw_trains; //forward
        std::vector<std::list<std::unique_ptr<Train>>> bw_trains; //backward

        //std
        

        int current_time {0};
        
        bool start_trains(); //takes the timetable and cycles throught it to view if it has to create a train to start simulating it
        //deve ciclare su tutti i treni presenti in timetable, se è arrivata l'ora di partire e non sono già 
        //stati messi in trains allora fallo partire se possibile (una linea libera e free_to_start) e inseriscilo nella banchina della prima stazione

        bool free_to_start(Station* st, Train* tr);//true if the train has a free path to start and is the best that can start for that station
        //(da diversificare per Primary e Secondary) controllare se la linea è libera per 10km e se il treno che ho scelto 
        //è il migliore da far partire e se la linea di transito (se c'è) è libera

        bool notice_20_km_mark(Train* tr);//controlla se il treno è a 20 km dalla stazione successiva riferisce il suo stato

        void check_distance();//controlla ed eventualmente sistema tutti i problemi con le distanze e velocità fra tutti i treni 
        
        bool entering_station(Train* tr);//return true if the specified train is going to enter the station area the next step

        void in_station(); //checks all trains ad decides what to do when they enter the station area
        //se è in anticipo calcola l'anticipo metti nel parcheggio
        //se la stazione è principale e il treno che sto guardando ha un treno in culo mettilo  e c'è solo una banchina libera
        //mettilo nel parcheggio altrimenti se è un regionale con due treni in culo mettilo nel parcheggio, altrimenti metti in una banchina
        //se la stazione è secondaria e il treno in analisi è Regionale se ho almeno una banchina libera va altrimenti nel parcheggio,
        //se il treno non è un hs che ha un shs dietro e c'è solo una banchina libera allora decidi con la funzione se parcheggiarlo o farlo andare
        //in tutti gli altri casi fai passare il treno

        bool decide_station_passing(Train* a, Train* b); //questa è la funzione magica che decide chi far passare in entrata alla stazione

        void parked_trains();//decides for each train in the parking slots what to do
        //se ho esattamente una banchina libera prendo il treno con il maggior ritardo e di tier piu alto e se la funzione magica dice 
        //che può passare entra nella banchina altrimenti stanno tutti li. se hai due banchine libere manda il treno più "figo"

        bool should_this_parked_train_go(Train*a, Train* b); //il primo treno è quello nel parcheggio, il secondo è il treno che lo precede
        //se non c'è un treno nella tratta precedente passa comunque

        Train* get_previous_train(std::unique_ptr<Train>* tr); //ritorna il puntatore al treno precedente


        void stop_trains();//stops the train that need to unload passangers
        //cicla i treni nelle banchine e li fa fermare se arrivati alla stazione

        //mette il treno nel parcheggio della stazione
        void park_train(Train* tr, Station* st);
        
        //mette il treno nella banchina della stazione
        void train_to_platform(Train& tr, Station& st);

        //rimuove un treno dalla banchina della stazione
        void leave_platform(Train& tr, Station& st);

        //rimuove un treno dal parcheggio della stazione
        void leave_park(Train& tr, Station& st);

        //segnale che il treno manda alla stazione quando è a venti chilometri
        void notice_entering_station_area(Train& tr, Station& st);

        void notice_entering_station_platform(Train& tr, Station& st);
        
        void notice_leaving_station_platform(Train& tr, Station& st);
        

        //richiama step per ogni treno in ogni railway
        void step();



        //funzione opzionale che seve se siamo lazy
        void sort_trains();
};


//QUESTA VA SPOSTATA IN UN .H A SE COSì CHE TUTTI LA POSSANO USARE NELLE LORO CLASSI PER DIRE L'ORA
std::string minute_to_hour(int minute);