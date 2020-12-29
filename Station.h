#include <iostream>
#include <vector>
#include <string>
#include "Train.h"

class Station {
    public:
        Station (const Station&) = delete;
        Station& operator=(const Station&) = delete;

        virtual void add_train_to_park(Train t);
        virtual std::vector<Train> get_parking_train();
        virtual int get_count_parking_train();
        virtual void remove_train_from_park(Train t);
        virtual int get_passing_tracks();
        virtual int get_stop_tracks();
        virtual void set_passing_tracks(int _n);
        virtual void set_stop_tracks(int _n);
        virtual std::string get_station_name() const = 0;
        virtual int get_station_distance() const = 0;
        virtual void set_station_name(const std::string _name);
        virtual void set_station_distance(const int _distance);
        virtual int get_station_type() const = 0;
        virtual ~Station(){};

    protected:
        Station() {};

    private:
        std::string name; 
        std::vector<Train> t;
        int distance;
        int passing_tracks;
        int stop_tracks;
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
        int get_passing_tracks();
        int get_stop_tracks();
        void set_passing_tracks(int _n);
        void set_stop_tracks(int _n);
        std::string get_station_name() const = 0;
        int get_station_distance() const = 0;
        void set_station_name(const std::string _name);
        void set_station_distance(const int _distance);
        int get_station_type() const = 0;
       

    private: 
        std::string name; 
        int distance;
        int passing_tracks;
        int stop_tracks;
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
        int get_passing_tracks();
        int get_stop_tracks();
        void set_passing_tracks(int _n);
        void set_stop_tracks(int _n);
        std::string get_station_name() const = 0;
        int get_station_distance() const = 0;
        void set_station_name(const std::string _name);
        void set_station_distance(const int _distance);
        int get_station_type() const = 0;

    private: 
        std::string name; 
        int distance;
        int passing_tracks;
        int stop_tracks;
        static constexpr int TYPE = 0;
};

std::ostream& operator<<(std::ostream& os, const Station& obj);