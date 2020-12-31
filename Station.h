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
        virtual std::vector<Train> get_parking_train() const = 0;

         /**
         * @brief Get the count parking train object
         * 
         * @return int 
         */
        virtual int get_count_parking_train() const = 0;

        /**
         * @brief Remove one train from the parking
         * 
         * @param t  - use vector parking
         */
        virtual void remove_train_from_park();

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
        virtual void add_train_to_stop(Train t );

        /**
         * @brief Remove train to transit track
         * 
         * @param t 
         * 
         */
        virtual void remove_train_to_transit();
        
        /**
         * @brief Remove train to stop track
         * 
         * @param t 
         */
        virtual void remove_train_to_stop();
    
        /**
         * @brief Get the transit tracks object
         * 
         * @return int 
         */
        virtual int get_transit_tracks() const = 0;

        /**
         * @brief Get the stop tracks object
         * 
         * @return int 
         */
        virtual int get_stop_tracks() const = 0;

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

        std::string get_station_name() const override;
        int get_station_distance() const override;
        int get_station_type() const override;
        void add_train_to_park(Train t) override;
        std::vector<Train> get_parking_train() const override;
        int get_count_parking_train() const override;
        void remove_train_from_park() override;
        void add_train_to_transit(Train t) override;
        void add_train_to_stop(Train t);
        void remove_train_to_transit()override;
        void remove_train_to_stop()override;
        int get_transit_tracks() const override;
        int get_stop_tracks() const override;
        
       

    private: 
        Secondary() {};
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;
        static constexpr int N_TRANS_TRACK = 1;
        static constexpr int N_STOP_TRACK = 2;
};

class Principal : public Station {

    public:
        Principal(std::string _name, const int _distance);
        Principal(const Principal& obj);
        Principal& operator=(const Principal& obj);
        Principal(Principal&& obj);
        Principal& operator=(Principal&& obj);
        ~Principal() { }

        std::string get_station_name() const override;
        int get_station_distance() const override;
        int get_station_type() const override;
        void add_train_to_park(const Train t) override;
        std::vector<Train> get_parking_train() const override;
        int get_count_parking_train() const override;
        void remove_train_from_park() override;
        void add_train_to_transit(const Train t) override;
        void add_train_to_stop(const Train t);
        void remove_train_to_transit()override;
        void remove_train_to_stop()override;
        int get_transit_tracks() const override;
        int get_stop_tracks() const override;
        
    private: 
        Principal() {};
        std::string name; 
        int distance;
        std::vector<Train> parking;     
        std::vector<Train> transit_tracks;
        std::vector<Train> stop_tracks;
        static constexpr int N_TRANS_TRACK = 0;
        static constexpr int N_STOP_TRACK = 2;
};

std::ostream& operator<<(std::ostream& os, const Station& obj);

#endif //Station_h