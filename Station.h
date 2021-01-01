//Author: Angelo Turris

#ifndef Station_h
#define Station_h

#include <iostream>
#include <vector>
#include <string>
#include "Train.h"

class Station {
    public:

        enum type : int{
            Secondary, 
            Principal 
        };

        Station (const Station&) = delete;
        Station& operator=(const Station&) = delete;

        /**
         * @brief Get the station name 
         * 
         * @return std::string 
         */
        std::string get_station_name() const;

        /**
         * @brief Get the station distance
         * 
         * @return int 
         */
        int get_station_distance() const;

        /**
         * @brief Get the station type Secondary Station == 1 || Principal == 0
         * 
         * @return int 
         */
        virtual int get_station_type() const = 0;

        /**
         * @brief Add one train to the vector<train> (parking)
         * 
         * @param t - use vector parking
         */
        void add_train_to_park(Train& t);
                
        /**
         * @brief Get the parking train object
         * 
         * @return std::vector<Train> 
         */
        std::vector<Train> get_parking_train() const;

         /**
         * @brief Get the count parking train object
         * 
         * @return int 
         */
        virtual int get_count_parking_train() const;

        /**
         * @brief Remove one train from the parking
         * 
         * @param t  - use vector parking
         */
        virtual void remove_train_from_park();
        
        /**
         * @brief Add train to stop track
         * 
         * @param t 
         */
        void add_train_to_stop(Train& t );
        
        /**
         * @brief Remove train to stop track
         * 
         * @param t 
         */
        void remove_train_to_stop();
    
        /**
         * @brief Solo per le stazioni Secondary
         * 
         * @return int 
         * 
         * int get_transit_tracks() const;
         */
        

        /**
         * @brief Get the stop tracks object
         * 
         * @return int 
         */
        int get_stop_tracks() const;

        /**
         * @brief Destroy the Station object
         * 
         */
        virtual ~Station(){};

    protected:
        Station() {};
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;

    private:
       
};


class Secondary : public Station {
    public:
        Secondary(const std::string _name, const int _distance);
        Secondary(const Secondary& stn);
        Secondary& operator=(const Secondary& stn);
        Secondary(Secondary&& stn);
        Secondary& operator=(Secondary&& stn);
        ~Secondary() { }

        int get_station_type() const override;
        void add_train_to_park(Train& t);
        std::vector<Train> get_parking_train() const;
        int get_count_parking_train() const;
        void remove_train_from_park();
        void add_train_to_transit(Train& t);
        void add_train_to_stop(Train& t);
        void remove_train_to_transit();
        void remove_train_to_stop();
        int get_transit_tracks() const;
        int get_stop_tracks() const;

    private: 
        static constexpr int N_TRANS_TRACK = 1;
        static constexpr int N_STOP_TRACK = 2;
};

class Principal : public Station {

    public:
        Principal(const std::string _name, const int _distance);
        Principal(const Principal& stn);
        Principal& operator=(const Principal& stn);
        Principal(Principal&& stn);
        Principal& operator=(Principal&& stn);
        ~Principal() { }

        int get_station_type() const override;
        void add_train_to_park(Train& t);
        std::vector<Train> get_parking_train() const;
        int get_count_parking_train() const;
        void remove_train_from_park();
        void add_train_to_stop(Train& t);
        void remove_train_to_stop();
        int get_transit_tracks() const;
        int get_stop_tracks() const;
        
    private: 
        static constexpr int N_STOP_TRACK = 2;
};

std::ostream& operator<<(std::ostream& os, const Station& stn);

#endif //Station_h