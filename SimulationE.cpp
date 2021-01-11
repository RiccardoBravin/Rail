#include "Simulation.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>


using namespace std;

void Simulation::sort_trains() {
    for(int i=0; i<trains.size(); i++) {
        vector<unique_ptr<Train>> replacer;
        while(trains[i].size() > 0) {
            int min_index {0};
            for(int j=0; j<trains[i].size(); j++) {
                if(trains[i][min_index]->get_distance() > trains[i][j]->get_distance())
                    min_index = j;
            }
            replacer.push_back(move(trains[i][min_index]));
            trains[i].erase(trains[i].begin() + min_index);
        }
        trains[i] = replacer;
    }
}