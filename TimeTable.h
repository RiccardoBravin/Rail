//Author: elia feltrin

#ifndef TimeTable_h
#define TimeTable_h

#include <vector>
#include <string>
#include <iostream>



struct timetable_element{
    int train_number {0};
    int train_type {0};
    std::vector<int> time_at_station;
};


class TimeTable{
    public:
        /**
         * @brief Costruttore
         * 
         * @param elements 
         * @param is_going 
         */
        TimeTable(std::vector<timetable_element> elements, bool is_going);
        
        /**
         * @brief Costruttore di copia
         * 
         * @param tt 
         */
        TimeTable(const TimeTable& tt);

        /**
         * @brief Operatore di copia
         * 
         * @param tt 
         * @return TimeTable& 
         */
        TimeTable& operator=(const TimeTable& tt);

        /**
         * @brief Costruttore di spostamento
         * 
         * @param tt 
         */
        TimeTable(TimeTable&& tt);

        /**
         * @brief Operatore di spostamento
         * 
         * @param tt 
         * @return TimeTable& 
         */
        TimeTable& operator=(TimeTable&& tt);

        /**
         * @brief Costruttore di default
         * 
         */
        TimeTable() {};
        
        //E' sufficente il distruttore generato dal compilatore

        /**
         * @brief Standardizza gli orari di arrivo
         * 
         * @details Elimina gli orari in eccedenza segnalandolo, aggiunge 0 dove mancanti(necessario per altri controlli), elimina i treni in partenza dopo le 23.59
         * 
         * @param number_principal_stations 
         * @param number_secondary_station 
         * @
         */
        void adjust_timetable(int number_principal_stations, int number_secondary_station);

        /**
         * @brief Modifica gli orari di arrivo di un treno in una stazione
         * 
         * @param time_table_index 
         * @param station_index 
         * @param arrival_time 
         */
        void modify_arrival_time(int time_table_index, int station_index, int arrival_time);
        
        /**
         * @brief Cancella gli orari di arrivo in una stazione solamente per i treni regionali
         * 
         * @param ind 
         */
        void delete_regionals_station_time(int ind);

        /**
         * @brief Cancella gli orari di arrivo in una stazione solamente per i treni HighSpeed e SuperHighSpeed
         * 
         * @param ind 
         */
        void delete_fast_superFast_station_time(int ind);

        /**
         * @brief operatore di uguaglianza
         * 
         * @param tt 
         * @return true 
         * @return false 
         */
        bool operator==(const TimeTable& tt) const;

        /**
         * @brief Cerca i dati relativi a un treno 
         * 
         * @param train_number 
         * @return timetable_element per copia
         */
        timetable_element search_timetable_element(int train_number) const;

        /**
         * @brief Restiuisce la i-esima istanza di timetable_element presente
         * 
         * @param ind 
         * @return timetable_element per copia
         */
        timetable_element get_timetable_element(int ind) const;

        /**
         * @brief Restituisce il numero di timetable_elemetn contenute
         * 
         * @return int 
         */
        int get_timetable_size() const;

        /**
         * @brief Restuisce il verso di percorrenza comune a tutti i treni di questa istanza di TimeTable
         * 
         * @return true 
         * @return false 
         */
        bool is_going() const { return going_line; }

        /**
         * @brief Imposta il verso di percorrenza di questa istanza di TimeTable
         * 
         */
        void set_as_going();
        

    private:
        
        bool going_line {true};
        std::vector<timetable_element> time_table;

};

/**
 * @brief Overload operatore di output per TimeTable
 * 
 * @param os 
 * @param tt 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const TimeTable& tt);

/**
 * @brief Overload opeartore di output per timetable_element
 * 
 * @param os 
 * @param tte 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const timetable_element& tte);

/**
 * @brief Divide le informazioni dei treni a seconda del verso di percorrenza
 * 
 * @details Se sono presenti treni sia in andata che al ritorno ha dimensione due: all'indice 0 sono presenti le informazioni sui treni di andata, all'indice 1 di ritorno
 * @details Se è presente un solo verso di percorrenza, ha dimensione 1. is_going() per scoprire il verso
 * 
 * @param time_table 
 * @return std::vector<TimeTable> 
 */
std::vector<TimeTable> split_timeTable(std::string time_table);

#endif //TimeTable_h