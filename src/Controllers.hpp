/*
 * IDENTIFICATION
 * File name:  Controllers.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the Controller class that handles
 * movement, shooting and running.
 */

#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <SFML/Graphics.hpp>
#include <cmath>

/* CLASS Controllers
 *
 * PARENT CLASS
 * None
 *
 * DESCRIPTION
 * Handles all key inputs such as movement, shooting and running.
 * 
 * CONSTRUCTORS
 * Contollers(), default constructor.
 *
 * OPERATIONS
 * normalize, input sf::Vector2f, output sf::Vector2f
 * handle_input, input bool, sf::Keyboard::Key, output none
 * direction, input none, output sf::Vector2f
 * shoot(), input none, output boolean
 * run(), input none, output boolean
 * is_moving(), input none, output boolean
 *
 * DATA MEMBERS
 * bool left
 * bool right
 * bool space
 * bool shift
 */

class Controllers
{
public:
    Controllers();
    ~Controllers() = default;
    sf::Vector2f normalize(const sf::Vector2f &);
    void handle_input(bool, sf::Keyboard::Key);
    sf::Vector2f direction();
    bool shoot() const;
    bool run() const;
    bool is_moving() const;
private:
    bool left{};
    bool right{};
    bool space{};
    bool shift{};
};

#endif /* Controllers_hpp */
