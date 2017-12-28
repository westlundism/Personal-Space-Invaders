/*
 * IDENTIFICATION
 * File name:  Button.cpp
 * Type:       Definitions for module Button
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Button classes including all the child
 * classes.
 */

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Game.hpp"

#define window_width 1024
#define window_height 768

using namespace std;


/*
 * CONSTRUCTOR Button(string const & text, int y) 
 *
 * Constructs the Button with a string that will be 
 * the text that is seen on the screen. 
 * Also takes the y-coordinate where the button should be.
 * Loads font from file. 
 *  
 * INPUT
 * string const &: a string with the name of the button.
 * int: the y-coordinate of the button.
 *
 */
Button::Button(string const & text, int y)
{
    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");

    button_text = sf::Text(text, font, 56);
    button_text.setPosition(window_width/2 - button_text.getGlobalBounds().width / 2, y);
    
    warning_text = sf::Text("", font, 15);
    warning_text.setPosition(window_width / 2, window_height / 2 - 30);
}


/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws the button and warning_text on the window.
 *
 * INPUT: 
 * sf::RenderWindow &: a reference to the game window.
 * 
 */
void Button::draw(sf::RenderWindow & window)
{
    window.draw(warning_text);
    window.draw(button_text); 
}

/*
 * FUNCTION clicked(sf::Event &) 
 *
 * Checks if the button is clicked
 *
 * INPUT: 
 * sf::Event &: a reference to the event
 *
 * OUTPUT:
 * bool, retruns true if the button is clicked  
 * 
 */
bool Button::clicked(sf::Event & event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
	float x = event.mouseButton.x; 
	float y = event.mouseButton.y;
	if (button_text.getGlobalBounds().contains(x, y))
	    return true;
    }
    return false; 
}

/*
 * FUNCTION touched(sf::Event &) 
 *
 * This function makes the text of the button red
 * if the mouse is held over it. 
 *
 * INPUT: 
 * sf::Event &: a reference to the event 
 * 
 */
void Button::touched(sf::Event & event)
{  
    if (event.type == sf::Event::MouseMoved)
    {
	float x = event.mouseMove.x; 
	float y = event.mouseMove.y; 
	if (button_text.getGlobalBounds().contains(x, y))
	    button_text.setColor(sf::Color::Red); 
	else
	    button_text.setColor(sf::Color::White); 	
    }
}


/*
 * --------------------------------------------------
 * --------------------- START_BUTTON ---------------
 * --------------------------------------------------
 */

/*
 * FUNCTION handle_input(sf::Event &, Game &) 
 *
 * This function handles if the mouse have moved or been 
 * clicked. It updates the game_state to Field if the
 * Start_Button has been clicked.
 * If the user has not entered an alias a warning_text
 * is set. 
 *
 * INPUT: 
 * sf::Event &: a reference to the event
 * Game &: a reference to the current Game 
 *
 * USES: 
 * function: touched(sf::Event &)
 * function: clicked(sf::Event &)
 * function: Game::update_state(int)
 * function: alias_needed_warning()
 * 
 */
void Start_Button::handle_input(sf::Event & event, Game & game)
{
    touched(event);
    
    if (clicked(event))
    {
	if (game.get_alias() != "")
	{
	    warning_text.setString(""); 
	    game.update_state(1);
	}
	else
	{
	    alias_needed_warning();	
	}
    }
    
}

/*
 * FUNCTION alias_needed_warning() 
 *
 * This function sets the warning_text
 *
 * INPUT: 
 * none
 * 
 */
void Start_Button::alias_needed_warning()
{
    warning_text.setString("(You need to enter your alias!)"); 
    sf::FloatRect textRect = warning_text.getLocalBounds();
    warning_text.setOrigin(textRect.width / 2, textRect.height / 2);
}


/*
 * --------------------------------------------------
 * --------------------- QUIT_BUTTON --------------
 * --------------------------------------------------
 */
/*
 * FUNCTION handle_input(sf::Event &, Game &) 
 *
 * This function handles if the mouse have moved or been 
 * clicked. It quits the game if clicked.
 *
 * INPUT: 
 * sf::Event &: a reference to the event
 * Game &: a reference to the current Game 
 *
 * USES: 
 * function: touched(sf::Event &)
 * function: clicked(sf::Event &)
 * function: Game::quit_game()
 * 
 */
void Quit_Button::handle_input(sf::Event & event, Game & game)
{
    touched(event);    
    if (clicked(event))
    {
	game.quit_game();
    }
}

/*
 * --------------------------------------------------
 * --------------------- RESUME_BUTTON --------------
 * --------------------------------------------------
 */
/*
 * FUNCTION handle_input(sf::Event &, Game &) 
 *
 * This function handles if the mouse have moved or been 
 * clicked. It updates the state back to Field if clicked. 
 *
 * INPUT: 
 * sf::Event &: a reference to the event
 * Game &: a reference to the current Game 
 *
 * USES: 
 * function: touched(sf::Event &)
 * function: clicked(sf::Event &)
 * function: Game::update_state(int)
 * 
 */
void Resume_Button::handle_input(sf::Event & event, Game & game)
{
    touched(event); 
    if (clicked(event))
    {
    	game.update_state(1);
    }
}


/*
 * --------------------------------------------------
 * --------------------- RESTART_BUTTON -------------
 * --------------------------------------------------
 */
/*
 * FUNCTION handle_input(sf::Event &, Game &) 
 *
 * This function handles if the mouse have moved or been 
 * clicked. It restarts the Game if clicked. 
 *
 * INPUT: 
 * sf::Event &: a reference to the event
 * Game &: a reference to the current Game 
 *
 * USES: 
 * function: touched(sf::Event &)
 * function: clicked(sf::Event &)
 * function: Game::restart() 
 * 
 */
void Restart_Button::handle_input(sf::Event & event, Game & game)
{
    touched(event); 
    if (clicked(event))
    {
    	game.restart(); 
    }
}
