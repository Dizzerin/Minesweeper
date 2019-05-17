#pragma once

// Define constants for the sprites (these are the graphical tiles, pieces of the texture -- more explained later)
// A sprite is basically a part of the texture that can be moved and manipulated individually
// Each sprite is accessed/referrenced by using the "multipliers" below
// I.e. each sprite (tile) is 32 pixels wide, and when we want to use a sprite, we define the shape (square) and starting position
// of that sprite, so the starting position of each sprite is 32 * how ever many sprites to move over in the texture.
enum tile {
	blankTile,
	oneTile,
	twoTile,
	threeTile,
	fourTile,
	fiveTile,
	sixTile,
	sevenTile,
	eightTile,
	mineTile,
	clickedMineTile,
	unclickedTile,
	flaggedTile
};

// Struct for game board dimensions
struct GridDimensions {
	int numGridRows;
	int numGridCols;

	// The following code overloads the = operator so we can set two of these structs equal to each other using it
	// with just a single line instead of equating its entries/members (whatever they are called) one by one
	// assume the object holds reusable storage, such as a heap-allocated buffer mArray
	GridDimensions& operator=(const GridDimensions& other) // copy assignment
	{
		if (this != &other) { // self-assignment check expected
			numGridRows = other.numGridRows;
			numGridCols = other.numGridCols;
		}
		return *this;
	}

};

// This is for the dimensions of the sprites created from the texture, they are all squares
// so their heights and widths are all the same so only one variable is required
// Note: variable name is short for "sprite rectangle dimensions"
const auto spriteRectDim = 32;

// Attempt at variable Difficulty (this may need some adjustment later)
// These values are used in the random number generation, a lower number corresponds to a higher likelihood of mine occurence
enum Difficulty {
	impossible = 2,
	extreme = 3,
	hard = 4,
	normal = 5,
	easy = 6,
	beginner = 9,
};