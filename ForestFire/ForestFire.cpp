// ForestFire.cpp
#include "Constants.h"
#include "Environment.cpp"
#include "Settings.h"

using namespace std;

//wind_directions wind_direction;
//wind_speeds wind_speed;
//int grid_size, moisture_level, number_of_neighbours;

Settings* current_settings;

void wait_for_ENTER()
{
	cout << "					press ENTER to continue..." << endl;
	getchar();
}

void get_settings_from_user()
{
	current_settings = new Settings();

	int grid_size_input, wind_direction_input, wind_speed_input, moisture_level_input, neighbour_type_input;

	cout << "					Welcome to Forest Fire Simulator 0.1\n" << endl;
	cout << "			Before the simulation can begin, the environment needs to be set up " << endl;
	cout << "			with data like grid size, wind direction, moisture level and so on." << endl;
	cout << "			Please answer the questions below, confirming each input with ENTER" << endl;

	//grid size input
	do
	{
		cout << "\nEnter the size of rectangular grid (10-30) :  ";

		if (cin >> grid_size_input && (grid_size_input >= 10 && grid_size_input <= 30))
		{
			cout << "Grid size set to : " << grid_size_input << " x " << grid_size_input << endl;
		}
		else
		{
			cout << "Incorrect input" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (grid_size_input < 10 || grid_size_input > 30);

	current_settings->grid_size = grid_size_input;

	//wind speed input
	do
	{
		// clearing the buffer again, in case there was some junk leftover from last semi-illegal input
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "\nChoose wind speed (1-4)" << endl;
		cout << "1: No wind \n2: Low \n3: High" << endl;

		if (cin >> wind_speed_input && (wind_speed_input >= 1 && wind_speed_input <= 3))
		{
			cout << "Wind speed set to : " << wind_speed_string[wind_speed_input];
		}
		else
		{
			cout << "Incorrect input" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (wind_speed_input < 1 || wind_speed_input > 3);

	//this workaround is necessary because I decided to use non-continous values in wind_speed enum
	//during input, didn't want to confuse user and ask him/her to chose 1,2 or 5
	//I would rather compensate for it here
	if (wind_direction_input = 3)
	{
		wind_direction_input = 5;
	}

	//risky buisness here, as always with casting, but the input should be validated by now
	//we are casting an int into our wind_speeds enum, so we can take advantage of all the nice things enum gives us
	current_settings->wind_speed = (wind_speeds)wind_speed_input;

	
	//wind direction input
	if (current_settings->wind_speed != NO_WIND)
	{	
		do
		{
			// clearing the buffer again, in case there was some junk leftover from last semi-illegal input - like "6aaa"
			// it would sitisfy the code above because of the int 6, but "aaa" would be left in a buffer, causing trouble during subsequent inputs
			cin.clear();
			cin.ignore(INT_MAX, '\n');

			cout << "\n\nChoose wind direction (1-4)" << endl;
			cout << "1: North \n2: South \n3: East \n4: West" << endl;

			if (cin >> wind_direction_input && (wind_direction_input >= 1 && wind_direction_input <= 4))
			{
				cout << "Wind direction set to : " << wind_direction_string[wind_direction_input];
			}
			else
			{
				cout << "Incorrect input" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		} while (wind_direction_input < 1 || wind_direction_input > 4);

		//risky buisness here, as always with casting, but the input should be validated by now
		//we are casting an int into our wind_directions enum, so we can take advantage of all the nice things enum gives us
		current_settings->wind_direction = (wind_directions)wind_direction_input;
	}
	else
	{
		current_settings->wind_direction = _NO_WIND;
	}

	//moisture level input
	do
	{
		cout << "\n\nEnter the moisture level in % (0-100) :  ";

		if (cin >> moisture_level_input && (moisture_level_input >= 0 && moisture_level_input <= 100))
		{
			cout << "Moisture level set to : " << moisture_level_input << "%" << endl;
		}
		else
		{
			cout << "Incorrect input" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (moisture_level_input < 0 || moisture_level_input > 100);

	current_settings->moisture_level = moisture_level_input;

	//type of neigbourhood input
	do
	{
		cout << "\nChoose type of neighbourhood (1-2) :  ";
		cout << "\n1: Von Neumann (four neighbours)\n2: Moore (eight neighbours)" << endl;
		cout << "(please see the docummentation for more details)" << endl;

		if (cin >> neighbour_type_input && (neighbour_type_input >= 1 && neighbour_type_input <= 2))
		{
			cout << "Neighbourhood type set to : " << ((neighbour_type_input == 1) ? ("Von Neuman") : ("Moore"));
		}
		else
		{
			cout << "Incorrect input" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (neighbour_type_input < 1 || neighbour_type_input > 2);

	//I cannot help it - I love that syntax
	//if the input was 1 (Von Neuman), number_of_neigbours will be set to 4, otherwise to 8 (Moore)
	current_settings->number_of_neighbours = (neighbour_type_input == 1) ? (4) : (8);

	system("pause");
}


int main()
{
	get_settings_from_user();
	

	//initialising random seed - will need it later when calculating ignition probability
	srand(time(NULL));

	bool fire_is_over = false;

	//initialise the forest with the values provided by the user
	Environment burning_forest(current_settings);

	burning_forest.display();

	while (!fire_is_over)
	{
		fire_is_over = !burning_forest.update();

		wait_for_ENTER();

		burning_forest.display();
	}

	burning_forest.display();
	system("pause");
	
	
	return 0;
}