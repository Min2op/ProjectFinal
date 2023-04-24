#include "Controller.h"
#include <iostream>
using namespace std;

void Controller::viewMenu(){
    int choice = 0;
    do 
    {
        choice = view.showMenu();
        switch(choice){
        case 1:
            model.getData(); // Load the data in from the calibrated files.
            break;
        case 2: // shows the available room data to detect yourself in
            view.showAvailableData(); 
            break;
        case 3: // this case starts the matching algorithm
            model.starReadingSignals();
            model.findRoom();
            break;
        case 4: // Calibrate the data
            model.calibrateData();
            break;
        case 5:// exites the programme;
            break;
        }
    
 


    }while (choice != 5);
 
    
}