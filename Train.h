

class Train{
    public:
        Train(const Train&) = delete;
        Train& operator=(const Train&) = delete;
        //ci va? non utilizzo memoria nel freespace attualmente...
        virtual ~Train(){}
        
        virtual int get_number() const;
        //non sono certo che l'=0 serva per cio che lo intendo io (da discutere)
        virtual int get_type() const = 0; 
        virtual void set_delay(int _delay) = 0;
        virtual int get_delay() const = 0;
        virtual void set_speed(int _speed) = 0;
        virtual int get_speed() const = 0;
        

    protected:
        Train() { }

    private:
        int speed; //velocità di crociera
        int number; //numero del treno
        int delay; //ritardo? lo deve sapere il treno o verrà gestito altrove?
};

class Regional : public Train{
    public:
        Regional(int _number);

        int get_number() const;
        int get_type() const; 
        void set_delay(int _delay);
        int get_delay() const;
        void set_speed(int _speed);
        int get_speed() const;

    private:
        int speed; 
        int number; 
        int delay; 
        static constexpr int MAXSPEED = 160;


};

class HighSpeed : public Train{
    public:
        HighSpeed(int _number);
        int get_number() const;
        int get_type() const; 
        void set_delay(int _delay);
        int get_delay() const;
        void set_speed(int _speed);
        int get_speed() const;

    private:
        int speed; 
        int number; 
        int delay; 
        static constexpr int MAXSPEED = 240;
        
};

class SuperHighSpeed : public Train{
    public:
        SuperHighSpeed(int _number);
        int get_number() const;
        int get_type() const; 
        void set_delay(int _delay);
        int get_delay() const;
        void set_speed(int _speed);
        int get_speed() const;

    private:
        int speed; 
        int number;
        int delay;
        static constexpr int MAXSPEED = 300;
        
};