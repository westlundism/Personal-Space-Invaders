/*
 * IDENTIFICATION
 * File name:  Button.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declaration of the base class Button and its sub classes 
 * Start_Button, Quit_Button, Resume_Button and Restart_Button.
 * 
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Game; 

/* CLASS Button
 *
 * PARENT CLASS
 * None
 *
 * DESCRIPTION
 * Represents a Button that the user can click on. 
 * 
 * CONSTRUCTORS	
 * Button(std::string &, int) INPUT: std::string &, int
 *
 * OPERATIONS
 * virtual void handle_input, INPUT: sf::Event &, Game &
 * void draw,                 INPUT: sf::RenderWindow &
 * bool clicked,              INPUT: sf::Event &
 * void touched,              INPUT: sf::Event & 
 *
 * DATA MEMBERS
 * sf::Text button_text
 * sf::Text warning_text
 * sf::Font font
 *
 */
class Button
{
public:
    Button(std::string const &, int);
    virtual ~Button() = default;
    virtual void handle_input(sf::Event &, Game &) = 0; 
    void draw(sf::RenderWindow &);
    bool clicked(sf::Event &);
    void touched(sf::Event &); 
protected:
    sf::Text button_text{};
    sf::Text warning_text{};
    sf::Font font{};
};


/* CLASS Start_Button
 *
 * PARENT CLASS
 * Button
 *
 * DESCRIPTION
 * Represents a Start_Button, the user can click on it.
 * 
 * 
 * CONSTRUCTORS	
 * Start_Button(std::string &, int) INPUT: std::string &, int
 *
 * OPERATIONS
 * void handle_input,          INPUT: sf::Event &, Game & 
 * void alias_needed_warning,  INPUT: none
 *
 */
class Start_Button : public Button
{
public:
    Start_Button(std::string const & text, int y): Button(text,y) {};
    ~Start_Button() = default;

    void handle_input(sf::Event &, Game &) override; 
    void alias_needed_warning();

};


/* CLASS Quit_Button
 *
 * PARENT CLASS
 * Button
 *
 * DESCRIPTION
 * Represents a Quit_Button, the user can click on it.
 * 
 * CONSTRUCTORS	
 * Quit_Button(std::string &, int) INPUT: std::string &, int
 *
 * OPERATIONS
 * void handle_input,          INPUT: sf::Event &, Game & 
 *
 */
class Quit_Button: public Button
{
public:
    Quit_Button(std::string const & text, int y): Button(text,y) {};
    ~Quit_Button() = default;

    void handle_input(sf::Event &, Game &) override; 

};

/* CLASS Resume_Button
 *
 * PARENT CLASS
 * Button
 *
 * DESCRIPTION
 * Represents a Resume_Button, the user can click on it.
 * 
 * CONSTRUCTORS	
 * Resume_Button(std::string &, int) INPUT: std::string &, int
 *
 * OPERATIONS
 * void handle_input,          INPUT: sf::Event &, Game & 
 *
 */
class Resume_Button: public Button
{
public:
    Resume_Button(std::string const & text, int y): Button(text,y) {};
    ~Resume_Button() = default;

    void handle_input(sf::Event &, Game &) override; 


};


/* CLASS Restart_Button
 *
 * PARENT CLASS
 * Button
 *
 * DESCRIPTION
 * Represents a Restart_Button, the user can click on it.
 * 
 * CONSTRUCTORS	
 * Restart_Button(std::string &, int) INPUT: std::string &, int
 *
 * OPERATIONS
 * void handle_input,          INPUT: sf::Event &, Game & 
 *
 */
class Restart_Button: public Button
{
public:
    Restart_Button(std::string const & text, int y): Button(text,y) {};
    ~Restart_Button() = default;

    void handle_input(sf::Event &, Game &); 

};

#endif
