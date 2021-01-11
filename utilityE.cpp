//author: elia feltrin

#include <iostream>
#include <string>
#include "utility.h"

using namespace std;

string mtoh(int minute) {
    int temp = minute % 1440;
    string s;
    int hour = temp/60;
    int min = temp%60;

    s = to_string(hour) + ":";
    if(min/10 == 0)
        s += "0";
    s += to_string(min);
    

    return s;
}