#pragma once
#include <string>
#include <vector>

using namespace std;



struct room{
    string roomNo;
    vector<pair<string,int>> macID_SignalStrength;    
    int guessScore;
};

class dataset{
    private:
    vector<room> Rooms;
    
    public:
    void setDatafromFiles();
    vector<room> returnDataFromFiles();

};