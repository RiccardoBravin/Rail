#include "Station.h"
#include <string>
#include <memory>
#include "Train.h"

using namespace std;

void print_tr(vector<unique_ptr<Train>>& tr);
void print_st(vector<unique_ptr<Station>>& st);

bool in_station(Train* t, Station* s);

bool at_stop(Train* t, Station* s);

bool passing_at(Train* t, double dist);

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
    /*tr.push_back(unique_ptr<SuperHighSpeed>(new SuperHighSpeed(3)));
    tr.push_back(unique_ptr<SuperHighSpeed>(new SuperHighSpeed(4)));*/


    st.push_back(unique_ptr<Principal>(new Principal("Sacile", 0)));
    st.push_back(unique_ptr<Principal>(new Principal("Pordenone", 20)));
    st.push_back(unique_ptr<Secondary>(new Secondary("Codroipo", 46)));
    st.push_back(unique_ptr<Principal>(new Principal("Trieste", 150)));

    for(unique_ptr<Train> &t : tr){
        st[0].get()->add_train_to_stop(t.get());
        t.get()->set_speed(80);
    }

    tr[2].get()->park(0);
    tr[1].get()->stop(0);
    cout << "\n\n";

    print_tr(tr);

    print_st(st);


    //tr[0].get()->set_speed(900);
    unsigned cycle;
    while(!tr.empty()){
        
        if(cycle == 15){
            tr[2].get()->set_speed(80);
            st[0].get()->add_train_to_stop(tr[2].get());
        }
        cout << "~~~~~~  Cycle " << cycle << "   ~~~~~~\n";
        
        step(tr,st);
        print_tr(tr);
        print_st(st);
        

        cycle++;
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

bool in_station(Train* t, Station* s){
    if(t->next_distance() > s->get_station_distance() - 5  && t->next_distance() < s->get_station_distance() + 5)
        return true;
    return false;
}

bool at_stop(Train* t, Station* s){
    if(t->get_distance() < s->get_station_distance() && t->next_distance() >= s->get_station_distance())
        return true;
    return false;
}

bool passing_at(Train* t, double dist){
    if(t->get_distance() < dist && t->next_distance() >= dist)
        return true;
    return false;
}


bool crash(Train* t1, Train* t2){
    if(t1 == t2)
        return false;
    if(t1->parked() || t2->parked() || t1->stationary() || t2->stationary())
        return false;
    if(t1->get_distance() > t2->get_distance() - 10 && t1->get_distance() < t2->get_distance())
        return true;
    return false;
}


void step(vector<unique_ptr<Train>> &tr, vector<unique_ptr<Station>>& st){
    for(int i = 0; i < tr.size(); i++){
        
        for(unique_ptr<Station> &s : st){ //per ogni stazione
            if(tr[i].get()->get_type() == Train::Regional){ //se sei un regionale te le fai tutte le stazioni
                //se arrivi alla stazione allora fermati
                if(at_stop(tr[i].get(), s.get())){
                    tr[i].get()->stop(s.get()->get_station_distance());
                    break;
                }
                //se sei in zona stazione devi andare ad 80 
                if(in_station(tr[i].get(), s.get()) && !tr[i].get()->parked())
                    tr[i].get()->set_speed(80);
                
                //se stai entrando controlla se puoi transitare
                if(passing_at(tr[i].get(), s.get()->get_station_distance()-5)){
                    if(s.get()->add_train_to_stop(tr[i].get())){
                        //tr[i].get()->set_speed(80); //teoricamente non serirebbe nemmeno
                    }
                    else{
                        s.get()->add_train_to_park(tr[i].get());
                        tr[i].get()->park(s.get()->get_station_distance() - 5);
                    }
                    break;
                }

                if(passing_at(tr[i].get(), s.get()->get_station_distance() + 5)){
                    s.get()->remove_train_to_stop(tr[i].get());
                    tr[i].get()->set_speed(900);
                    break;     
                }
                

            }else if(tr[i].get()->get_type() == Train::HighSpeed || tr[i].get()->get_type() == Train::SuperHighSpeed){ //se non sei regional fai solo principal
                
                if(s.get()->get_station_type() == Station::Principal){
                    //se arrivi alla stazione allora fermati
                    if(at_stop(tr[i].get(), s.get())){
                        tr[i].get()->stop(s.get()->get_station_distance());
                        break;
                    }
                    //se sei in zona stazione devi andare ad 80 
                    if(in_station(tr[i].get(), s.get()))
                        tr[i].get()->set_speed(80);

                    //se stai entrando controlla se puoi transitare
                    if(passing_at(tr[i].get(), s.get()->get_station_distance()-5)){
                        if(s.get()->add_train_to_stop(tr[i].get())){
                            //tr[i].get()->set_speed(80); //teoricamente non serirebbe nemmeno
                        }
                        else{
                            s.get()->add_train_to_park(tr[i].get());
                            tr[i].get()->park(s.get()->get_station_distance() - 5);
                        }
                        break;
                    }

                    if(passing_at(tr[i].get(), s.get()->get_station_distance() + 5)){
                        s.get()->remove_train_to_stop(tr[i].get());
                        tr[i].get()->set_speed(900);
                        break;     
                    }

                    /*bool ok = true;
                    for(unique_ptr<Train> &t : tr){
                        if(crash(tr[i].get(), t.get())){
                            tr[i]->set_distance(t->get_distance() - 10);
                            tr[i]->set_speed(t->get_speed());
                            ok = true;
                            break;
                        }
                    }
                    if(ok)
                        tr[i].get()->set_speed(900);
                    */

                }
            }
        }
        

        tr[i].get()->step();

        if(tr[i].get()->get_distance() > st.back().get()->get_station_distance()){
            st.back().get()->remove_train_to_stop(tr[i].get());
            tr.erase(tr.begin()+i);
        }
    }
}   