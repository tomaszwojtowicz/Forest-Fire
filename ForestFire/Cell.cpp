// Cell.cpp
#ifndef Cell_CPP
#define Cell_CPP

#include "Constants.h"
#include "Cell.h"


using namespace std;


// declaring enumerated types
//enum cell_states { EMPTY, TREE, BURNING, IGNITED };

//declaring symbols to visually represent the states of the cell
static const char empty_cell_character = (char)176;
const char tree_character = (char)190;
const char burning_tree_character = char(64);

cell_states state, next_state;

//VIRTUAL -DELETE IMPLEMENTATION WHEN READY
void Cell::display()
{
	//switch (state)
	//{
	//case EMPTY:
	//	cout << empty_cell_character << empty_cell_character;
	//	break;
	//case TREE:
	//	cout << tree_character << tree_character;
	//	break;
	//case BURNING:
	//	cout << burning_tree_character << burning_tree_character;
	//	break;
	//default:
	//	break;
	//}
}

//VIRTUAL -DELETE IMPLEMENTATION WHEN READY
void Cell::ignite(int ignition_probability, int moisture_level)
{
	////the forumula below is totaly arbitrary - need some more work
	////but I don't think it matters much for this particular project

	//int result = rand() % 100;

	//result = (result * ignition_probability ) - moisture_level;
	//
	//if (result > 50)
	//{
	//	/*this->cell_state = IGNITED;*/
	//	this->next_state = BURNING;
	//};
}

Cell::cell_states Cell::get_state()
{
	return this->state;
}

Cell::cell_states Cell::get_next_state()
{
	return this->next_state;
}



// Methods of the subclasses

//Tree
Tree::Tree()
{
	this->state = TREE;
}

void Tree::display()
{
	cout << tree_character << tree_character;
}

// this method works out if the cell will ignite
void Tree::ignite(int ignition_probability, int moisture_level)
{
	//the forumula below is totaly arbitrary - need some more work
	//but I don't think it matters much for this particular project

	int result = rand() % 100;

	result = (result * ignition_probability) - moisture_level;

	if (result > 50)
	{
		this->next_state = BURNING;
	};
}



//Empty_cell
Empty_cell::Empty_cell()
{
	this->state = EMPTY;
}

void Empty_cell::display()
{
	cout << empty_cell_character << empty_cell_character;
}


//Burning_tree
Burning_tree::Burning_tree()
{
	this->state = BURNING;
}

void Burning_tree::display()
{
	cout << burning_tree_character << burning_tree_character;
}

#endif

