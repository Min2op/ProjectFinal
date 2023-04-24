#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>
#include "Calibrate.H"

using namespace std;

vector<macID_signalStrength> Calibrator::calibrateData(vector<macID_signalStrength> x){  //create a function to calulate the mean signal strength related to the mac address and return it
    for(int i = 0; i < x.size(); i++){
       double sum = 0; // this is the average we will use
       sum = accumulate(x[i].signalStrengths.begin(), x[i].signalStrengths.end(), 0); // accumalate all the signal strengths 
       sum = sum / x[i].signalStrengths.size(); // calculate the average
       x[i].signalStrengths.clear();// clear all the signal strengths as we now just have our average signal strenght which is what we need
       x[i].signalStrengths.push_back(int(sum)); // push back the standardies macID_signalStrength
    }
    return x;
}

vector<macID_signalStrength> Calibrator::sortData(filesystem::path path){
    macID_signalStrength x; //create a tempory variable to store the data we need
    ifstream iFile; // Create an input file to store our data
    string holder, newMacAddress; // create some strings to hold our information
    int newSignalStrength;  // create a temp variable for new sign strengths
    vector<macID_signalStrength> dataArr; // create an array to store all of our mac addresses and sign values.
    
    iFile.open(path, ios::in); // open file
        while(iFile >> holder){ // while being able to read from file
                
                
                if(holder == "Address:"){ // if the line we read in is a address we know that the next word will be the mac address so lets store it
                    iFile >> newMacAddress; // store the mac address
                }
                else if (holder == "Signal") //The exact same if the line is the signal then we know the next value will be the text we need to store.
                {
                    iFile >> holder;
                    holder = holder.substr(6,3); //  The last 3 characters in our text is the value we need as the dBm values in the format '-xx'
                    newSignalStrength = stoi(holder); // Convert the text to integer
                    
                    if(dataArr.empty()){ // if the array is empty we can just push back the whole value and do not need to check if the mac addresses are the same                   
                        x.macAddresses = newMacAddress;  
                        x.signalStrengths.push_back(newSignalStrength);
                        dataArr.push_back(x); // assign the data to the struct we made earlier and push it back
                    }
                    else if (!dataArr.empty()) // If the data is not empty then we have to do a check to see if the mac addresses are the same as this will happen from different readings  
                    {                         
                            for(int i = 0; i < dataArr.size(); i++ ){ // Loop through our array
                            if(newMacAddress == dataArr[i].macAddresses){ //if mac address match enter here
                                x.signalStrengths.clear(); // clear the vector of the current signal strengths so we get a clean set
                                dataArr[i].signalStrengths.push_back(newSignalStrength); // push back the new signal value with its respecitve mac address
                                break; // break out
                            }
                            else if(i == dataArr.size() -1){ // if we are at the end of the loop then we knoew we have a new mac address so lets add that to our array
                                x.signalStrengths.clear(); // clear the signal strengths as we dont want to assign it all the old ones 
                                x.macAddresses = newMacAddress; // assign new values
                                x.signalStrengths.push_back(newSignalStrength);
                                dataArr.push_back(x); //push back that new mac address into our array
                                }

                        }
                    }                
                }
                if(iFile.eof()){
                    iFile.close(); // if we reach end of the file close it
                }
            }
               

            dataArr = calibrateData(dataArr);  // calculate mean of signal values using the calibrate Data function that returns an array we pass
            for(int p = 0; p < dataArr.size(); p++){ //outputs the data
                    cout << dataArr[p].macAddresses << endl;
                    for(int k = 0; k < dataArr[p].signalStrengths.size(); k++){
                        cout << dataArr[p].signalStrengths[k] << endl;
                    }
            }
            return dataArr; //return our array

}

void Calibrator::createStandardisedFile(vector<macID_signalStrength> data){ //function that creates a new file with normalised data
    string fileName; 
    cout << "Please enter the name of the calibrated data file: " << endl;
    cin >> fileName;
    //take file name and store it
    ofstream outFile;
    fileName = "/home/alex/Documents/Personal project/CalibratedRooms/" + fileName;
    outFile.open(fileName, ios::out);  
    for(int i = 0; i < data.size(); i++){
        outFile << data[i].macAddresses; 
        outFile << endl;
        outFile << data[i].signalStrengths[0];
        outFile << endl;
        //Store all of our data into the file
    }   
}

void Calibrator::calibrate(){
    int choice = 0;
    vector<filesystem::path> filepaths; //We create a vector to store all the uncalibrated files 
    vector<macID_signalStrength> standaradisedData; // we create a standardised piece ofdata
    cout << " Welcome to the Calibration programme " << endl;
    cout << "Please select the file you want to calibrate from " << endl;

    auto fileReader = filesystem::directory_iterator("/home/alex/Documents/RoomData/CalibrationData/"); // create a dir iteratort for looping our directory
    int i = 1;
    
    for(auto& entry : fileReader){ //loops over files in our uncalibrated folder
        
        filesystem::path F = entry; //create a temp path to push back
        cout << i << ": " << F.filename() << endl; 
        filepaths.push_back(F);// push the file back
        i++;
    
    }
    cin >> choice;
    standaradisedData = sortData(filepaths[choice - 1]); // they choose which file to calibrate
    createStandardisedFile(standaradisedData); // create the new standardiesd file with the calibratedData.

}