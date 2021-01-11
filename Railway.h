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
        /**
         * @brief Costruttore
         * 
         * @param line_description 
         * @param ref TimeTable relativa
         */
        Railway(std::string line_description, TimeTable* ref);
        
        /**
         * @brief Costruttore di copia
         * 
         * @param rw 
         */
        Railway(const Railway& rw);

        /**
         * @brief Operatore di copia
         * 
         * @param rw 
         * @return Railway& 
         */
        Railway& operator=(const Railway& rw);

        /**
         * @brief Costruttore di spostamento
         * 
         * @param rw 
         */
        Railway(Railway&& rw);
        
        /**
         * @brief Operatore di spostamento
         * 
         * @param rw 
         * @return Railway& 
         */
        Railway& operator=(Railway&& rw);

        //Costruttore di default
        Railway() { /*std::cout << "using railway default constructor\n";*/};

        
        //E' sufficente il distruttore generato dal compilatore

        /**
         * @brief Operatore di ugualglianza
         * 
         * @param rw 
         * @return true 
         * @return false 
         */
        bool operator==(const Railway& rw);
       
        /**
         * @brief Memorizza rw percorsa in direzione opposta. Cancella i dati contenuti precedentemente
         * 
         * @param rw 
         * @param tt 
         */
        void reverse (Railway& rw, TimeTable* tt);

        /**
         * @brief Controlla la validità delle stazioni e richiama verify_correct_timing(Timetable*
         * 
         * @details Se due stazioni hanno distanza <= MIN_STATION_DISTANCE: elimina la più distante dall'origine e la relativa sulla railway inversa (se presente), cancellando tutti i relativi orari di arrivo dalle timetable
         * 
         */
        void verify_railway();

        /**
         * @brief Verifica che i tempi di percorrenza siano compatibili con le velovità massime, aventualmente correggendoli
         * 
         * @details Per essere considerato corretto, il tempo di percorrenza deve contenere: il tempo necessario per percorrere la tratta fra una stazione e l'altra a massima velocità meno i 10 km all'interno delle stazioni percorsi a 80 km/h più 10 minuti 
         * 
         * @param tt 
         */
        void verify_correct_timing(TimeTable* tt);
       
       /**
        * @brief elimina una stazione dalla tratta
        * 
        * @details Segnala in output
        * 
        * @param i 
        */
        void remove_station(int i);

        /**
         * @brief Calcola la distanza fra due stazioni 
         * 
         * @param ind 
         * @param fw 
         * @return int 
         */
        int secondary_treats_length(int ind, bool fw);

        /**
         * @brief calcola la distanza fra due stazioni pricipali, ignorando le secondarie nel mezzo
         * 
         * @param ind 
         * @param fw 
         * @return int 
         */
        int principal_treats_length(int ind, bool fw);

        /**
         * @brief Restituisce la prima stazione della tratta
         * 
         * @return Station& 
         */
        Station& get_beginning_station() const;

        /**
         * @brief Reistituisce l'ultima stazione della tratta
         * 
         * @return Station& 
         */
        Station& get_terminal_station() const;
        
        /**
         * @brief Resituisce l'i-esima stazione
         * 
         * @param i 
         * @return Station& 
         */
        Station& get_station(int i) const;

        /**
         * @brief Restituisce la stazione principale successiva
         * 
         * @param this_principal_index 
         * @return Station& 
         */
        Station& get_next_principal(int this_principal_index) const;

        /**
         * @brief restituisce il file contenente le informazioni sulla tratta
         * 
         * @return std::string 
         */
        std::string get_source_file_name() const;

        /**
         * @brief Restituisce la lunghezza totale della tratta in km
         * 
         * @return int 
         */
        int get_railway_length() const;

        /**
         * @brief Restituisce il numero di stazioni presenti nella tratta
         * 
         * @return int 
         */
        int get_station_count() const;

        /**
         * @brief Restituisce il numero di stazioni pricipali presenti nella tratta
         * 
         * @return int 
         */
        int get_principal_count() const;

        /**
         * @brief Restiuisce l'indice di una stazione principale relativo alle sole stazioni principali
         * 
         * @param this_pricipal_index indice relativo a tutte le stazioni
         * @return int 
         */
        int principal_index(int this_pricipal_index) const;

        /**
         * @brief Controlla l'esistenza di una railway inversa
         * 
         * @return true 
         * @return false 
         */
        bool has_reverse();

        /**
         * @brief Restuisce un puntatore alla railway inversa (se esiste, altrimenti è nullptr)
         * 
         * @return Railway* 
         */
        Railway* get_reverse_reference();

        /**
         * @brief Restituisce un puntatore alla TimeTable relativa
         * 
         * @return TimeTable* 
         */
        TimeTable* get_timetable_reference();

        /**
         * @brief Imposta il riferimento alla railway inversa
         * 
         * @param ref 
         */
        void set_reverse_railway(Railway* ref);

        /**
         * @brief Distanza minima fra due stazioni affinche siano valide
         * 
         */
        static constexpr int MIN_STATION_DISTANCE = 20;

    private:
        
        std::vector<std::unique_ptr<Station>> stations;
        
        std::string line_description_file_name;

        Railway* reverse_railway {nullptr};
        
        TimeTable* reference_to_TimeTable;
};

/**
 * @brief overload operatore di output per Railway
 * 
 * @param os 
 * @param rw 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, Railway& rw);

#endif //Railway_h