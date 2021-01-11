#include "Railway.h"
#include "TimeTable.h"
#include "Train.h"
#include "Station.h"
#include <memory>
#include <vector>
#include <list>
#include <iterator>

class Simulation {
    public:
        Simulation(std::string line_description_file, std::string timetables_file);
        void simulate();        


    private:
        int RAILWAYS {0};

        int current_time {0};

        std::vector<TimeTable> timetable;
        std::vector<Railway> railway;
        std::vector<std::vector<std::unique_ptr<Train>>> trains;

        int trains_at_trminal {0};
        
        

        int calc_delay(int k, int tr_index, int st_index);


        void start_trains(); //takes the timetable and cycles throught it to view if it has to create a train to start simulating it
        //deve ciclare su tutti i treni presenti in timetable, se è arrivata l'ora di partire e non sono già 
        //stati messi in trains allora fallo partire se possibile (una linea libera e free_to_start) e inseriscilo nella banchina della prima stazione


        bool free_to_start(Station* st,  int trains_index) const;//true if the train has a free path to start 
        //(da diversificare per Primary e Secondary) controllare se la linea è libera per 10km
        // e se la linea di transito (se c'è) è libera

        void notice_20_km_mark();//cicla sui treni, se un treno è a venti km da una stazione avvisa l'utente dell'accaduto 

        void check_distance();//controlla ed eventualmente sistema tutti i problemi con le distanze e velocità fra tutti i treni 
        


        void exit_station();//se un treno sta uscendo dalla stazione allora va alla velocità massima

        void in_station(); //checks all trains ad decides what to do when they enter the station area
        //se è in anticipo calcola l'anticipo metti nel parcheggio
        //se la stazione è principale e il treno che sto guardando ha un treno in culo mettilo  e c'è solo una banchina libera
        //mettilo nel parcheggio altrimenti se è un regionale con due treni in culo mettilo nel parcheggio, altrimenti metti in una banchina
        //se la stazione è secondaria e il treno in analisi è Regionale se ho almeno una banchina libera va altrimenti nel parcheggio,
        //se il treno non è un hs che ha un shs dietro e c'è solo una banchina libera allora decidi con la funzione se parcheggiarlo o farlo andare
        //in tutti gli altri casi fai passare il treno

        bool decide_station_passing(Train* a, Train* b); //questa è la funzione magica che decide chi far passare in entrata alla stazione
        //se il ritardo di a + (a.pos - b.pos)/b.vel > (next_station.lenght/b.vel)-(next_station.lenght/b.vel)+ ritardo di b
        //allora fai procedere a altrimenti metti a nel parcheggio


        bool best_train_in_station(Station* st, Train* t);

        void parked_trains();//decides for each train in the parking slots what to do
        //se ho esattamente una banchina libera prendo il treno con il maggior ritardo e di tier piu alto e se la funzione magica dice 
        //che può passare entra nella banchina altrimenti stanno tutti li. se hai due banchine libere manda il treno più "figo"

        int best_train_in_park(int k, int st_index); //il primo treno è quello nel parcheggio, il secondo è il treno che lo precede
        //se non c'è un treno nella tratta precedente passa comunque

        int best_regional_in_park(int k , int st_index);

        int prev_train_index(int k, int tr_index); //ritorna il puntatore al treno precedente

        bool smart_train_function(int k, int tr_index, int st_index);

        void stop_trains();//stops the train that need to unload passangers
        //cicla i treni nelle banchine e li fa fermare se arrivati alla stazione

        //mette il treno nel parcheggio della stazione
        void park_train(Station& st, Train* tr);
        
        //rimuove un treno dal parcheggio della stazione
        void leave_park(Station& st, Train* tr);
        
        
        //mette il treno nell binario di transito
        void add_train_transit(Station& st, Train* tr);
        
        //toglie il treno dal binario di transito
        void remove_train_transit(Station& st, Train* tr);

        //mette il treno nella banchina libera
        void entering_station_area(Station& st, Train* tr);
        
        //toglie il treno dalla banchina
        void exiting_station_area(Station& st, Train* tr);

        
        
        
        //rimuove tutti i treni che hanno superato l'ultima stazione così che non vengano più simulati ed aumenta il contatore 
        //nel rispettivo vettore di int trains_in_terminal
        void ending_station();


        //controlla se tutti i numeri in trans_in_trminal corrispondono a tutti i treni da simulare
        //true solo se ho terminato di simulare
        bool end_simulation();
        
        

        //richiama step per ogni treno in ogni railway
        void step();



        //funzione opzionale che seve se siamo lazy
        void sort_trains();
};



void push_front_train(const timetable_element& a, std::vector<std::unique_ptr<Train>>* trains);