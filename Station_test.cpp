#include "Station.h"
#include <string>
#include "Train.h"

using namespace std;

void print_tr(vector<unique_ptr<Train>>& tr);
void print_st(vector<unique_ptr<Station>>& st);

void step(vector<unique_ptr<Train>> &tr, vector<unique_ptr<Station>>& st);

int main() {
    /*string s = "Sacile";
    Principal test_principal = Principal(s, 10);
    string p = "Mirano";
    Secondary test_secondary = Secondary(p, 25);
    Regional reg = Regional(0);
    Regional reg1 = Regional(1);
    Regional reg2 = Regional(2);
    Regional reg3 = Regional(3);
    Regional reg4 = Regional(4);
    test_principal.add_train_to_park(reg);
    test_principal.add_train_to_stop(reg1);
    test_principal.add_train_to_stop(reg2);
    bool b = (test_principal != test_secondary);
    if(b == true)
        cout << "Sono uguali" << endl;
    else 
        cout << "Sono diverse"<< endl;
    
    cout << test_principal.get_station_type()<< endl;
    cout << test_secondary.get_station_type() << endl; 
    cout << test_principal << endl;
    test_principal.remove_train_to_stop();
    test_principal.can_add_train_to_stop();
    test_principal.add_train_to_stop(reg3);
    test_principal.remove_train_to_stop();
    test_principal.remove_train_to_stop();
    cout << test_principal<< endl; */




    

    vector<unique_ptr<Train>> tr;
    vector<unique_ptr<Station>> st;

    tr.push_back(unique_ptr<Regional>(new Regional(0)));
    tr.push_back(unique_ptr<HighSpeed>(new HighSpeed(1)));
    tr.push_back(unique_ptr<Regional>(new Regional(2)));
    tr.push_back(unique_ptr<SuperHighSpeed>(new SuperHighSpeed(3)));
    tr.push_back(unique_ptr<SuperHighSpeed>(new SuperHighSpeed(4)));


    st.push_back(unique_ptr<Principal>(new Principal("Sacile", 0)));
    st.push_back(unique_ptr<Principal>(new Principal("Pordenone", 20)));
    st.push_back(unique_ptr<Secondary>(new Secondary("Codroipo", 46)));
    st.push_back(unique_ptr<Principal>(new Principal("Trieste", 150)));

    print_tr(tr);

    print_st(st);


    tr[0].get()->set_speed(900);

    while(!tr.empty()){
        step(tr,st);
        print_tr(tr);

    }
    
}

void print_tr(vector<unique_ptr<Train>>& tr){
    for(unique_ptr<Train> &x : tr){
        cout << *x.get() << endl;
    }

    cout << endl;

}

void print_st(vector<unique_ptr<Station>>& st){
    for(unique_ptr<Station> &x : st){
        cout << *x.get() << endl;
    }

    cout << endl;
}

void step(vector<unique_ptr<Train>> &tr, vector<unique_ptr<Station>>& st){
    for(unique_ptr<Train> &x : tr){


        x.get()->step();
        for(unique_ptr<Station> &s : st)
            if(x.get()->get_distance() >)
    }
}