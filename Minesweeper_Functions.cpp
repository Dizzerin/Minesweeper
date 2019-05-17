#include <iostream>
#include "Minesweeper_Functions.h"
#include "Minesweeper_Types and Constants.h"

GridDimensions GetGameBoardSize() {
	
	//FIXME -- actually get input
	// Initialize size of playing board
	GridDimensions gridDimensions;
	gridDimensions.numGridRows = 10;
	gridDimensions.numGridCols = 10;

	return gridDimensions;
}

Difficulty GetDifficulty() {
	// FIXME: Get desired Difficulty from user
	const auto difficulty = normal;

	return difficulty;
}

void resizeGameWindow(GridDimensions gridDimensions, sf::RenderWindow& window) {

	// Calculate the dimensions of the window based on number of tiles and width of each sprite / tile
	const auto windowHeight = gridDimensions.numGridRows * spriteRectDim;
	const auto windowWidth = gridDimensions.numGridCols * spriteRectDim;

	// change the size of the window
	window.setSize(sf::Vector2u(windowHeight, windowWidth));

	// change the title of the window
	window.setTitle("Minesweeper!");

	//FIXME
	// change the position of the window (relatively to the desktop)
	window.setPosition(sf::Vector2i(1100, 240));

}