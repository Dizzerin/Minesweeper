#include "Minesweeper_GameboardClass.h"
#include <ctime> // For "random" number generation
#include "Minesweeper_Types and Constants.h"
#include <iostream>

GameboardClass::GameboardClass(GridDimensions gridDimensions, Difficulty difficulty) : gridDimensions(gridDimensions), difficulty(difficulty)
{
	// Store the passed in gridDimensions and difficulty to the object
	// The variable gridDimensions (of type GridDimensions) local to this object is set equal to the variable gridDimensions that is passed in
	// Needing to use this-> in this case could easily be avoided by choosing a different name for the local variable on this object
	// I chose to do it this way for the sake of learning and showing when/where/why the this-> can be useful
	// this->gridDimensions = gridDimensions;
	// Post note: so instead of doing the line above, I chose to use an initializer list for the sake of more learning
	// It has the exact same effect in this case, you can see it after the : after the constructor header above
	//FIXME:  should clean up these comments and maybe comment more about what I'm doing above with the initializer list

	// Make the arrays one larger on every side so when checking for surrounding mines later
	// no special out of bounds checking is required -- this outer boarder is left blank and never displayed
	arrayRows = gridDimensions.numGridRows + 2;
	arrayCols = gridDimensions.numGridCols + 2;

	//FIXME COMMENTS
	// These are 2 two dimensional arrays here - one for the grid that will be "currently displayed" the other for the grid
	// with all of the real data, where the mines are etc. that is used to update the display grid as the user selects tiles


	// Allocate memory that will be used for the arrays
	// The pointers are then set to point to the allocated memory locations
	// NOTE: these are double pointers
	// NOTE: pointers and arrays are used the same in c++ basically
	fullGrid = new tile*[arrayRows];
	displayGrid = new tile*[arrayRows];

	for (int i = 0; i < arrayRows; i++) {
		fullGrid[i] = new tile[arrayCols];
		displayGrid[i] = new tile[arrayCols];
		
		//Initialize everything to 0's
		memset(fullGrid[i], 0, sizeof(tile)*arrayCols);
		memset(displayGrid[i], 0, sizeof(tile)*arrayCols);
	}

	// Notes about pointers and accessing the 2D arrays created above:
	// The following two statements do the same thing
	// They create a pointer that points to the third element in the second block of the fullGrid
	// I.e. row 2 col 3
	// int *secondBlockThirdElement = *(fullGrid+1) + 2;
	// int *secondBlockThirdElement = fullGrid[1] + 2;
	// int *secondBlockThirdElement = &(fullGrid[1][2]);
	//std::cout << "All these pointers will be the same:" << *(fullGrid + 1) + 2 << "  " << fullGrid[1] + 2 << "  " << &(fullGrid[1][2]) << std::endl;


	// Calculate the max number of mines this game board can have
	maxMines = CalcMaxMines();
	
	// Initialize the game board:
	InitializeGameboard();

}

GameboardClass::~GameboardClass()
{
	// Deallocate the memory allocated for the display grid arrays
	for (int i = 0; i < arrayRows; i++) {
		delete[] fullGrid[i];
		delete[] displayGrid[i];
	}

	delete[] fullGrid;
	delete[] displayGrid;
}

int GameboardClass::CalcMaxMines() {
	// maxMines is later set based on both Difficulty level chosen and game board size
	int maxMines;

	const int gridArea = gridDimensions.numGridRows * gridDimensions.numGridCols;

	// Switch statement for setting maxMines based off Difficulty and game board size
	switch (difficulty) {
	case beginner:
		// Set the max number of mines to 11% of the game board
		maxMines = .11 * gridArea;
		break;
	case easy:
		maxMines = .15 * gridArea;
		break;
	case normal:
		maxMines = .23 * gridArea;
		break;
	case hard:
		maxMines = .35 * gridArea;
		break;
	case extreme:
		maxMines = .90 * gridArea;
		break;
	case impossible:
		maxMines = gridArea;
		break;
	default:
		break;
	}
	
	return maxMines;
}

void GameboardClass::InitializeGameboard() {
	// Seed the random number function with the time
	srand(time(NULL));

	// Generate the grid
	// Nested loops to loop through the rows and columns of the two dimensional arrays
	numMines = 0;
	for (int row = 1; row <= gridDimensions.numGridRows; row++) {
		for (int col = 1; col <= gridDimensions.numGridCols; col++) {
			// Initialize every value in the display grid to an unclicked tile
			displayGrid[row][col] = unclickedTile;

			// Generate a random number between 0 and the number corresponding to the user's chosen Difficulty level and if it that number is 0:
			// Set the current tile position to a mine tile
			if ((rand() % difficulty == 0) && (numMines < maxMines)) {
				fullGrid[row][col] = mineTile;
				numMines++;
			}
			// Otherwise initialize the current tile to a blank tile
			else fullGrid[row][col] = blankTile;
		}
	}

	/*
	 *Now fill in the rest of the tiles with what they should be
	 *(they should be a number corresponding to the number of mines around them)
	 *(if there are no mines around them, then they are blank)
	 */

	 // Nested loops to loop through the rows and columns of the two dimensional arrays
	for (int row = 1; row <= gridDimensions.numGridRows; row++) {
		for (int col = 1; col <= gridDimensions.numGridCols; col++) {
			// Declare and initialize local var
			int adjacentMines = 0;

			// If current tile is a mine, skip it and continue
			if (fullGrid[row][col] == mineTile) continue;

			// If the tile below is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row + 1][col] == mineTile) adjacentMines++;

			// If the tile to the right is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row][col + 1] == mineTile) adjacentMines++;

			// If the tile above is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row - 1][col] == mineTile) adjacentMines++;

			// If the tile to the left is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row][col - 1] == mineTile) adjacentMines++;

			// If the tile to the bottom right corner is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row + 1][col + 1] == mineTile) adjacentMines++;

			// If the tile to the bottom left corner is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row + 1][col - 1] == mineTile) adjacentMines++;

			// If the tile to the top left corner is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row - 1][col - 1] == mineTile) adjacentMines++;

			// If the tile to the top right corner is a mine, add 1 to the number of adjacent mines
			if (fullGrid[row - 1][col + 1] == mineTile) adjacentMines++;

			// And FINALLY set the current tile to the sprite/tile that corresponds to the number of adjacent mines
			fullGrid[row][col] = static_cast<tile>(adjacentMines);
		}
	}
}

int GameboardClass::GetNumMines() {
	return numMines;
}

int GameboardClass::GetMaxMines() {
	return maxMines;
}
