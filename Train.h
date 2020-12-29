//Riccardo Bravin

#include <iostream>

class Train{
    public:
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
        
                

    protected:
        Train() { } ///elemina il costruttore di default e rende inutilizzabile il costruttore esternamente

    private:
        int speed; ///velocità di crociera
        int number; ///numero del treno
        int delay; ///ritardo? lo deve sapere il treno o verrà gestito altrove?
        double distance; ///distanza dalla stazione di partenza
};

class Regional : public Train{
    public:
        Regional();
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

    private:
        int speed; 
        int number; 
        int delay; 
        double distance;
        static constexpr int MAXSPEED = 160;


};

class HighSpeed : public Train{
    public:
        HighSpeed();   
        HighSpeed(const int _number);
        HighSpeed(const HighSpeed& obj);
        HighSpeed& operator=(const HighSpeed& obj);
        HighSpeed(HighSpeed&& obj);
        HighSpeed& operator=(HighSpeed&& obj);
        ~HighSpeed() { }

        int get_number() const;
        int get_type() const; 
        void set_delay(const int _delay);
        int get_delay() const;
        void set_speed(const int _speed);
        int get_speed() const;
        void set_distance(const double _distance);
        double get_distance() const;
        double next_distance() const;

    private:
        int speed; 
        int number; 
        int delay; 
        double distance;
        static constexpr int MAXSPEED = 240;
        
};

class SuperHighSpeed : public Train{
    public:
        SuperHighSpeed();
        SuperHighSpeed(const int _number);
        SuperHighSpeed(const SuperHighSpeed &obj);
        SuperHighSpeed& operator=(const SuperHighSpeed &obj);
        SuperHighSpeed(SuperHighSpeed&& obj);
        SuperHighSpeed& operator=(SuperHighSpeed&& obj);
        ~SuperHighSpeed() { }

        int get_number() const;
        int get_type() const; 
        void set_delay(const int _delay);
        int get_delay() const;
        void set_speed(const int _speed);
        int get_speed() const;
        void set_distance(const double _distance);
        double get_distance() const;
        double next_distance() const;

    private:
        int speed; 
        int number;
        int delay;
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