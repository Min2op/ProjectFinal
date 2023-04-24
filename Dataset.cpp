#include "Dataset.h"
#include <fstream>
#include <filesystem>
#include <iostream>

void dataset::setDatafromFiles(){ // This is the function to read date from files
    string lineHolder, readMacAdress, readSignalStrength; // these are the pieces of text that will be used to hold the data we read    
    ifstream reader; // create an input file stream as we are reading data
    auto fileReader = filesystem::directory_iterator("/home/alex/Documents/Personal project/CalibratedRooms/"); //We create a dir iterator for the directory that contains all the calibrated data
    for(auto& entry : fileReader){ //for each file in the directory loop
        room* holderObject = new room(); // create a new room object as we are reading each rooms data
        filesystem::path F = entry; // set our file path to the current iteration of the directory to read from
        cout << F.filename() << endl; // Output the file we are reading from
        reader.open(F, ios::in); //open that file
        
        while(!reader.eof()){ // while the read does not read the end of file token then do the code below
            reader >> readMacAdress; // we know the 1st and 2nd line of our calibrated data is a mac address and its signal value so lets read that data
            reader >> readSignalStrength; // read the signal strength in that is associated to that mac address
            holderObject->macID_SignalStrength.push_back(make_pair(readMacAdress, stoi(readSignalStrength))); 
            //lets push back the mac address and associate signal reading value into the vector to store it
        }
        holderObject->roomNo = F.filename(); // The calibrated data file names are their room numbers so we know the current room no is the same as the file name
        holderObject->macID_SignalStrength.pop_back(); //
        Rooms.push_back(*holderObject); //lets push this read room into our array held in the model class 
        delete holderObject; // delete the object as we are going to need a fresh one to read the next files data from
        
        reader.close(); //close the current file
        reader.clear(); //clear the ifile stream
        //return to loop and repeat

        
    }
}

vector<room> dataset::returnDataFromFiles(){
    return Rooms;
}