//Author: Riccardo Bravin

#ifndef Train_h
#define Train_h

#include <iostream>

class Train{
    public:

        enum state : int{
            Running, 
            Parked, 
            Stationary
        };

        enum type : int{
            Regional,
            HighSpeed,
            SuperHighSpeed
        };

        Train(const Train&) = delete;
        Train& operator=(const Train&) = delete;
        //ci va? non utilizzo memoria nel freespace attualmente...
        virtual ~Train(){}
        
        /**
         * @brief Get the identifying number of the train
         * @return int 
         */
        virtual int get_number() const = 0;
        
        /**
         * @brief Get the type of train that is being called upon
         * @return int 
         * 
         * @warning Vorrei che questa funzione potesse essere statica per i figli dato che non varia per ogni oggetto  
         */
        //non sono certo che l'=0 serva per cio che lo intendo io (da discutere)
        virtual int get_type() const = 0; 
        
        /**
         * @brief Set the delay of the train
         * @param _delay to set
         */
        virtual void set_delay(const int _delay) = 0;

        /**
         * @brief Get the delay of the train
         * @return int 
         */
        virtual int get_delay() const = 0;

        /**
         * @brief Set the speed of the train, is limited by the max speed
         * @param _speed 
         */
        virtual void set_speed(const int _speed) = 0;
        
        /**
         * @brief Get the actual speed of the train
         * @return int 
         */
        virtual int get_speed() const = 0;  
        
        /**
         * @brief calculates the distance from the starting station in the next minute
         * @return the next distance as a double
         */
        virtual double next_distance() const = 0; 
        
        /**
         * @brief Set the distanca of a train from the starting station 
         * @param _distance 
         */
        virtual void set_distance(const double _distance) = 0;

        /**
         * @brief Get the distance of the train from the starting station
         * @return double 
         */
        virtual double get_distance() const = 0;
        

        /**
         * @brief check if the train is at the station
         * @return true if is waiting at the station 
         */
        virtual bool stationary() const = 0;

        /**
         * @brief check if the train is parked
         * @return true if in the park
         */
        virtual bool parked() const = 0;

        /**
         * @brief check if the train is running
         * @return true if running
         */
        virtual bool running() const = 0;

        /**
         * @brief Sets the train stats to stay in the parking slot and starts the time counter  
         */
        virtual void park(const double _distance) = 0;

        /**
         * @brief Sets the train stats to stay in the station and starts the time counter
         * 
         * @param _distance pass the position it should stop at
         */
        virtual void stop(const double _distance) = 0;

        /**
         * @brief returns if the train is ready so start moving
         * 
         * @return true the train is not waiting for something and can start
         * @return false the train is waiting at the station and can't start
         */
        virtual bool can_start() const = 0;

        /**
         * @brief makes a 1 minute step in time and space
         */
        void step();


    protected:
        Train() { } ///elemina il costruttore di default e rende inutilizzabile il costruttore esternamente

    private:
        int speed; ///velocità di crociera
        int number; ///numero del treno
        int delay; ///ritardo? lo deve sapere il treno o verrà gestito altrove?
        int state; ///refer to the enum state
        int station_timer; //keeps track of the time waiting in platform
        double distance; ///distanza dalla stazione di partenza

};

class Regional : public Train{
    public:
        
        Regional(const int _number);
        Regional(const Regional& obj);
        Regional& operator=(const Regional& obj);
        Regional(Regional&& obj);
        Regional& operator=(Regional&& obj);
        ~Regional() { }

        int get_number() const override;
        int get_type() const override; 
        void set_delay(const int _delay) override;
        int get_delay() const override;
        void set_speed(const int _speed) override;
        int get_speed() const override;
        void set_distance(const double _distance) override;
        double get_distance() const override;
        double next_distance() const override;

        bool stationary() const override;
        bool parked() const override;
        bool running() const override;
        void park(const double _distance) override;
        void stop(const double _distance) override;
        bool can_start() const override;

        void step();

    private:
        Regional(){}
        int speed; 
        int number; 
        int delay; 
        int state; 
        int station_timer;
        double distance;
        static constexpr int MAXSPEED = 160;


};

class HighSpeed : public Train{
    public:
           
        HighSpeed(const int _number);
        HighSpeed(const HighSpeed& obj);
        HighSpeed& operator=(const HighSpeed& obj);
        HighSpeed(HighSpeed&& obj);
        HighSpeed& operator=(HighSpeed&& obj);
        ~HighSpeed() { }

        int get_number() const override;
        int get_type() const override; 
        void set_delay(const int _delay) override;
        int get_delay() const override;
        void set_speed(const int _speed) override;
        int get_speed() const override;
        void set_distance(const double _distance) override;
        double get_distance() const override;
        double next_distance() const override;

        bool stationary() const override;
        bool parked() const override;
        bool running() const override;
        void park(const double _distance) override;
        void stop(const double _distance) override;
        bool can_start() const override;

        void step();

    private:
        HighSpeed(){}
        int speed; 
        int number; 
        int delay; 
        int state; 
        int station_timer;
        double distance;
        static constexpr int MAXSPEED = 240;
        
};

class SuperHighSpeed : public Train{
    public:
        //costruttori e distruttori
        SuperHighSpeed(const int _number);
        SuperHighSpeed(const SuperHighSpeed &obj);
        SuperHighSpeed& operator=(const SuperHighSpeed &obj);
        SuperHighSpeed(SuperHighSpeed&& obj);
        SuperHighSpeed& operator=(SuperHighSpeed&& obj);
        ~SuperHighSpeed() { }

        //getter e setter
        int get_number() const override;
        int get_type() const override; 
        void set_delay(const int _delay) override;
        int get_delay() const override;
        void set_speed(const int _speed) override;
        int get_speed() const override;
        void set_distance(const double _distance) override;
        double get_distance() const override;
        double next_distance() const override;

        //funzioni pubbliche
        bool stationary() const override;
        bool parked() const override;
        bool running() const override;
        void park(const double _distance) override;
        void stop(const double _distance) override;
        bool can_start() const override;

        void step();

    private:
        SuperHighSpeed(){}
        int speed; 
        int number; 
        int delay; 
        int state; 
        int station_timer;
        double distance;
        static constexpr int MAXSPEED = 300;

};

/**
 * @brief Print used for debugging
 * @param os 
 * @param obj 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Train& obj);


#endif //Train_h