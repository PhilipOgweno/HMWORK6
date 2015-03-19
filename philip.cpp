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
          {
               January = 1, February, March, April,May, June, 
               July, August, September, October, November, December
          };

struct earthquake
{
    string id,
    string date,
    string time,
    string earthquake_name,
    double epicenter,
    string magnitude_type,
    double magnitude,
};


struct station 
{
    string network,
    string stn_name,
    string band,
    string instrument,
    string orient,
};
