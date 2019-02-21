// Cell.h
#ifndef Cell_H
#define Cell_H

using namespace std;

class Cell
{
public:
	// declaring enumerated types
	enum cell_states { EMPTY, TREE, BURNING };
	
	//declaring symbols to visually represent the states of the cell
	static const char empty_cell_character = (char)176;
	static const char tree_character = (char)190;
	static const char burning_tree_character = char(64);

	// attributes of each cell
	cell_states state, next_state;

	// declaring method signatures
	virtual void display();
	virtual void ignite(int ignition_probability, int moisture_level);
	cell_states get_state();
	cell_states get_next_state();
	
};

class Tree : public Cell
{
public: Tree();
		void display();
		void ignite(int ignition_probability, int moisture_level);
};

class Empty_cell : public Cell
{
public:
	Empty_cell();
	void display();
};

class Burning_tree : public Cell
{
public:
	Burning_tree();
	void display();
};
#endif