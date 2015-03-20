/*
 * Homework 6 Program, Stn Channels
 * Goal: Learning basic concepts about software design by re-doing Homework5
 * using a arrays, enumerators, and structures
 * Author: Luke Philip Ogweno
 * 19 March 2015
 * Github account: https://github.com/PhilipOgweno/HMWORK6.git
 */
 //******************************************************************************
// External Libraries

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <fstream>
#include <iomanip>
#include <locale>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

// Global Variables

string iFileName, oFilename = "philip.out", logfilename = "philip.log", message;
int flag;

// Defining Struct

struct earthquake 
{
    string Event_ID;
    string Date;
    string Time;
    string Time_Zone;
    string EqkName;
    string Lon;
    string Lat;
    string depth;
    string Mag_type_string;
    float Mag_size;
};

struct entry 
{
    string Network_Code;
    string Stn_code;
    string Band_Type;
    string Inst_Type;
    string Orient;
};

// Defining Enumerators

enum Months {January = 1, February, March, April, May, June,
     July, August, September, October, November, December};
enum Mag_type {ML, Ms, Mb, Mw };
enum Network_Code {CE, CI, FA, NP, WR };
enum Band_Type {longperiod, shortperiod, broadband };
enum Inst_Type {highgain, lowgain, accelerometer };
//******************************************************************************
// Function Prototypes

void open_input ( ifstream & );
void open_file ( string, ofstream & );
void print_file ( string, ofstream & );
void print_file ( int, ofstream & );
void Date_check ( string, ofstream & );
void Month_check ( int, ofstream & );
void Day_check ( int, ofstream & );
void Year_check ( int, ofstream & );
void Time_check ( string, ofstream & );
void Time_Zone_check ( string, ofstream & );
void Mag_Type_check ( string, ofstream & );
void Mag_size_check ( float, ofstream & );
void Signals ( ofstream &, string, string, string, string, string, string );
void Network_Code_check ( int, string, ofstream & );
void Stn_code_check ( int, string, ofstream & );
void Band_Type_check ( int, string , ofstream & );
void Inst_Type_check ( int, string, ofstream & );
//******************************************************************************
string MonthStrng ( Months );
string uppercase ( string );
string Mag_type2string ( Mag_type );
Mag_type string2_Mag_type ( string );
string Network_Code_to_string ( Network_Code );
Network_Code string2_Network_Code ( string );
string Band_Type2string ( Band_Type );
Band_Type string2_Band_Type ( string );
string Inst_Type2string ( Inst_Type );
Inst_Type string2_Inst_Type ( string );
//******************************************************************************
// Main Program starts here

int main ()

{
    // Defining Variables' Type

    string EqkName1, day, Month, year;
    string Temp, h1, h2, h3, h4, h5;
    int Numb_of_valid_entries = 0, Numb_of_input = 0, Val = 0, Numb_of_signal = 0;
    Months Month_name;

    entry Entry_Arr [ 300 ];
    entry Entry_Temp;
    earthquake header;

    // Prompt User for Input File Name.

    ifstream iFile;
    open_input ( iFile );

    // Preparing log file

    ofstream logfile;
    open_file ( logfilename, logfile );

    message = "Opening file: philip.in";
    print_file ( message, logfile );
    print_file ( "\n", logfile );
    message = "Processing input ...";
    print_file ( message, logfile );
    print_file ( "\n", logfile );

    // Reading and Checking the Header

    iFile >> header.Event_ID;
    iFile >> header.Date;   
    Date_check ( header.Date, logfile );

    // Finding and Checking the Validity of the Month

    Temp       =  Temp.append ( header.Date.begin (), header.Date.begin () + 2 );
    Val        = atoi(Temp.c_str());
    Month_check ( Val, logfile );
    Month_name = Months(Val);
    Month      = MonthStrng ( Month_name );

    // Finding and Checking the Validity of the day

    h1 =  h1.append ( header.Date.begin () + 4, header.Date.begin () + 5 );
    Val   = atoi(h1.c_str());
    Day_check ( Val, logfile );

    // Getting and Checking  Validity of the year

    h2 =  h2.append ( header.Date.begin () + 6, header.Date.end () );
    Val   = atoi(h2.c_str());
    Year_check ( Val, logfile );

    iFile >> header.Time;
    Time_check ( header.Time, logfile );
    iFile >> header.Time_Zone;
    Time_Zone_check ( header.Time_Zone, logfile );
    iFile >> header.EqkName;
    getline(iFile, EqkName1);
    header.EqkName.append ( EqkName1 ); 

    // Getting Epicenter Location

    iFile >> header.Lon;
    iFile >> header.Lat; 
    iFile >> header.depth;

    // Getting Mag Information

    iFile >> header.Mag_type_string;
    Mag_Type_check ( header.Mag_type_string, logfile );
    iFile >> header.Mag_size;
    Mag_size_check ( header.Mag_size, logfile );
    message = "Header read correctly!";
    print_file ( message, logfile );
    print_file ( "\n\n", logfile );

    // Preparing output files

    ofstream oFile;
    open_file ( oFilename, oFile );
    oFile    << "#"   << day.append( header.Date.begin () + 3, 
             header.Date.begin () + 5 ) 
             << " "   << Month << " "    << year.append( header.Date.begin () + 6,
             header.Date.end () );
    oFile    << " "   << header.Time     << " "    <<  header.Time_Zone << " " 
             << Mag_type2string ( string2_Mag_type ( header.Mag_type_string)) 
             << " "   << header.Mag_size << " "    << header.EqkName << " ";
    oFile    << "["   << header.Event_ID << "]  (" << header.Lon << ", " 
             << header.Lat << ", " << header.depth << ")" << endl;

    // Reading the input Entries

    while (( iFile >> Entry_Temp.Network_Code ) && ( Numb_of_valid_entries < 300)) 
    {
        flag = 0;
        Numb_of_input = Numb_of_input + 1;
        
        // Checking the following

        Network_Code_check ( Numb_of_input, Entry_Temp.Network_Code, logfile );
        iFile >> Entry_Temp.Stn_code;
        Stn_code_check ( Numb_of_input, Entry_Temp.Stn_code, logfile );
        iFile >> Entry_Temp.Band_Type;
        Band_Type_check ( Numb_of_input, Entry_Temp.Band_Type, logfile );
        iFile >> Entry_Temp.Inst_Type;
        Inst_Type_check ( Numb_of_input, Entry_Temp.Inst_Type, logfile );

       // Getting and Checking for Orientation

        h3 = "";
        h4 = "";
        h5 = "";
        iFile >> Entry_Temp.Orient;
        if (( Entry_Temp.Orient.length() < 1 ) || 
           ( Entry_Temp.Orient.length() > 3)) 
        {
            flag = 5;
        }
        else 
        {
            h1 = Entry_Temp.Orient[0];
            if (( h1 != "1" ) && ( h1 != "2" ) && ( h1 != "3" )) 
            {
                if (( uppercase ( h1 ) != uppercase ( "N" )) 
                && ( uppercase ( h1 )   != uppercase ( "E" )) 
                && ( uppercase ( h1 )   != uppercase ( "Z" )) ) 
                { 
                    flag = 5;
                }
                else 
                {
                    if ( Entry_Temp.Orient.length() > 1 ) 
                    {
                        h2 = Entry_Temp.Orient[1];
                        if (( h2 != "N" ) && ( h2 != "E" ) && ( h2 != "Z" )) 
                        {
                            flag = 5;
                        }
                        else 
                        {
                            if ( Entry_Temp.Orient.length() > 2 ) 
                            {
                                h5 = Entry_Temp.Orient[2];
                                if (( h5 != "N" ) && ( h5 != "E" ) && ( h5 != "Z" )) 
                                {
                                    flag = 5;
                                }
                            }
                        }
                    }
                }
            }
            else {
                if ( Entry_Temp.Orient.length() > 1 ) 
                {
                    h2 = Entry_Temp.Orient[1];
                    if (( h2 != "1" ) && ( h2 != "2" ) && ( h2 != "3")) 
                    {
                        flag = 5;
                    }
                    else 
                    {
                        if ( Entry_Temp.Orient.length() > 2 ) 
                        {
                            h5 = Entry_Temp.Orient[2];
                            if (( h5 != "1" ) && ( h5 != "2" ) && ( h5 != "3")) 
                            {
                                flag = 5;
                            }
                        }
                    }
                }
            }
        }

       if ( flag == 5 ) 
       {
            print_file ( "Entry # ", logfile );
            print_file ( Numb_of_input, logfile );
            print_file ( " ignored. Invalid Orient. ", logfile ); 
            print_file ( "\n", logfile );  
        }
        if ( flag == 0 ) 
        {
            Numb_of_valid_entries = Numb_of_valid_entries + 1;
            Entry_Temp.Orient = h1;
            Entry_Arr [ Numb_of_signal ] = Entry_Temp;
            Numb_of_signal = Numb_of_signal + 1;
            if ( h2 != "" ) 
            {
                Entry_Temp.Orient = h2;
                Entry_Arr [ Numb_of_signal ] = Entry_Temp;
                Numb_of_signal = Numb_of_signal +1;
                if ( h5 != "" ) 
                {
                    Entry_Temp.Orient = h5;
                    Entry_Arr [ Numb_of_signal ] = Entry_Temp;
                    Numb_of_signal = Numb_of_signal +1;
                }
            }
        }
    }

    print_file ( "Total invalid entries ignored: ", logfile );
    print_file (( Numb_of_input - Numb_of_valid_entries ), logfile );
    print_file ( "\n", logfile );
    print_file ( "Total valid entries read: ", logfile );
    print_file ( Numb_of_valid_entries, logfile );
    print_file ( "\n", logfile );
    print_file ( "Total signal names produced: ", logfile );
    print_file ( Numb_of_signal, logfile );
    print_file ( "\n", logfile );
    print_file ( "Finished!", logfile );

    oFile << ( Numb_of_signal ) << endl;             // Printing Outputs
    for (int i = 0; i < ( Numb_of_signal ); i++) 
    {

        // Producing Signal

        Signals ( oFile, header.Event_ID, Network_Code_to_string 
        ( string2_Network_Code ( Entry_Arr[i].Network_Code)), 
        Entry_Arr[i].Stn_code, Band_Type2string ( string2_Band_Type 
        ( Entry_Arr[i].Band_Type)),  Inst_Type2string 
        ( string2_Inst_Type ( Entry_Arr[i].Inst_Type)), Entry_Arr[i].Orient );
    }
    return 0;
}            // End of main programm

//******************************************************************************
// Functions

void open_input ( ifstream & ifs )                  // open_input Function 
{
    cout << "Enter input file name: ";              // Prompt User for Input File Name.
    cin >> iFileName;                               // Input file

    ifs.open(iFileName.c_str());

    if ( !ifs.is_open() ) 
    {
        message = "Input file does not exist!";    // Check if the File Is Opened correctly

        ofstream logfile;                         // log to logfile if Error occurrs
        open_file ( logfilename, logfile );
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void open_file ( string filename, ofstream & ofs ) // open_file Function (open new file)
{
    ofs.open(filename.c_str());
    if ( !ofs.is_open() ) 
    {
        message = "File does not exist!";

        ofstream logfile;                         // log to logfile if Error occurrs
        open_file ( logfilename, logfile );
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void print_file ( string message, ofstream & ofs )  // Prints Messages on Files and Terminal
{
    ofs << message  << flush;                       // Flush output stream buffer
    cout << message << flush;
    return;
}
//******************************************************************************
void print_file ( int number, ofstream & ofs )     // Function to Prints numbers
{
    ofs << number  << flush;
    cout << number << flush;
    return;
}
//******************************************************************************
void Date_check ( string Date, ofstream & logfile ) // function to checks validity of Date
{
    message = "Incorect Date !";
    if ( Date.length() != 10 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else 
    {
        if (( ( Date[2] != "-"[0] ) && ( Date[2] != "/"[0])) || 
        (( Date[5] != "-"[0] ) && ( Date[5] != "/"[0])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        else 
        {
            if (( !isdigit ( Date[0])) || ( !isdigit ( Date[1])) || 
            ( !isdigit ( Date[3])) || ( !isdigit ( Date[4])) ) 
            {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }  
            if (( !isdigit ( Date[6])) || ( !isdigit ( Date[7])) || 
            ( !isdigit ( Date[8])) || ( !isdigit ( Date[9])) ) 
            {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        }
    }
    return;
}
//******************************************************************************
void Month_check ( int Month, ofstream & logfile )  // function to check validity of Month 
{
    if (( Month > 12 ) || ( Month < 1))
    {
        message = "Incorect Month ! ";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Day_check ( int day, ofstream & logfile )    // function checks the validity of Day
{
    if (( day > 31 ) || ( day < 1))
    {
        message = "Incorect Day !.";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Year_check ( int year, ofstream & logfile )  // checking the validity of Year
{
    if ( year < 0 ) 
    {
        message = "Incorect Year !";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Time_check ( string Time, ofstream & logfile )  // checking the validity of Time
{
    message = "Incorrect Time format !";
    if ( Time.length() != 12 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else 

    {
        if (( Time[2] != ":"[0] ) || ( Time[5] != ":"[0] ) || 
           ( Time[8] != "."[0])) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        else 
        {
        if (( !isdigit ( Time[0])) || ( !isdigit ( Time[1])) || 
           ( !isdigit ( Time[3])) || ( !isdigit ( Time[4])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        if (( !isdigit ( Time[6])) || ( !isdigit ( Time[7])) || 
           ( !isdigit ( Time[9])) 
        || ( !isdigit ( Time[10])) || ( !isdigit ( Time[11])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        // Defining other Variables

        string temp0, h1, h2;
        double Val;

        temp0 =  temp0.append ( Time.begin (), Time.begin () + 2 ); // checking the validity of Hour
        Val = atoi(temp0.c_str());
        if (( Val < 0 ) || ( Val > 23)) 
        {
            message = "Incorrect Hour !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        h1 =  h1.append ( Time.begin () + 3, Time.begin () + 5 ); // checking the validity of Minutes
        Val = atoi(h1.c_str());
        if (( Val < 0 ) || ( Val > 59)) 
        {
            message = "Incorrect Minute !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        h2 =  h2.append ( Time.begin () + 6, Time.begin () + 8 ); // checking the validity of Seconds
        Val = atoi(h2.c_str());
        if (( Val < 0 ) || ( Val > 59)) 
        {
            message = "Incorrect Second !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        }
    }
    return;
}
//******************************************************************************
void Time_Zone_check ( string Time_Zone, ofstream & logfile ) // checking the validity of Time Zone
{
    message = "Incorrect Time_Zone format !.";
    if (( Time_Zone.length() != 3 ) || ( !isalpha ( Time_Zone[0])) || 
    ( !isalpha ( Time_Zone[1])) || ( !isalpha ( Time_Zone[2])) ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Mag_Type_check ( string Mag_type, ofstream & logfile ) // checking the validity of MagType
{
    message = "Incorrect Mag_type !.";
    string mt = uppercase ( Mag_type );
    if (( mt != uppercase ( "ml")) && ( mt != uppercase ( "ms")) 
    && ( mt != uppercase ( "mb")) && ( mt != uppercase ( "mw")) ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
// Function to checks for validity of Mag size 

void Mag_size_check ( float Mag_size, ofstream & logfile ) 
{
    message = "Incorrect Magnitude size !";
    if ( Mag_size <= 0 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
string uppercase ( string s )          // Converts all letters of input string to upper case.
{
    string result = s;
    for (int i=0; i < (int)s.size(); i++)
        result[i] = toupper(s[i]);
    return result;
}
//******************************************************************************
string MonthStrng ( Months Month )   // Function to Convert "Month" to a String
{
    switch ( Month ) 
    {
        case January:
            return "January";
        case February:
            return "February";
        case March:
            return "March";
        case April:
            return "April";
        case May:
            return "May";
        case June:
            return "June";
        case July:
            return "July";
        case August:
            return "August";
        case September:
            return "September";
        case October:
            return "October";
        case November:
            return "November";
        case December:
            return "December";
        default:
            return "ILLEGAL";
    }
}
//******************************************************************************
// Function to Produce Signal Name
        
void Signals ( ofstream & oFile, string Event_ID, string Network_Code, 
     string Stn_code, string Band_Type, string Inst_Type, string Orient ) 
{ 
    string temp= "";
    temp.append( Event_ID );
    temp.append( "." );
    temp.append( Network_Code );
    temp.append( "." );
    temp.append( Stn_code );
    temp.append( "." );
    temp.append( Band_Type );
    temp.append( Inst_Type );
    temp.append( Orient );
    oFile << temp << endl;
    return;
}
//******************************************************************************
// Function to Check Network Code

void Network_Code_check ( int Numb_of_input, string code, ofstream & logfile ) 
{
    if (( code.length() != 2 ) || (( code != "CE" ) && ( code != "CI" ) 
    && ( code != "FA" ) 
    && ( code != "NP" ) && ( code != "WR")) ) 
    {
        flag = 1;
    }
    if ( flag == 1) 
    {
        print_file ( "Entry # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid network. ", logfile );
        print_file ( "\n", logfile );
    }
    return;
}
//******************************************************************************
// Function to Check Station Code

void Stn_code_check ( int Numb_of_input, string code, ofstream & logfile ) 
{
    if ( code.length() != 3 ) 
    {
        if ( code.length() != 5 ) 
        {
            flag = 2;
        }
        else 
        {
            if (( !isdigit ( code[0])) || ( !isdigit ( code[1])) 
            || ( !isdigit ( code[2]))   || ( !isdigit ( code[3])) 
            || ( !isdigit ( code[4])) ) 
            {
                flag = 2;
            }
        }
    }
    else 
    {
        if (( !isalpha ( code[0])) || ( !isalpha ( code[1])) 
        || ( !isalpha ( code[2])) ) 
        {
            flag = 2;
        }
        else {
            if ( uppercase ( code ) != code ) 
            {
                flag = 2;
            }    
        }
    }
    if ( flag == 2) 
    {
        print_file ( "Entry # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid Stn code. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return;
}
//******************************************************************************
// Function to Check Type of Band

void Band_Type_check ( int Numb_of_input, string band, ofstream & logfile ) 
{
    if (( uppercase ( band ) != uppercase ( "Long-period")) 
    && ( uppercase  ( band ) != uppercase ( "Short-period")) 
    && ( uppercase  ( band ) != uppercase ( "Broadband")) ) 
    {
        flag = 3;
    }
    if ( flag == 3 ) {
        print_file ( "Entry # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid type of band. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return;
}    
//******************************************************************************
// Function to check instrument type
void Inst_Type_check ( int Numb_of_input, string instrument, ofstream & logfile ) 
{
    if (( uppercase ( instrument ) != uppercase ( "High-Gain")) 
    && ( uppercase ( instrument )  != uppercase ( "Low-Gain")) 
    && ( uppercase ( instrument )  != uppercase ( "Accelerometer")) ) 
    {
        flag = 4;
    }
    if ( flag == 4 ) 
    {
        print_file ( "Entry # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid type of instrument. ", logfile ); 
        print_file ( "\n", logfile );
    }
}
//******************************************************************************
string Mag_type2string ( Mag_type M )         // Function to Change Mag Type to String
{
    switch ( M ) 
    {
        case ML:
            return "ML";
        case Ms:
            return "Ms";
        case Mb:
            return "Mb";
        case Mw:
            return "Mw";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Mag_type string2_Mag_type ( string NN )       // Function to Change String to Mag Type
{
    NN = uppercase ( NN );
    if ( NN == "ML" ) 
    {
        return ML;
    }    
    if ( NN == "MS" ) 
    {
        return Ms;
    }
    if ( NN == "MB" ) 
    {
        return Mb;
    }
    if ( NN == "MW" ) 
    {
        return Mw;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
string Network_Code_to_string ( Network_Code MM )  // Function to Change Network Code to String
{
    switch ( MM ) 
    {
        case CE:
            return "CE";
        case CI:
            return "CI";
        case FA:
            return "FA";
        case NP:
            return "NP";
        case WR:
            return "WR";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Network_Code string2_Network_Code (string NN)  // Function to Change String to Network Code
{
    NN = uppercase (NN);
    if ( NN == "CE" ) 
    {
        return CE;
    }    
    if ( NN == "CI" ) 
    {
        return CI;
    }
    if ( NN == "FA" ) 
    {
        return FA;
    }
    if ( NN == "NP" ) 
    {
        return NP;
    }
    if ( NN == "WR" ) 
    {
        return WR;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
string Band_Type2string ( Band_Type MMM )  // Function to Change Band Type to String
{
    switch ( MMM ) 
    {
        case longperiod:
            return "L";
        case shortperiod:
            return "B";
        case broadband:
            return "H";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Band_Type string2_Band_Type (string NN)  // Function to Change String to Band Type
{
    NN = uppercase (NN);
    if ( NN == uppercase ( "Long-Period"))
    {
        return longperiod;
    }    
    if ( NN == uppercase ( "Short-Period"))
    {
        return shortperiod;
    }
    if ( NN == uppercase ( "Broadband"))
    {
        return broadband;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
// Function to Change Instrument Type to String

string Inst_Type2string ( Inst_Type MMMM )
{
    switch ( MMMM ) 
    {
        case highgain:
            return "H";
        case lowgain:
            return "L";
        case accelerometer:
            return "N";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Inst_Type string2_Inst_Type (string NN)   // Function to Change String to Instrument Type
{
    NN = uppercase (NN);
    if ( NN == uppercase ( "High-Gain"))
    {
        return highgain;
    }    
    if ( NN == uppercase ( "Low-Gain"))
    {
        return lowgain;
    }
    if ( NN == uppercase ( "Accelerometer"))
    {
        return accelerometer;
    }
    exit(EXIT_FAILURE);
}//******************************************************************************
