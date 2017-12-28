/*
 * IDENTIFICATION
 * File name:  Info_Strip.cpp
 * Type:       Definitions for module Actor
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the class Info_Strip
 */
#include "Info_Strip.hpp"

using namespace std;
/*
 * FUNCTION Info_Strip() 
 *
 * loads the data and the sprites for the infostrip.
 */
Info_Strip::Info_Strip()
{
    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");

    lives_text = sf::Text("LIVES: ", font, 23);
    lives_text.setPosition(100, 10);

    score_text = sf::Text("", font, 23);
    score_text.setPosition(820, 10); 

    if(!texture.loadFromFile("sprites/heart.png"))
	throw invalid_argument("Heart not found!");
    
    sprite.setTexture(texture);
}
/*
 * FUNCTION draw(RenderWindow &) 
 *
 * draws the info_strip on the window
 */
void Info_Strip::draw(sf::RenderWindow & window) 
{       
    float heart_position = 200;
    
    for(int count{}; count < lives; ++count)
    {	
	sprite.setPosition(sf::Vector2f(heart_position, 0)); 
	window.draw(sprite);
	heart_position += 50;
    }
    
    window.draw(score_text); 
    window.draw(lives_text);
}
/*
 * FUNCTION update() 
 *
 * updates the info_strip
 */
void Info_Strip::update()
{
    score_text.setString("SCORE: " + to_string(score));
}
/*
 * FUNCTION update_score() 
 *
 * Uådates the score datamember
 */
int Info_Strip::update_score(int _score)
{
    score += _score;
    return score;
}
/*
 * FUNCTION update_lives() 
 *
 * updates the lives datamember
 */
int Info_Strip::update_lives(int life)
{
    if(life > 0 && lives < 3)
	lives += life;
    else if(life < 0)
	lives += life;
    
    return lives;
}
