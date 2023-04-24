#include "MatchingAlgorithm.h"
#include <string>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;



CurrentReading MatchingAlgorithm::getRealtimeReading(){
    CurrentReading incomingReading; // we collect the currents reading information
    string mac; // holder for the mac addresses incoming
    int signalStrength; //holder for the signal strength incominig

    string command = "sudo iwlist wlo1 scan | grep -e Address -e level > currentReading.txt"; //command we give linux to create a new file for the current reading signal coming into be stored.
    system(command.c_str()); //tell linux to run the command. Has to be casted to a cstring to work    
    ifstream iFile; //create infile to read the current reading file
    iFile.open("/home/alex/Documents/Personal project/build/currentReading.txt", ios::in); // open that file   

    string holder; //holder to read the data from file with
    while(iFile >> holder){ // while the binary value from the read is 1 that means we can read so lets read
                //The code below is the same as we use in the calibration programme so i will not explain this in great detail
                //we basicall look for text values where we know that in the next line thats where our data will lie and we take that value and store it
                if(holder == "Address:"){ 
                    iFile >> mac;
                }
                else if (holder == "Signal")
                {
                    iFile >> holder;
                    holder = holder.substr(6,3);
                    signalStrength = stoi(holder);
                    incomingReading.current_MacID_Signalstrength.push_back(make_pair(mac,signalStrength));
                    incoming_Readings.push_back(incomingReading);
                }    

    }
    
    return incomingReading; //return that incoming reading
}