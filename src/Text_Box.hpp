/*
 * IDENTIFICATION
 * File name:  Text_Box.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the Text_Box class which
 * allows you to enter your alias in the start screen.
 */

#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <string>

/* CLASS Text_Box
 *
 * PARENT CLASS
 * None
 *
 * CONSTRUCTORS
 * Text_Box()
 *
 * OPERATIONS
 * draw, input RenderWindow &, output none
 * handle_input, input Event &, output none
 * get_alias, input none, output string
 *
 * DATA MEMBERS
 * string alias
 * Font font
 * Text text
 */

class Text_Box
{
public: 
    Text_Box(); 
    ~Text_Box() = default;
    void draw(sf::RenderWindow &);
    void handle_input(sf::Event &);
    std::string get_alias() const;   

private:
    std::string alias{};
    sf::Font font{};
    sf::Text text{};
};
#endif
