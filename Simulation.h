/**
 * @file Simulation.h
 * @author Bravin Riccardo
 * @brief manages the simulation of the railway
 * @version 0.1
 * @date 2021-01-11
 * 
 * @copyright Copyright (c) 2021
 */

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

        int RAILWAYS {0};   ///keeps track of the railways being simulated

        int current_time {0};   ///keeps track of the elapsed time since the start of the simulation

        std::vector<TimeTable> timetable;   ///contains the timetable of all railways
        std::vector<Railway> railway;   ///contains the stations of all railways
        std::vector<std::vector<std::unique_ptr<Train>>> trains;    ///contains the trains divided by in different railways

        int trains_at_terminal {0}; ///keeps track of the trains that got to the ending station
        
        
        /**
         * @brief calculates the delay or the advance of one train relative to the station is entering
         * 
         * @param k the index of the railway in which the train is in
         * @param tr_index the index of the train in question
         * @param st_index the index of the station he is gettin into
         * @return int the delay or advance
         */
        int calc_delay(int k, int tr_index, int st_index);

        /**
         * @brief Makes all trains that need to move from the station center start with a speed of 80 and warns the user
         * 
         * Cycles the timetables in order to create all the trains in the first station (given that they can start) and starts up all the train in
         * different stations   
         */
        void start_trains(); 

        /**
         * @brief says whether or not the station has free route to start the trains in the platform
         * 
         * @param st station where to check the condition
         * @param k the railway in which the checking needs to happen
         * @return true if it has a free path
         * @return false if it needs to not let trains start
         */
        bool free_to_start(Station* st,  int k) const;

        /**
         * @brief prints the station in which the train is getting approximately 20 km near to
         */
        void notice_20_km_mark();

        /**
         * @brief makes all the trains stay 20 kilometers apart and adjustes the speeds accordingly. Also prints their status
         */
        void check_distance();//controlla ed eventualmente sistema tutti i problemi con le distanze e velocità fra tutti i treni 
        

        /**
         * @brief checks if a train is gone out of a station area, sets his speed accordingly and prints the status of the train and the station 
         * 
         */
        void exit_station();

        /**
         * @brief checks if a train is getting into a station area and acts accordingly
         * 
         * If a train is advance then it parks it, if it is slowing down trains it makes it wait in the parking lot and if it needs to transit then
         * if it's reasonable it lets it go
         * 
         */
        void in_station();          
        
        
        /**
         * @brief if a train needs to start and it is the best choice for that station it says that it can go
         * 
         * @param st station from where the train whants to leave
         * @param t train that wants to leave
         * @return true the train is the best choice to let start
         * @return false the train should let another go first
         */
        bool best_train_in_station(Station* st, Train* t);

        /**
         * @brief decides for each train in the parking lots if they need to stay or go in order to minimize delay
         */
        void parked_trains();


        /**
         * @brief gives the index of the best choice in a specified parking lot
         * 
         * @param k the index of the railway in which the station is contained
         * @param st_index the index of the station in which it needs to look for
         * @return int the index of the train in the same railway
         */
        int best_train_in_park(int k, int st_index);


        /**
         * @brief gives the index of the best choice in a specified parking lot just between the regional trains
         * 
         * @param k the index of the railway in which the station is contained
         * @param st_index the index of the station in which it needs to look for
         * @return int the index of the train in the same railway
         */
        int best_regional_in_park(int k , int st_index);

        /**
         * @brief finds the nearest train that is behind the specified train that is not parked or inside a station  
         * 
         * @param k the index of the railway in which the train is contained
         * @param tr_index the index of the train 
         * @return int the index of the previous train
         */
        int prev_train_index(int k, int tr_index); 


        /**
         * @brief says whether or not it's slowing down the trains behind
         * 
         * @param k the index of the railway in which the train is contained
         * @param tr_index the index of the train 
         * @return true if it is slowing down something
         * @return false it is not slowing down something
         */
        bool slowing_down_trains(int k, int tr_index);


        //questa è la funzione magica che decide chi far passare in entrata alla stazione
        //se il ritardo di a + (a.pos - b.pos)/b.vel > (next_station.lenght/b.vel)-(next_station.lenght/b.vel)+ ritardo di b
        //allora fai procedere a altrimenti metti a nel parcheggio
        /**
         * @brief calculates with a function whether or not is convenient for the train to go for his route or wait for the train behind to pass
         * 
         * train.delay + (train.pos - train.pos)/prev_train.vel > ((station.pos - next_station.pos)/prev_train.vel)-(station.pos - next_station.pos)/b.vel)) + prev_train.delay
         * this is the function used
         * 
         * @param k the index of the railway in which to look
         * @param tr_index the index of the train 
         * @param st_index the index of the station
         * @return true if it is free to go
         * @return false if it should let the previous train pass
         */
        bool smart_train_function(int k, int tr_index, int st_index);

        /**
         * @brief stops the train that need to unload passangers
         * 
         */
        void stop_trains();

        /**
         * @brief parks the train in the station and warns the user 
         * 
         * @param st station  
         * @param tr train
         */
        void park_train(Station& st, Train* tr);
        
        /**
         * @brief removes the train from the station's parking lot and warns the user
         * 
         * @param st station  
         * @param tr train
         */
        void leave_park(Station& st, Train* tr);
        
        
        /**
         * @brief adds the train to the station's transit tack and warns the user
         * 
         * @param st station  
         * @param tr train
         */
        void add_train_transit(Station& st, Train* tr);
        
        /**
         * @brief removes the train from the station's transit tack and warns the user
         * 
         * @param st station  
         * @param tr train
         */
        void remove_train_transit(Station& st, Train* tr);

        /**
         * @brief adds the train to the station binary for unloading passengers and warns the user
         * 
         * @param st station  
         * @param tr train
         */
        void entering_station_area(Station& st, Train* tr);
        
        /**
         * @brief removes the train from the station binary and warns the user
         * 
         * @param st station  
         * @param tr train
         */
        void exiting_station_area(Station& st, Train* tr);

        
        
        /**
         * @brief removes all the trains that passed the last station from the simulation and increases the counter
         */
        void ending_station();


        /**
         * @brief checks whether or not all the trains have been simulated 
         * 
         * @return true if the simulation is done
         * @return false if the simulation has to continue
         */
        bool end_simulation();
        
        

        /**
         * @brief makes all the trains step in time and space
         */
        void step();



        /**
         * @brief function that sorts all the trains in the railway using their position relative to the railway. Required for some functions that are position specific 
         */
        void sort_trains();
};


/**
 * @brief creates a train and adds it to the vector
 * 
 * @param a the timetable element containing the data for the creation of the train
 * @param trains the vector in which to push the new train
 */
void push_front_train(const timetable_element& a, std::vector<std::unique_ptr<Train>>* trains);