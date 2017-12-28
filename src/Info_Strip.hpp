/*
 * IDENTIFICATION
 * File name:  Info_Strip.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the Actor class Info_Strip
 * 
 */
#ifndef INFO_STRIP_H
#define INFO_STRIP_H

#include <SFML/Graphics.hpp>
/* CLASS Info_Strip
 * 
 *
 * DESCRIPTION
 * handles the values and the functions that handles the
 * drawign and updating opf the info strip
 * 
 * CONSTRUCTORS
 * Info_Strip()
 *
 * DESTRUCTOR
 * ~Info_Strip()
 *
 * OPERATIONS
 * draw, input RenderWindow &, output none
 * update, input none, output none
 * update_score, input int, output int
 * update_lives, input int, output int
 *
 * DATA MEMBERS
 * int lives
 * int scores
 * Text lives_text
 * Text score_text
 * Font font
 * Sprite sprite
 * Texture texture
 * Vector2f position
 *
 */
class Info_Strip
{
public: 
    Info_Strip(); 
    ~Info_Strip() = default;
    void draw(sf::RenderWindow &);
    void update();
    int update_score(int);
    int update_lives(int);
private:
    int lives{3};
    int score{};
    sf::Text lives_text{}; 
    sf::Text score_text{};
    sf::Font font{};
    sf::Sprite sprite{};
    sf::Texture texture{};
    sf::Vector2f position{};
};

#endif
