#include <windows.h>

#include <iostream>
#include <vector>
#include "Train.h"


using namespace std;


void print(Regional& a, HighSpeed& b, SuperHighSpeed& c, HANDLE&  hConsole){
    
    a.step();
    b.step();
    c.step();

    SetConsoleTextAttribute(hConsole, 14);
    cout << a << endl;
    SetConsoleTextAttribute(hConsole, 3);
    cout << b << endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout << c;
    SetConsoleTextAttribute(hConsole, 15);
}

void test(vector<Train*> &v){
    Regional* r = new Regional(10);
    v.push_back(r);
}


int main(int argc, char const *argv[])
{

    vector<Train*> v;
    test(v);

    cout << *v[0];

    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int counter = 0;
    
    Regional reg = Regional(0);
    HighSpeed hs = HighSpeed(1);
    SuperHighSpeed shs = SuperHighSpeed(2);
    shs.park(-1);
    print(reg,hs,shs, hConsole);


    reg.set_speed(80);
    
    for(int i = 0; i < 18; i++){

        cout << "----    Cycle " << i << "    ----\n"; 
        
        if(reg.next_distance() - 10 < hs.get_distance() && counter == 1 && !reg.parked())
            hs.set_speed(reg.get_speed());

        if(reg.get_distance() > 5 && counter == 0){
            reg.set_speed(300); //set max speed
            counter++;
        }
        if(reg.next_distance() > hs.get_distance() + 10 && counter == 1){
            hs.set_speed(80);
            counter++;
        }
        if(hs.get_distance() > 5 && counter == 2){
            hs.set_speed(300);
            counter++;
        }
        if(reg.next_distance() > 20 && counter == 3){
            counter++;
            reg.park(20);
        }
        if(hs.next_distance() > 25 && counter == 4){
            hs.stop(25);
            counter++;
        }
        if(hs.stationary()){
            reg.set_speed(80);
        }
        if(reg.next_distance() > 25)
            reg.stop(25);


        print(reg,hs,shs, hConsole);
        cout << "_______________________________________________________________\n";
        cin.get();
    }
    
    
    

    SetConsoleTextAttribute(hConsole, 15);

    return 0;

}
