#pragma once
#include <SFML/Graphics.hpp> // For graphics!
#include "Minesweeper_Types and Constants.h"

/**
 * @brief
 *
 *
 * @pre
 *
 *
 * @post
 *
 *
 * @return
 *
 *
 * @param
 *
 */
sf::Sprite CreateSprite(std::string filepath);


/**
 * @brief
 * 
 * 
 * @pre
 * 
 * 
 * @post
 * 
 * 
 * @return
 * 
 * 
 * @param
 * 
 */
GridDimensions GetGameBoardSize();

/**
 * @brief
 *
 *
 * @pre
 *
 *
 * @post
 *
 *
 * @return
 *
 *
 * @param
 *
 */
Difficulty GetDifficulty();

/**
 * @brief
 *
 *
 * @pre
 *
 *
 * @post
 *
 *
 * @return
 *
 *
 * @param
 *
 */
void resizeGameWindow(GridDimensions gridDimensions, sf::RenderWindow& window);