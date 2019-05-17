#include <iostream>
#include "Minesweeper_Functions.h"
#include "Minesweeper_GameboardClass.h"
#include "Minesweeper_Types and Constants.h"

/*
 * Note:  In this project I took the liberty to take it a little further and try to teach myself some graphics etc.
 * because of this it has obviously taken a bit longer as I've had to do a lot of reading etc.
 * to learn how this stuff works and how to use it.  Hence this project is still in its developmental
 * rough draft stages, BUT I'm really close to having the basic functionality down, just have some weird bugs
 * to figure out and fix etc.  I decided to use the SFML library for the graphics in the project instead of straight OpenGL
 * I have tried to comment and explain everything pretty well, almost over comment just to be really clear and explain what's
 * happening in each step, plus this helps me learn and understand it as I'm coding it and learning the stuff myself.
 * Some areas are not explained in the clearest manner though probably and if you are confused about any of it or want me to explain
 * some part, let me know and I can explain it.
 * Also, it may be helpful to reference the texture image named "tiles.jpg" located in:
 * "...project\p03\Project 3 - Minesweeper\Project 3 - Minesweeper\Images"
 * Another note: I have done all of the development on this project locally on my windows computer in visual studio, so
 * I'm not sure how to set it up and run it on any other OS, though I believe it should be possible if done right.
 * If you need me to, I can bring my computer in and show you the program running on my laptop.
 */

/*
 * TODO:
 * Divide stuff up into functions
 * 
 * Write menu screen for choosing Difficulty, game board size, loading from saved games, saving and naming saved games, and verify inputs
 * 
 * Add functionality to save games and load from saves
 * (give choice of save name, but if none provided default name should include time stamp to verify uniqueness)
 * 
 * Make it display the percentage of the map that is mines
 * 
 * Make it so display grid is just 1 or 0 -- where 1 shows whats "behind" (shows the full grid there) and 0 shows the blank tile
 * 
 * Implement game over screen
 * 
 * Fix/refine Difficulty generations with different sized game boards etc.
 * 
 * Figure out sizing issues -- see if you can have non-square grid sizes
 * 
 * Make it so mines aren't generated until after the first click, so the first click is always safe
 *	Further goal, make it so the game is always possible to solve logically, no guessing ever needed
 * 
 * Make rescaling nice for all monitor sizes and resolutions, not pixel based
 * 
 * check all FIXMEs and make sure none are left
 * 
 * make sure game board is uniformly two words everywhere - or uniformly 1 word
 * 
 */

/*
 * Done:
 * Make clicked mine turn red
 * Change tiles to enum
 * Fix window closing -- couldn't close actual minesweeper window
 * 
 */

int main() {

	// Generate window for displaying stuff, set size, title, and options (close button)
	sf::RenderWindow window(sf::VideoMode(100, 300), "Minesweeper Menu", sf::Style::Close);

	// Filepath to sprite texture image
	const std::string spriteFilepath = "Images/tiles 2.jpg";

	//---------------------------------------------------------------------
	// Create a sprite from that sprite texture image
	// Create a texture from an image
	sf::Texture textureImage;

	// Verify it could be loaded
	if (!textureImage.loadFromFile(spriteFilepath)) {
		// Report error
		std::cerr << "Error, could not load texture image!" << std::endl;

		//FIXME - error handling here
		// Use known existing texture (texture not found texture)  -- or I could set it to some default color
		// filepath = 
	}

	// Create a sprite from that texture
	// A sprite is basically a part of the texture that can be moved and manipulated independently
	sf::Sprite sprite(textureImage);
	//----------------------------------------------------

	// Get the user's desired gameboard size
	const GridDimensions gridDimensions = GetGameBoardSize();

	// Get the user's desired difficulty level
	const Difficulty difficulty = GetDifficulty();

	// Resize the displayed window according to the gameboard dimensions
	resizeGameWindow(gridDimensions, window);

	// Create game board object
	GameboardClass gameboardObject(gridDimensions, difficulty);

	// Report max number of mines and the number of mines the gameboard has
	std::cout << "Max mines is: " << gameboardObject.GetMaxMines() << std::endl;
	std::cout << "This gameboard has " << gameboardObject.GetNumMines() << " mines." << std::endl;

	bool gameOver = false;

	// Main game loop -- runs as long as the window is open and the game isn't over
	while (window.isOpen() && !gameOver) {

		// Initialize mouse position to 0
		int mouseXPos = 0;
		int mouseYPos = 0;

		// Create event object
		sf::Event event;
		// Window.pollEvent(event) returns true as long as there is an event
		// So this loop executes as long as there are pending events...
		while (window.pollEvent(event)) {
			// check the type of the event...
			switch (event.type) {
				// Close option selected
				case sf::Event::Closed:
					// Ask user if they want to save their game
					// FIXME -- haven't implemented saving
					window.close();
					break;

				// Key pressed
				case sf::Event::KeyPressed:
					std::cout << "Key Pressed!" << std::endl;
					break;

				// Mouse Button Clicked
				case sf::Event::MouseButtonPressed:
					if (gameOver)
						break;
					// If it was the left mouse button...
					if (event.key.code == sf::Mouse::Left) {

						std::cout << "Left Mouse Button Clicked!" << std::endl;

						// Get the mouse position (x and y)
						const sf::Vector2i position = sf::Mouse::getPosition(window);
						// Set mouse x (or y) position to its pixel position divided by the width (or height) of each sprite/tile (32 px)
						// integer division here is what we want as it will truncate to a number corresponding to the tile
						// position in the grid arrays which can be used as an index in these arrays
						// add 1 to both x and y since the first row and column (indexed by 0) are not displayed and are empty
						mouseXPos = position.x / spriteRectDim + 1;
						mouseYPos = position.y / spriteRectDim + 1;

						// If they clicked on a mine, show game over and set the clicked mine to a clicked mine tile (background is red instead of gray)
						if (gameboardObject.fullGrid[mouseXPos][mouseYPos] == mineTile) {
							std::cout << "GAME OVER!" << std::endl;
							gameboardObject.fullGrid[mouseXPos][mouseYPos] = clickedMineTile;
							gameOver = true;
						}

						// Update the display grid at the position they clicked from the full grid
						gameboardObject.displayGrid[mouseXPos][mouseYPos] = gameboardObject.fullGrid[mouseXPos][mouseYPos];
					}

					// Else if it was the right mouse button...
					else if (event.key.code == sf::Mouse::Right) {

						// Get the mouse position (x and y)
						const sf::Vector2i position = sf::Mouse::getPosition(window);
						// Set mouse x (or y) position to its pixel position divided by the width (or height) of each sprite/tile (32 px)
						// integer division here is what we want as it will truncate to a number corresponding to the tile
						// position in the grid arrays which can be used as an index in these arrays
						// add 1 to both x and y since the first row and column (indexed by 0) are not displayed and are empty
						mouseXPos = position.x / spriteRectDim + 1;
						mouseYPos = position.y / spriteRectDim + 1;

						std::cout << "Right Mouse Button Clicked!" << std::endl;
						gameboardObject.displayGrid[mouseXPos][mouseYPos] = flaggedTile;
					}
					break;

				// No other event types are processed
				default:
					break;
			} // End of switch statement for dealing with different types of events
		} // End of while loop for dealing with polling events

		// Clear everything displaying on the current window and replace with the color black
		// This is so we can redraw the new gameboardObject.displayGrid and not redraw over the old grid
		window.clear(sf::Color::Black);

		// Update the window with what should now be displayed using gameboardObject.displayGrid and gameboardObject.fullGrid
		// Nested loops to loop through the rows and columns of the two dimensional arrays
		for (int row = 1; row <= gridDimensions.numGridRows; row++) {
			for (int col = 1; col <= gridDimensions.numGridCols; col++) {
				// If game over (they clicked on a mine), show the full grid
				// -- make the two grids (the displayed grid and "behind the scenes" grid with real values) equal
				// because we want to display the whole entire grid as the game is over at this point
				if (gameOver) {
					gameboardObject.displayGrid[row][col] = gameboardObject.fullGrid[row][col];
				}

				// Set the sprite to the proper part (square tile) of the texture
				// Remember gameboardObject.displayGrid[row][col] contains a value (0-12) corresponding to what should be displayed there
				// to create the sprite a small square/rectangle piece of the texture is taken
				// this is done using IntRect which takes 4 parameters (start x, start y, width, height)
				// (Note: everything is defined from the top left corner)
				// This start position for each sprite is gameboardObject.displayGrid[row][col] tiles/sprites over in the texture,
				// and each tile has a width of 32 pixels or spriteRectDim
				// so multiply gameboardObject.displayGrid[row][col] by the width of each sprite to get the desired distance over for the start position
				sprite.setTextureRect(sf::IntRect(gameboardObject.displayGrid[row][col] * spriteRectDim, 0, spriteRectDim, spriteRectDim));
				// Set the position on the screen where that sprite should be displayed
				// Subtract spriteRectDimensions from both x and y since we don't want to display the first row or first column (since those are empty)
				sprite.setPosition(row * spriteRectDim - spriteRectDim, col * spriteRectDim - spriteRectDim);
				// Draw the sprite to the window -- these changes are not displayed until window.display is called
				window.draw(sprite);
			}
		}

		// Update the window and display all the new changes (all the updated sprites etc.)
		window.display();

	} // End of main game loop

	system("PAUSE");

	window.close();

} // End of main
