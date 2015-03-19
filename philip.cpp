/*
 * Homework 6 Program, Station Channels
 * Goal: Understand how to declare and manipulate a collections of objects
 * using a arrays, enumerators, and structures
 * Author: Luke Philip Ogweno
 * 19 March 2015
 * Github account: https://github.com/PhilipOgweno/HMWORK6.git
 */
// libraries 

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <locale>

using namespace std;

//  Definining variables
// Using enum to declare months 

enum month 
          {January = 1, February, March, April,May, June, 
           July, August, September, October, November, December};

struct header {

    string EQID;
    string Date;
    string Day;
    string Year;
    string Time;
    string TimeZone;
    string EarthquakeName;
    string Lat;
    string Lon;
    string MagType;
    string Magnitude;
    string Event;
    };

struct signalInfo 

    {
    string NetCode;
    string stnName;
    string BandName;
    string InstName;
    string OrientName;
    };



// Openning Input File and checking ii it is opened correctly
void open_input(ifstream& inputFile, string inputFileName) 
{

   inputFile.open(inputFileName.c_str());

    if (inputFile.fail()) 
    {
        cout << "Error! Unable to open file for reading " << inputFileName << endl;
        exit(EXIT_FAILURE);
    }
}


// Printing the header information
void WriteHeader (int EntryNumb, string EQID, string Day, string MonthName, string Year,
                  string Time,string TimeZone, string EarthquakeName, string Lat, string Lon, 
                  string MagType, string Magnitude, string Events) 
{
    ofstream oFile;
    string oFileName = "philip.out" ;
    if (EntryNumb == 0)
       oFile.open(oFileName.c_str()); 
    else
        oFile.open(oFileName.c_str(), ofstream::out | ofstream::app);

        oFile << "# " << day << " "  << monthNmae   << " "  << year << "  "<< time1   << " " 
              << timeZone << " "     << magType     << "  " << magnitude   << " "     << earthquakeName 
              << " [" <<EQID << "] " << " (" << lat <<" , " <<lon << " "   << Enumber << ")" << endl;
}

// Print to File 
void printToFile(string EQID, int EntryNumb, string NCode, string stationName, 
                string instrumentName, string bandName, string orName) {
    
    ofstream oFile;
    string oFileName = "philip.out" ;
    if (EntryNumb > 0)
       oFile.open(oFileName.c_str(), ofstream::out | ofstream::app);
    else
       oFile.open(oFileName.c_str()); 

    for (int unsigned i = 0 ; i < orName.length(); i++) {
       oFile << EQID << "." << NCode << "."   << stationName << "." << uppercase(bandName)
             << uppercase(instrumentName)     << orName[i]   << endl;

    }
}

// Printing errors to Log file 
void WriteErrors(int EntryNumb, int validEntries, int invalidEntries, int totalSignal, 
                bool ii, bool jj, bool kk, bool ll, bool pp, bool qq, bool mm, bool nn) {

    ofstream oErrFile;
    string oFileName = "philip.log" ;
    if (EntryNumb > 0)
       oErrFile.open(oFileName.c_str(), ofstream::out | ofstream::app);
    else
       oErrFile.open(oFileName.c_str()); 

    if (ii == false) {
        oErrFile << "Entry # " << EntryNumb << " Invalid Network"    << endl;
        cout     << "Entry # " << EntryNumb << " Invalid Network"    << endl;
    }
    else if (jj == false) {
        oErrFile << "Entry # " << EntryNumb << " Invalid Station"    << endl;
        cout     << "Entry # " << EntryNumb << " Invalid Station"    << endl;
    }
    else if (kk == false) {
        oErrFile << "Entry # " << EntryNumb << " Invalid Band type"  << endl;
        cout     << "Entry # " << EntryNumb << " Invalid Band type"  << endl;
    }
    else if (ll == false) {
        oErrFile << "Entry # " << EntryNumb << " Invalid Instrument" << endl;
        cout     << "Entry # " << EntryNumb << " Invalid Instrument" << endl;
    }
    else if (pp == false) {
        oErrFile << "Entry # " << EntryNumb << " Invalid Orientation" << endl;
        cout     << "Entry # " << EntryNumb << " Invalid Orientation" << endl;
    elseif (qq == false) {
        oErrFile << "Error # Date format wrong !" << endl;
        cout     << "Error # Date format wrong !" << endl;
    }
    else if (mm == false){
        oErrFile << "Error # Either Magnitude_type or Magnitude is wrong !" << endl;
        cout     << "Error # Either Magnitude_type or Magnitude is wrong !" << endl;
    }
    else if (nn == false) {
        oErrFile << "Error # Either time format or time zone is wrong !" << endl;
        cout     << "Error # Either time format or time zone is wrong !" << endl;
    }

}








