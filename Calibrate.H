#pragma once 
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>

using namespace std;

struct macID_signalStrength{
    string macAddresses; // create a struct that stores the mac address with the realted signal strength.
    vector<int> signalStrengths;

};


class Calibrator{
    public:
    vector<macID_signalStrength> sortData(filesystem::path path);
    vector<macID_signalStrength> calibrateData(vector<macID_signalStrength> x);
    void createStandardisedFile(vector<macID_signalStrength> data);
    void calibrate();


};