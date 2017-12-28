/*
 * IDENTIFICATION
 * File name:  Actor.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the Actor classes including the child
 * classes Player, Enemy, Boss_Enemy, Block and Projectile.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Info_Strip.hpp"
#include "Controllers.hpp"
#include <sstream>
#include <cmath>

class Projectile;

/* CLASS Actor
 *
 * PARENT CLASS
 * None
 *
 * DESCRIPTION
 * Parent class for all Actors, includes virtual
 * functions used by the child classes and stores
 * their sprites, positions and a few booleans
 * used by the child classes.
 * 
 * CONSTRUCTORS
 * Actor(), default constructor.
 *
 * OPERATIONS
 * virtual update, input Time &, output none
 * virtual handle_input, input Event &, output none
 * virtual create_projectile, input vector<unique_ptr<Projectile>> &, output none
 * virtual change_direction, input none, output none
 * virtual handle_collision, input bool, Info_Strip &, output none
 * draw, input RenderWindow &, output none
 * get_position, input none, output Vector2f
 * get_size, input none, output FloatRect
 *
 * DATA MEMBERS
 * Sprite sprite
 * Vector2f position
 * bool shoot
 * bool hit_border
 * bool hit_bottom
 * bool make_new_boss
 * bool alive
 * bool removed
 */

class Actor
{
    friend class Field;
public:
    Actor() = default;
    virtual ~Actor() = default;
    virtual void update(sf::Time &) = 0;
    virtual void handle_input(sf::Event &) {}
    virtual void create_projectile(std::vector<std::unique_ptr<Projectile>> &) {}
    virtual void change_direction() {}
    virtual void handle_collision(bool, Info_Strip &) = 0;
    virtual void draw(sf::RenderWindow &);
    sf::Vector2f get_position() const;
    sf::FloatRect get_size();
protected:
    sf::Sprite sprite{};
    sf::Vector2f position{};
    bool shoot{false};
    bool hit_border{false};
    bool hit_bottom{false};
    bool make_new_boss{false};
    bool alive{true};
    bool removed{false};
};

/* CLASS Player
 *
 * PARENT CLASS
 * Actor
 *
 * DESCRIPTION
 * The actor for the game user. Handles movement and shooting
 * for the player. 
 * 
 * CONSTRUCTORS
 * Player()
 *
 * OPERATIONS
 * update, input Time &, output none
 * handle_input, input Event &, output none
 * create_projectile, input vector<unique_ptr<Projectile>> &, output none
 * handle_collision, input bool, Info_Strip &, output none
 *
 * DATA MEMBERS
 * Texture texture
 * Vector2f direction
 * float projectile_Delay
 * SoundBuffer hit_buffer
 * Sound hit_sound
 * Controllers controllers
 */

class Player : public Actor
{
public:
    Player();
    ~Player() = default;
    void update(sf::Time &) override; 
    void handle_input(sf::Event &) override;
    void create_projectile(std::vector<std::unique_ptr<Projectile>> &) override;
    void handle_collision(bool, Info_Strip &) override;
    void draw(sf::RenderWindow &) override;
private:
    sf::Texture texture{};
    sf::Vector2f direction{};
    float projectile_delay{};
    sf::RectangleShape energy_bar{};
    float energy_delay{};
    int energy{50};
    sf::Text energy_text{};
    sf::SoundBuffer hit_buffer{};
    sf::Sound hit_sound{};
    Controllers controllers{};
};

/* CLASS Enemy
 *
 * PARENT CLASS
 * Actor
 *
 * DESCRIPTION
 * The enemy actor. Handles movement, collision with
 * player projectiles and blocks, direction change and shooting
 * for the enemies.
 * 
 * CONSTRUCTORS
 * Enemy(float, float, int)
 *
 * OPERATIONS
 * update, input Time &, output none
 * handle_input, input Event &, output none
 * create_projectile, input vector<unique_ptr<Projectile>> &, output none
 * handle_collision, input bool, Info_Strip &, output none
 *
 * DATA MEMBERS
 * Texture texture
 * float moving_delay
 * float projectile_delay
 * float change_direction_delay
 * int direction
 * float initialized_y{};
 *
 */

class Enemy : public Actor
{    
public:
    Enemy(float, float, int);
    ~Enemy() = default;
    void update(sf::Time &) override;
    void create_projectile(std::vector<std::unique_ptr<Projectile>> &) override;
    void change_direction() override;
    void handle_collision(bool, Info_Strip &) override;
private:
    sf::Texture texture{};
    float moving_delay{};
    float projectile_delay{};
    float change_direction_delay{};
    int direction{1};
    float initialized_y{};
};

/* CLASS Boss_Enemy
 *
 * PARENT CLASS
 * Actor
 *
 * DESCRIPTION
 * A larger enemy that appears every 30 seconds. The class handles its' movement
 * and collision with player projectiles.
 * 
 * CONSTRUCTORS
 * Boss_Enemy()
 *
 * OPERATIONS
 * update, input Time &, output none
 * handle_collision, input bool, Info_Strip &, output none
 *
 * DATA MEMBERS
 * Texture texture
 * float boss_delay
 * int health
 */

class Boss_Enemy : public Actor
{
public:
    Boss_Enemy();
    ~Boss_Enemy() = default;
    void update(sf::Time &) override;
    void handle_collision(bool, Info_Strip &) override;
private:
    sf::Texture texture{};
    float boss_delay{};
    int health{2}; 
};

/* CLASS Block
 *
 * PARENT CLASS
 * Actor
 *
 * DESCRIPTION
 * Protection blocks for the player that appears in the beginning
 * of the game and that can be deformed and destructed by both the player
 * and the enemies using their projectiles.
 * 
 * CONSTRUCTORS
 * Block(float, float)
 *
 * OPERATIONS
 * update, input Time &, output none
 * handle_collision, input bool, Info_Strip &, output none
 *
 * DATA MEMBERS
 * Texture texture
 * Texture broken
 * Texture more_broken
 * int health
 */

class Block: public Actor
{
public:
    Block(float, float);
    ~Block() = default;
    void update(sf::Time &) override;
    void handle_collision(bool, Info_Strip &) override;
private:
    sf::Texture texture{};
    sf::Texture broken{};
    sf::Texture more_broken{};
    int health{3};
};

/* CLASS Projectile
 *
 * PARENT CLASS
 * Actor
 *
 * DESCRIPTION
 * The class for both player and enemy projectiles, handles its' movement
 * and collision with player, enemy, boss enemy and blocks.
 * 
 * CONSTRUCTORS
 * Projectile(Vector2f, bool)
 *
 * OPERATIONS
 * update, input Time &, output none
 * handle_collision, input bool, Info_Strip &, output none
 *
 * DATA MEMBERS
 * Texture texture
 * SoundBuffer player_buffer
 * SoundBuffer enemy_buffer
 * Sound player_sound
 * Sound enemy_sound
 * bool from_player
 */

class Projectile: public Actor
{
public:
    Projectile(sf::Vector2f, bool); 
    ~Projectile() = default;
    void update(sf::Time &) override;
    void handle_collision(bool, Info_Strip &) override;
private:
    sf::Texture texture{};
    sf::SoundBuffer player_buffer{};
    sf::SoundBuffer enemy_buffer{};
    sf::Sound player_sound{};
    sf::Sound enemy_sound{};
    bool from_player{};
};


#endif
