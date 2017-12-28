/*
 * IDENTIFICATION
 * File name:  Controllers.cpp
 * Type:       Definitions for module Controllers
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Controller class that handles
 * movement, shooting and running.
 */

#include "Controllers.hpp"

/*
 * FUNCTION Controllers()
 *
 * Constructor for Controllers that initializes the key
 * booleans to false.
 */

Controllers::Controllers() :
    left(false), right(false), space(false), shift(false) {}

/*
 * FUNCTION normalize(const sf::Vector2f &)
 *
 * Normalized the movement so that your speed does not increase if you hold
 * the movement keys.
 */

sf::Vector2f Controllers::normalize(const sf::Vector2f & direction)
{
    float length = sqrt(direction.x*direction.x + direction.y*direction.y);
    
    if (length <= 0.0f)
        return sf::Vector2f(0, 0);
    else
        return direction * (1.0f/length);
}

/*
 * FUNCTION handle_input(bool, sf::Keyboard::Key)
 *
 * Handles the user input by telling Controllers if
 * a key is pressed.
 */

void Controllers::handle_input(bool pressed, sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
	left = pressed;
	break;
    case sf::Keyboard::Right:
	right = pressed;
	break;
    case sf::Keyboard::Space:
	space = pressed;
	break;
    case sf::Keyboard::LShift:
	shift = pressed;
	break;
    default:
	break;
    }
}

/*
 * FUNCTION direction()
 *
 * Handles the direction of player movement depending on if left or
 * right is pressed and returns the normalized direction.
 */

sf::Vector2f Controllers::direction()
{
    sf::Vector2f direction;
    
    if (left)
        direction.x -= 1.0f;
    else if (right)
        direction.x += 1.0f;
    
    return normalize(direction);
}

/*
 * FUNCTION shoot()
 *
 * A function to check if the user pressed space.
 */

bool Controllers::shoot() const
{
    return space;
}

/*
 * FUNCTION run()
 *
 * A function to check if the user pressed Lshift.
 */

bool Controllers::run() const
{
    return shift;
}

/*
 * FUNCTION is_moving()
 *
 * A function to check if the user is moving.
 */

bool Controllers::is_moving() const
{
    if(left || right)
	return true;
    else
	return false;
}
