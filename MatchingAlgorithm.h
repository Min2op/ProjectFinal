#pragma once
#include <vector>
#include <string>
using namespace std;

struct CurrentReading{
   vector<pair<string,int>> current_MacID_Signalstrength;
};


class MatchingAlgorithm{
    private:
    vector<CurrentReading> incoming_Readings;
    public:
    CurrentReading getRealtimeReading();

};
