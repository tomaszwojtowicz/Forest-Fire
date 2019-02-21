// Forest.cpp
#ifndef Forest_CPP
#define Forest_CPP

//project files
#include "Constants.h"
#include "Settings.h"

//#include "Cell.h"

using namespace std;


class Environment
{
private:

	int grid_size;
	int trees_burnt;
	int trees_burning = 1;
	int moisture_level;
	int number_of_neighbours;
	wind_directions wind_direction;
	wind_speeds wind_speed;

	string horizontal_negative_space, vertical_negative_space;

	//declaring pointer for a single empty cell
	//all the empty cells will point to the same object
	Empty_cell* empty_cell = new Empty_cell();


public:
	/*Cell** forest_map;*/
	Cell*** forest_map;


	string calculate_horizontal_negative_space(int grid_size)
	{
		string negative_space;
		int number_of_spaces;

		//the assumption here is that the terminal window is 110 characters wide
		//which is true on my system, but might not be on a target system
		//inability to use windows.h means that there is no way for the program to find out
		//the actual size of the terminal window, or just set the size
		number_of_spaces = (110 - (2 * grid_size)) / 2;

		for (int i = 0; i < number_of_spaces; i++)
		{
			negative_space += " ";
		}

		return negative_space;
	}


	string calculate_vertical_negative_space(int grid_size)
	{
		string negative_space ="\n";
		int number_of_lines;

		//the assumption here is that the terminal window is 40 characters high
		//which is true on my system, but might not be on a target system
		//inability to use windows.h means that there is no way for the program to find out
		//the actual size of the terminal window, or just set the size
		number_of_lines = (40 -  grid_size) / 3 -2;

		for (int i = 0; i < number_of_lines; i++)
		{
			negative_space += "\n";
		}

		//cout << "number of lines" << number_of_lines;
		return negative_space;
	}


	bool still_burning()
	{
		bool still_burning = true;

		if (trees_burning == 0)
		{
			//printf("nothing is burning");
			still_burning = false;
		}

		return still_burning;
	}

	// Displays header above the forest map
	void display_header()
	{
		cout << "\n       					Forest Fire Simulator v0.1 " << vertical_negative_space;
	}

	// Displays statistic underneath the forest map
	void display_stats()
	{
		//adding some negative space
		cout << vertical_negative_space;

		cout.precision(3); //limiting display to three digits
		cout << "       					Trees burnt   : " << (this->trees_burnt * 100.0) / 361 << "% \n";
		cout << "       					Trees burning : " << this->trees_burning  << vertical_negative_space;

	}


	// Deafult constructor
	Environment(Settings* current_settings)
	{
		this->grid_size = current_settings->grid_size;
		this->wind_direction = current_settings->wind_direction;
		this->wind_speed = current_settings->wind_speed;
		this->moisture_level = current_settings->moisture_level;
		this->number_of_neighbours = current_settings->number_of_neighbours;

		


		//initialising single empty cell
		//all the empty cells will point to the same object
		//Empty_cell* empty_cell = new Empty_cell();


		this->grid_size = grid_size;
		//create one dimension of the array
		forest_map = new Cell**[this->grid_size];

		for (int y = 0; y < this->grid_size; y++)
		{
			//create the 2nd dimension of the array
			forest_map[y] = new Cell*[this->grid_size];

			// seting up cells status
			for (int x = 0; x < this->grid_size; x++)
			{
				// the first if statement sets up the border of empty cells
				if ((x == 0 || x == this->grid_size - 1 || y == 0 || y == this->grid_size - 1))
				{
					/*forest_map[y][x] = new Empty_cell();*/
					//reusing the only existing empty cell
					forest_map[y][x] = this->empty_cell;

				}
				// this block of code sets up a single burning cell in the middle of the forest
				else if (x == (this->grid_size / 2) && y == this->grid_size / 2)
				{
					forest_map[y][x] = new Burning_tree();
				}
				// and finaly, every other cell will contain trees
				else
				{
					forest_map[y][x] = new Tree();
				}

			}
		}

	}

	// Displays the curent state of the forest
	void display()
	{
		horizontal_negative_space = calculate_horizontal_negative_space(grid_size);
		vertical_negative_space = calculate_vertical_negative_space(grid_size);
		
		display_header();


		for (int y = 0; y < this->grid_size; y++)
		{
			//adding some negative space
			cout << horizontal_negative_space;

			for (int x = 0; x < this->grid_size; x++)
			{
				forest_map[y][x]->display();

				// Displaying Map Legend on the side
				if (y == ((this->grid_size)/2-4) && x == (this->grid_size - 1)) //5
				{
					cout << "		Map Legend";
				}
				else if (y == ((this->grid_size) / 2 - 2) && x == (this->grid_size - 1)) //7
				{
					cout << "	   Empty cell:	  " << Cell::empty_cell_character << Cell::empty_cell_character;
				}
				else if (y == ((this->grid_size) / 2) && x == (this->grid_size - 1)) //9
				{
					cout << "		 Tree:	  " << Cell::tree_character << Cell::tree_character;
				}
				else if (y == ((this->grid_size) / 2 + 2) && x == (this->grid_size - 1)) //11
				{
					cout << "	 Burning tree:	  " << Cell::burning_tree_character << Cell::burning_tree_character;
				}
			}
			cout << "\n";
		}
		display_stats();
	}


	// Updates the forest map for the next iteration
	// Method returns TRUE if there are trees still burning and FALSE once all trees are burned out
	bool update()
	{
		//starting from [1][1] since the borders consist of empty cells anyway
		//same with the oposite borders - going only as far as [gridsize-1][gridsize-1]
		for (int y = 1; y < (this->grid_size - 1); y++)
		{
			for (int x = 1; x < (this->grid_size - 1); x++)
			{
				//ignore the empty cells and burning trees - they dont need to be processed at this stage
				//will swich burning to empty after the whole forest have been processed
				if (forest_map[y][x]->get_state() == TREE)
				{
					int ignition_probability = 0;

					//puting all the neighbours into separate array, for convenience
					//neighbour[1] is to the NORTH
					//neighbour[2] is to the SOUTH
					//neighbour[3] is to the EAST
					//neighbour[4] is to the WEST
					// in line with the values of wind_directions enum
					Cell* neighbours[5] = { NULL, forest_map[y - 1][x], forest_map[y + 1][x], forest_map[y][x + 1], forest_map[y][x - 1] };

					for (int i = 1; i < 5; i++)
					{
						if (neighbours[i]->get_state() == BURNING)
						{
							ignition_probability++;

							//if wind direction is the same as the neigbour direction
							//that's possible because the indices in neighbour[] are corresponding to the values of wind_direction enumerated type
							if ((int)wind_direction == i)
							{
								ignition_probability = ignition_probability * wind_speed* wind_speed* wind_speed;
							}
						}
					};

					//atempting to ignite the cell, only if at least one neigbour is burning
					if (ignition_probability > 0)
					{
						forest_map[y][x]->ignite(ignition_probability, moisture_level);
					}
				}
			}
		}

		//loop once again to change ignited trees into burning trees, and burning trees into empty cells
		for (int y = 1; y < (this->grid_size - 1); y++)
		{
			for (int x = 1; x < (this->
				grid_size - 1); x++)
			{
				// If cell was burning during last iteration, change its state to empty
				if (forest_map[y][x]->get_state() == BURNING)
				{
					delete forest_map[y][x]; // making sure that the old objects doesn't linger in the memory
					/*forest_map[y][x] = new Empty_cell();*/
					forest_map[y][x] = this->empty_cell;

					trees_burnt++;
					trees_burning--;
				}
				else if (forest_map[y][x]->get_next_state() == BURNING)
				{
					delete forest_map[y][x]; // making sure that the old objects doesn't linger in the memory
					forest_map[y][x] = new Burning_tree();
					trees_burning++;
				};
			}
		}
		// this part will return false 
		if (trees_burning == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}


};

#endif