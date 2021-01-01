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
        
        virtual ~Train(){} // potrei volerlo scrivere completo oppure lasciare quello di default!!!!
        
        /**
         * @brief Get the identifying number of the train
         * @return int 
         */
        int get_number() const;
        
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
        void set_delay(const int _delay);

        /**
         * @brief Get the delay of the train
         * @return int 
         */
        int get_delay() const;

        /**
         * @brief Set the speed of the train, is limited by the max speed
         * @param _speed 
         */
        virtual void set_speed(const int _speed) = 0;
        
        /**
         * @brief Get the actual speed of the train
         * @return int 
         */
        int get_speed() const;  
        
        /**
         * @brief calculates the distance from the starting station in the next minute
         * @return the next distance as a double
         */
        double next_distance() const; 
        
        /**
         * @brief Set the distanca of a train from the starting station 
         * @param _distance 
         */
        void set_distance(const double _distance);

        /**
         * @brief Get the distance of the train from the starting station
         * @return double 
         */
        double get_distance() const;
        

        /**
         * @brief check if the train is at the station
         * @return true if is waiting at the station 
         */
        bool stationary() const;

        /**
         * @brief check if the train is parked
         * @return true if in the park
         */
        bool parked() const;

        /**
         * @brief check if the train is running
         * @return true if running
         */
        bool running() const;

        /**
         * @brief Sets the train stats to stay in the parking slot and starts the time counter  
         */
        void park(const double _distance);

        /**
         * @brief Sets the train stats to stay in the station and starts the time counter
         * 
         * @param _distance pass the position it should stop at
         */
        void stop(const double _distance);

        /**
         * @brief returns if the train is ready so start moving
         * 
         * @return true the train is not waiting for something and can start
         * @return false the train is waiting at the station and can't start
         */
        bool can_start() const;

        /**
         * @brief makes a 1 minute step in time and space
         */
        void step();


    protected:
        Train() { } ///elemina il costruttore di default e rende inutilizzabile il costruttore esternamente
        int speed; ///velocità di crociera
        int number; ///numero del treno
        int delay; ///ritardo? lo deve sapere il treno o verrà gestito altrove?
        int state; ///refer to the enum state
        int station_timer; //keeps track of the time waiting in platform
        double distance; ///distanza dalla stazione di partenza
    private:
        
        
};

class Regional : public Train{
    public:
        
        Regional(const int _number);
        Regional(const Regional& obj);
        Regional& operator=(const Regional& obj);
        Regional(Regional&& obj);
        Regional& operator=(Regional&& obj);
        ~Regional() { }

        int get_type() const override; 
        void set_speed(const int _speed) override; //forse si può rendere virtual in train, da verificare

    private:
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

       
        int get_type() const override; 
        void set_speed(const int _speed) override;

    private:
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
       
        int get_type() const override; 
        void set_speed(const int _speed) override;
        
        
    private:
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