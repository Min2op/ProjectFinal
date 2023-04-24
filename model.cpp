#include "Model.h"
#include <iostream>
#include <string>

using namespace std;

void Model::getData(){
    data.setDatafromFiles();
    Rooms = data.returnDataFromFiles();
}

void Model::starReadingSignals(){
    current_Reading = matcher.getRealtimeReading();
}

void Model::findRoom(){
    
    for(int i = 0; i < Rooms.size(); i++){ // Loop through all the rooms we have current in our rooms vector
        for(int k = 0; k < current_Reading.current_MacID_Signalstrength.size(); k++){ //then lopp through the total amount of mac addresses and signal values we just read
                for(int j = 0; j < Rooms[i].macID_SignalStrength.size(); j++){ //Then we have to loop through each rooms data set of mac addresses and signal values to compare 
                    if(current_Reading.current_MacID_Signalstrength[k].first == Rooms[i].macID_SignalStrength[j].first){ // if statement to find matching mac addresses
                        cout << "sniffing " << endl;
                        cout << "Current read mac address: " << current_Reading.current_MacID_Signalstrength[k].first << endl;
                        cout << "Mac address from historical data: " << Rooms[i].macID_SignalStrength[j].first << endl;
                        if(current_Reading.current_MacID_Signalstrength[k].second == Rooms[i].macID_SignalStrength[j].second){ //check to see if the signal value read from the current reading and historical data match for that room
                                ++Rooms[i].guessScore; // If the signal values for the current signal reading matches the respective signal value in the data set for that room increase the score value for the room
                        }
                        else if((current_Reading.current_MacID_Signalstrength[k].second - Rooms[i].macID_SignalStrength[j].second <= 3) && 
                                (current_Reading.current_MacID_Signalstrength[k].second - Rooms[i].macID_SignalStrength[j].second >= -3)){
                                ++Rooms[i].guessScore;
                                // This state does the same as the other if but instead of an exact value match for the signal reading we use a range of six. 
                        }
                    }
                }
            }
        } 
            getRroom(); //Once we have read all the data and incremented the scores we can then call the get room function to return the room with the highest guess score
        }

void Model::getRroom(){
    string guessedRoom; // hold the string that we are going to store the guessed room in
    int biggest = 0; // create value to hold the guess score of each room
    for(int i=0; i < Rooms.size(); i++){ // loop through rooms finds biggest guess score and we return that
        if(Rooms[i].guessScore > biggest){ 
           biggest =  Rooms[i].guessScore;
           guessedRoom = Rooms[i].roomNo; 
           
        }
    }
    string outputCommand; 
    cout << "We guess that you are in the room " << guessedRoom << " with the score " << biggest << endl; //output the room guessed
    outputCommand = "toilet -F border -F metal " + guessedRoom;
    system(outputCommand.c_str());
}

void Model::calibrateData(){
    calibrate.calibrate();
}