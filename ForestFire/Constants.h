// Constants.h
#ifndef Constants_H
#define Constants_H

//libraries
#include <iostream>
#include <cstdlib>
#include <string>  //cstring originally, but was having problems with << operators and strings
#include <Time.h>
#include <vector>

//project files
//#include "Forest.cpp"
#include "Cell.h"

using namespace std;

// declaring enumerated types
enum wind_directions { _NO_WIND = 0, NORTH_WIND = 1, SOUTH_WIND = 2, EAST_WIND = 3, WEST_WIND = 4 };



//the numbers represent multiplier aplied to ignition probability
//please note value 5 for the HIGH wind - the reason behind it is to have a bigger impact of strong wind
//it does have consequences though - need to compensate for it when casting user imput into enum
enum wind_speeds { NO_WIND = 1, LOW = 2, HIGH = 5 }; 
enum cell_states { EMPTY, TREE, BURNING };

// declaring constants
//const int ignition_probablity = 50;
//static const int moisture_level = 100;  // in % - so 0 is totaly dry, while 100 is very moist
//static const int grid_size = 21;

// in later version this will be set from user input
//static wind_directions wind_direction = NORTH_WIND;
//static wind_speeds wind_speed = HIGH;


//the purpose of those arrays is to translate the value of enum back into string so they can be displayed back to user
static string wind_direction_string[] = { "", "North", "South" , "East" , "West" };
static string wind_speed_string[] = { "", "No wind", "Low" , "High" };
#endif