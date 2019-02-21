//settings.h
#ifndef Settings_H
#define Settings_H

#include "Constants.h"

using namespace std;

struct Settings
{
	wind_directions wind_direction;
	wind_speeds wind_speed;
	int grid_size, moisture_level, number_of_neighbours;
};



#endif