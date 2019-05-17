#pragma once
#include <string>
#include "Minesweeper_Types and Constants.h"

class GameboardClass {
private:
	GridDimensions gridDimensions;
	Difficulty difficulty;
	int numMines;
	int maxMines;
	int arrayRows;
	int arrayCols;

public:

	//FIXME: is there a way to make this private? and should I?
	// Since methods within a class cannot create new variables added to the class here, we get around this by
	// declaring pointers here which we can then essentially make them any type and any size of variable later
	// this needs to be done in this case because we need to create two 2D arrays, but we don't know what size
	// they will be until we create an object from this class
	// -------------------------------------------------------------------------------------------------------
	// Declare two double pointers -- that will become the array grids
	// And initialize them to null pointers so they are pointing to null memory location (0X000) which is w/r protected
	// NOTE: These are double pointers
	tile **displayGrid = nullptr, **fullGrid = nullptr;

	// Constructor
	GameboardClass(GridDimensions gridDimensions, Difficulty difficulty);

	// Destructor
	~GameboardClass();

	// Methods
	int CalcMaxMines();
	void InitializeGameboard();

	// Methods to return values of private variables
	int GetNumMines();
	int GetMaxMines();
};
