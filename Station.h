//Author: Angelo Turris

#include <iostream>
#include <vector>
#include <string>
#include "Train.h"

class Station {
    public:
        Station (const Station&) = delete;
        Station& operator=(const Station&) = delete;

        /**
         * @brief Add one train to the vector<train> (parking)
         * 
         * @param t - use vector parking
         */
        virtual void add_train_to_park(Train t);
                
        /**
         * @brief Get the parking train object
         * 
         * @return std::vector<Train> 
         */
        virtual std::vector<Train> get_parking_train();

         /**
         * @brief Get the count parking train object
         * 
         * @return int 
         */
        virtual int get_count_parking_train();

        /**
         * @brief Remove one train from the parking
         * 
         * @param t  - use vector parking
         */
        virtual void remove_train_from_park(Train t);

        /**
         * @brief Add train to transit track 
         * 
         * @param t 
         *
        */
       virtual void add_train_to_transit(Train t);
        
        /**
         * @brief Add train to stop track
         * 
         * @param t 
         */
        virtual void add_train_to_stop(Train t);

        /**
         * @brief Remove train to transit track
         * 
         * @param t 
         * 
         */
        virtual void remove_train_to_transit(Train t);
        
        /**
         * @brief Remove train to stop track
         * 
         * @param t 
         */
        virtual void remove_train_to_stop(Train t);
    
        /**
         * @brief Get the transit tracks object
         * 
         * @return int 
         */
        virtual int get_transit_tracks();

        /**
         * @brief Get the stop tracks object
         * 
         * @return int 
         */
        virtual int get_stop_tracks();

        /**
         * @brief Get the station name 
         * 
         * @return std::string 
         */
        virtual std::string get_station_name() const = 0;

        /**
         * @brief Get the station distance
         * 
         * @return int 
         */
        virtual int get_station_distance() const = 0;

        /**
         * @brief Get the station type Secondary Station == 1 || Principal == 0
         * 
         * @return int 
         */
        virtual int get_station_type() const = 0;

        /**
         * @brief Destroy the Station object
         * 
         */
        virtual ~Station(){};

    protected:
        Station() {};

    private:
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;
};


class Secondary : public Station {
    public:
        Secondary(std::string _name, const int _distance);
        Secondary(const Secondary& obj);
        Secondary& operator=(const Secondary& obj);
        Secondary(Secondary&& obj);
        Secondary& operator=(Secondary&& obj);
        ~Secondary() { }

        void add_train_to_park(Train t);
        std::vector<Train> get_parking_train();
        int get_count_parking_train();
        void remove_train_from_park(Train t);
        void add_train_to_transit(Train t);
        void add_train_to_stop(Train t);
        void remove_train_to_transit(Train t);
        void remove_train_to_stop(Train t);
        int get_transit_tracks();
        int get_stop_tracks();
        void set_transit_tracks(int _n);
        void set_stop_tracks(int _n);
        std::string get_station_name() const;
        int get_station_distance();
        int get_station_type() const;
       

    private: 
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;
        static constexpr int N_PASS_TRACK = 1;
        static constexpr int N_STOP_TRACK = 2;
        static constexpr int TYPE = 1;
};

class Principal : public Station {

    public:
        Principal(std::string _name, const int _distance);
        Principal(const Principal& obj);
        Principal& operator=(const Principal& obj);
        Principal(Principal&& obj);
        Principal& operator=(Principal&& obj);
        ~Principal() { }

        void add_train_to_park(Train t);
        std::vector<Train> get_parking_train();
        int get_count_parking_train();
        void remove_train_from_park(Train t);
        void add_train_to_transit(Train t);
        void add_train_to_stop(Train t);
        void remove_train_to_transit(Train t);
        void remove_train_to_stop(Train t);
        int get_transit_tracks();
        int get_stop_tracks();
        void set_transit_tracks(int _n);
        void set_stop_tracks(int _n);
        std::string get_station_name() const;
        int get_station_distance();
        int get_station_type() const;

    private: 
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;
        static constexpr int N_PASS_TRACK = 1;
        static constexpr int N_STOP_TRACK = 2;
        static constexpr int TYPE = 1;
};

std::ostream& operator<<(std::ostream& os, const Station& obj);