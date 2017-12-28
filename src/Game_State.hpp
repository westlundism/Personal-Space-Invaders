/*
 * IDENTIFICATION
 * File name:  Game_State.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations of base class Game_State and its sub classes Startscreen, Field,
 * Pause and Lose. 
 * 
 *
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Actor.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "Info_Strip.hpp"
#include <vector>

class Game;


/* CLASS Game_State
 *
 * PARENT CLASS
 * None
 *
 * DESCRIPTION
 * Represents the different states the games can be in. 
 * 
 * CONSTRUCTORS	
 * Game_State(Game &) INPUT: a reference to the current game
 *
 * OPERATIONS
 * virtual void draw,         INPUT: sf::RenderWindow &
 * virtual void update,       INPUT: sf::Time &
 * virtual void handle_input, INPUT: sf::Event &
 *
 * DATA MEMBERS
 * Game & game
 * vector<std::unique_ptr<Button>> buttons
 * Sprite  sprite{}
 * Font    font{}
 * Texture background{}
 *
 */

class Game_State
{
public:
    Game_State(Game &);
    virtual ~Game_State() = default; 
    virtual void draw(sf::RenderWindow &) = 0;
    virtual void update(sf::Time &){}; 
    virtual void handle_input(sf::Event &) = 0;
protected:
    Game & game;
    std::vector<std::unique_ptr<Button>> buttons{}; 
    sf::Sprite  sprite{};
    sf::Font    font{};
    sf::Texture background{};
};

/* CLASS Startscreen
 *
 * PARENT CLASS
 * Game_State
 *
 * DESCRIPTION
 * Represents the Startscreen  
 * 
 * CONSTRUCTORS	
 * Startscreen(Game &) INPUT: a reference to the current game
 *
 * OPERATIONS
 * void draw,         INPUT: sf::RenderWindow &
 * void update,       INPUT: sf::Time &
 * void handle_input, INPUT: sf::Event &
 *
 * DATA MEMBERS
 * sf::Text version
 * sf::Text madeby
 * sf::Text controllerinfo
 *
 */

class Startscreen : public Game_State
{
public:
    Startscreen(Game &);
    ~Startscreen() = default; 
    void draw(sf::RenderWindow &) override;
    void handle_input(sf::Event &) override;
private:
    sf::Text version{};
    sf::Text madeby{};
    sf::Text controllerinfo{};
};

/* CLASS Field
 *
 * PARENT CLASS
 * Game_State
 *
 * DESCRIPTION
 * Represents the game field  
 * 
 * CONSTRUCTORS	
 * Field(Game &) INPUT: a reference to the current game
 *
 * OPERATIONS
 * virtual void draw,         INPUT: sf::RenderWindow &
 * virtual void update,       INPUT: sf::Time &
 * virtual void handle_input, INPUT: sf::Event &
 * 
 *
 * DATA MEMBERS
 * Info_Strip strip
 * std::vector<std::unique_ptr<Actor>> actors 
 * std::vector<std::unique_ptr<Projectile>> projectiles
 * float projectile_delay
 * float frame_delay
 * int frame_counter
 * int FPS
 * sf::Text FPS_text
 */

class Field : public Game_State
{
public:
    Field(Game &);
    ~Field() = default;
    void draw(sf::RenderWindow &) override;
    void update(sf::Time &) override;
    void handle_input(sf::Event &) override; 
private:
    void make_blocks();
    void make_enemies();
    void make_enemies_shoot();
    void collision_control();
    void actor_update(sf::Time &); 
    
    Info_Strip strip{};
    std::vector<std::unique_ptr<Actor>> actors{}; 
    std::vector<std::unique_ptr<Projectile>> projectiles{};
    float projectile_delay{};
    float frame_delay{};
    int frame_counter{};
    int FPS{};
    sf::Text FPS_text{};
    sf::Text energy_text{};
};



/* CLASS Pause
 *
 * PARENT CLASS
 * Game_State
 *
 * DESCRIPTION
 * Represents the pause screen 
 * 
 * CONSTRUCTORS	
 * Pause(Game &) INPUT: a reference to the current game
 *
 * OPERATIONS
 * void draw,         INPUT: sf::RenderWindow &
 * void update,       INPUT: sf::Time &
 * void handle_input, INPUT: sf::Event &
 *
 */
class Pause : public Game_State
{
public:
    Pause(Game &);
    ~Pause() = default;
    void draw(sf::RenderWindow &) override;
    void handle_input(sf::Event &) override;
};



/* CLASS Lose
 *
 * PARENT CLASS
 * Game_State
 *
 * DESCRIPTION
 * Represents the pause screen 
 * 
 * CONSTRUCTORS	
 * Lose(Game &) INPUT: a reference to the current game
 *
 * OPERATIONS
 * void draw,         INPUT: sf::RenderWindow &
 * void update,       INPUT: sf::Time &
 * void handle_input, INPUT: sf::Event &
 *
 * DATA MEMBERS
 * sf::Text lose_text
 *
 */
class Lose : public Game_State
{
public:
    Lose(Game &);
    ~Lose() = default; 
    void draw(sf::RenderWindow &) override;
    void handle_input(sf::Event &) override;
private:
    sf::Text lose_text{};
};

#endif
