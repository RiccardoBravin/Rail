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
            Principal, 
            Secondary 
        };

        Station (const Station&) = delete;
        Station& operator=(const Station&) = delete;

        /**
         * @brief Get the station name 
         * 
         * @return std::string 
         */
        std::string get_name() const;

        /**
         * @brief Get the station distance
         * 
         * @return int 
         */
        double get_distance() const;

        /**
         * @brief Get the station type Secondary Station == 1 || Principal == 0
         * 
         * @return int 
         */
        virtual int get_type() const = 0;

        /**
         * @brief Add one train to the vector<train> (parking)
         * 
         * @param t - use vector parking
         */
        void add_train_to_park(Train* t);
                
        /**
         * @brief Get the parking train object
         * 
         * @return std::vector<Train> 
         */
        std::vector<Train*> get_parking_train() const;

        /**
         * @brief Get the stop train object
         * 
         * @return std::vector<Train*> 
         */
        std::vector<Train*> get_stop_train() const;

         /**
         * @brief Get the count parking train object
         * 
         * @return int 
         */
        int get_count_parking_train() const;

        /**
         * @brief Asks if the train is in the park
         * 
         * @return true 
         * @return false 
         */
        bool train_in_park(Train* ) const;

        /**
         * @brief Remove one train from the parking
         * 
         * @param t  - use vector parking
         */
        void remove_train_from_park(Train* t);

        /**
         * @brief Asks if can add a train on the stop platform
         * 
         * @return true 
         * @return false 
         */
        bool can_add_train_to_stop() const;
        
       /**
        * @brief Add train to stop platform
        * 
        * @param t 
        * @return true 
        * @return false 
        */
        bool add_train_to_stop(Train* t);   

        /**
         * @brief Returns the platform number (1 or 2) where the train is stopped or 0 
         * 
         * @param t - train 
         * @return int 1 or 2 or 0
         */
        int what_platform_train(Train* t);
        
        /**
         * @brief Remove train to stop track
         * 
         * @param t 
         */
        bool remove_train_to_stop( Train* t);

        /**
         * @brief Get the count in stop trains 
         * 
         * @return int 
         */
        int get_count_in_stop_train() const; 

        /**
         * @brief Get the stop tracks object
         * 
         * @return int 
         */
        int get_stop_tracks() const;

        /**
         * @brief Get the count in stop transit
         * 
         * @return int 
         */
        virtual int get_count_in_transit_train() const = 0;

        /**
         * @brief Add train to transit track
         * 
         * @param t 
         */
        virtual void add_train_to_transit(Train* t) = 0;

        /**
         * @brief Asks if can add a train on the stop transit
         * 
         * @return true 
         * @return false 
         */
        virtual bool can_add_train_to_transit() const = 0;

        /**
         * @brief Remove train from transit track
         * 
         */
        virtual void remove_train_from_transit() = 0;

        /**
         * @brief Set the Discance object
         * 
         * @param d 
         */
        void set_distance(const double d);

        /**
         * @brief Destroy the Station object
         * 
         */
        virtual ~Station(){};

        static constexpr int N_STOP_TRACK = 2;

    protected:
        Station() {};
        std::string name; 
        double distance;
        std::vector<Train*> parking;     
        std::vector<Train*> transit_tracks;
        std::vector<Train*> stop_tracks;
        
    private:
       
};


class Secondary : public Station {
    public:
        Secondary(const std::string _name, const double _distance);
        Secondary(const Secondary& stn);
        Secondary& operator=(const Secondary& stn);
        Secondary(Secondary&& stn);
        Secondary& operator=(Secondary&& stn);
        ~Secondary() { }

        int get_type() const override;
        int get_count_in_transit_train() const override;
        bool can_add_train_to_transit() const override ;
        void add_train_to_transit(Train* t) override;
        void remove_train_from_transit() override;
        int get_transit_tracks() const;
        

    private: 
    static constexpr int N_TRANS_TRACK = 1; 
      
};

class Principal : public Station {

    public:
        Principal(const std::string _name, const double _distance);
        Principal(const Principal& stn);
        Principal& operator=(const Principal& stn);
        Principal(Principal&& stn);
        Principal& operator=(Principal&& stn);
        ~Principal() { }
           
        int get_type() const override;
        int get_count_in_transit_train() const override;
        bool can_add_train_to_transit() const override ;
        void add_train_to_transit(Train* t) override;
        void remove_train_from_transit() override;
        int get_transit_tracks() const;
        
    private:
    static constexpr int N_TRANS_TRACK = 0;

};

std::ostream& operator<<(std::ostream& os, const Station& stn);

bool operator == (const Station &stn1, const Station &stn2);

bool operator != (const Station &stn1, const Station &stn2);

#endif //Station_h