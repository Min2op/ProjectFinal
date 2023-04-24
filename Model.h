#pragma once
#include "Dataset.h"
#include "MatchingAlgorithm.h"
#include <unistd.h>
#include "Calibrate.H"


class Model{
    private: 
    vector<room> Rooms;
    CurrentReading current_Reading;
    dataset data;
    MatchingAlgorithm matcher;
    Calibrator calibrate;

    public:
    void getData();
    void starReadingSignals();
    void findRoom();
    void getRroom();
    void calibrateData();

};