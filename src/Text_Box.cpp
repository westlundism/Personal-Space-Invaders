/*
 * IDENTIFICATION
 * File name:  Text_Box.cpp
 * Type:       Definitions for module Text_Box
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Text_Box class which
 * allows you to enter your alias in the start screen.
 */

#include "Text_Box.hpp"

using namespace std; 

/*
 * CONSTRUCTOR Text_Box()
 *
 * Constructor for Text_Box. Loads and sets the text font, 
 * character size and position.
 */

Text_Box::Text_Box() 
{
    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");

    text = sf::Text("", font, 23);
    text.setPosition(1024/2, 325);
}


/*
 * FUNCTION draw(sf::RenderWindow &)
 *
 * Draws the text box and sets the origin depending on how many
 * characters you have written in the box.
 */

void Text_Box::draw(sf::RenderWindow & window) 
{
    text.setString("Enter your name: " + alias); 

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2,textRect.height/2);
    
    window.draw(text);
}

/*
 * FUNCTION handle_input(sf::Event &)
 *
 * Handles the character input in the text box.
 */

void Text_Box::handle_input(sf::Event & event)
{
    if (event.type == sf::Event::TextEntered)
    {
	if (event.text.unicode == 8 && alias.size() > 0)
	    alias.pop_back();
	else if (event.text.unicode > 31)
	    alias += static_cast<char>(event.text.unicode);
    }
}

/*
 * FUNCTION get_alias
 *
 * Returns the alias according to the user input.
 */

string Text_Box::get_alias() const
{
    return alias;
}
