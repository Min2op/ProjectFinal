#include "View.h"
#include <iostream>
#include <fstream>
#include <filesystem>


using namespace std;

int View::showMenu(){ // main view of the programme.
    int choice = 0; // holds the choice for the menu option variable
    do
    {
        
        cout << "***************************" << endl;
        cout << " Welcome To the Main Menu " << endl;
        cout << "***************************" << endl;
        cout << "1. Load Room Data from Files " << endl;
        cout << "2. Check Amount of Room Data " << endl;
        cout << "3. Start matching Algorithm  " << endl;
        cout << "4. Calibrate data            " << endl;
        cout << "5. Exit the programme        " << endl;
        cout << "**************************** " << endl;
        cout << "**************************** " << endl;
        
        cin >> choice;
        return choice;  //return the users menu choice.   
    }while (choice != 5); // do this while we dont want to exit the programme
   
   
}

void View::showAvailableData(){ // show the the rooms you can be detected in
    cout << "Here are all the rooms you can be found in" << endl; 
    auto dirIterator = filesystem::directory_iterator("/home/alex/Documents/Personal project/CalibratedRooms/"); //loop through the directory of our calibrated data
    for(auto& entry: dirIterator){ //for each loop for files in directory
        filesystem::path currFile = entry; // make a file path and set the current directory to it.
        cout << "Room " << currFile.filename() << endl; // output the file name of the file path.
    }
}

