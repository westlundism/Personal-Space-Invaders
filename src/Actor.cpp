/*
 * IDENTIFICATION
 * File name:  Actor.cpp
 * Type:       Definitions for module Actor
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Actor classes including the child
 * classes Player, Enemy, Block and Projectile.
 */

#include "Actor.hpp"

#define window_width 1024
#define window_height 768

#define left_border 95
#define right_border 890

using namespace std;

/*
 * --------------------------------------------------
 * --------------------- ACTOR ----------------------
 * --------------------------------------------------
 */

/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws the sprites for an actor.
 */

void Actor::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
}

/*
 * FUNCTION get_position() 
 *
 * Returns the position of an actor.
 */

sf::Vector2f Actor::get_position() const
{
    return position;
}

/*
 * FUNCTION get_size()
 *
 * Returns the size for an actor sprite.
 */

sf::FloatRect Actor::get_size()
{
    return sprite.getGlobalBounds(); 
}

/*
 * --------------------------------------------------
 * --------------------- PLAYER ---------------------
 * --------------------------------------------------
 */

/*
 * FUNCTION Player()
 *
 * Constructor for Player, loads textures and sets starting position.
 */

Player::Player()
{
    if(!texture.loadFromFile("sprites/player.png"))
	throw invalid_argument("Player not found!");
    sprite.setTexture(texture);
    position = sf::Vector2f((window_width/2 - texture.getSize().x / 2),
			    (window_height - texture.getSize().y * 2));

    energy_bar.setFillColor(sf::Color::Yellow);
    energy_bar.setPosition(window_width/2 - energy, 30);
}

void Player::draw(sf::RenderWindow & window)
{
    window.draw(energy_bar);
    window.draw(sprite);
}

/*
 * FUNCTION update(sf::Time &)
 *
 * Updates the position of the user and adds time to the
 * projectile delay.
 */

void Player::update(sf::Time & delta)
{
    projectile_delay += delta.asSeconds();
    energy_delay += delta.asSeconds();
    
    float distance = 250.0f * (delta.asMicroseconds() / 1000000.0f);

    if(controllers.run() && energy > 0 && controllers.is_moving())
    {
	distance = 250.0f * (delta.asMicroseconds() / 500000.0f);
	--energy;
	
    }

    if(round(energy_delay) >= 0.5 && energy < 50)
    {
	++energy;
	energy_delay = 0;
    }

    energy_bar.setSize(sf::Vector2f(energy * 2, 10));

    position += controllers.direction() * distance;
    
    if(position.x <= left_border)
	position.x = left_border;
    
    if(position.x >= right_border)
	position.x = right_border;

    sprite.setPosition(position);
}

/*
 * FUNCTION handle_input(sf::Event & event)
 *
 * Handles user inputs for player (shooting and moving)
 */

void Player::handle_input(sf::Event & event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
            controllers.handle_input(true, event.key.code);
            break;
        case sf::Event::KeyReleased:
            controllers.handle_input(false, event.key.code);
            break;
        default:
            break;
    }
}

/*
 * FUNCTION create_projectile(std::vector<std::unique_ptr<Projectile>> &)
 *
 * Creates a user projectile if controllers.shoot() = true, with
 * a delay of 1 second in case the shooting key is held.
 */

void Player::create_projectile(std::vector<std::unique_ptr<Projectile>> & projectiles)
{   
    if(controllers.shoot() && round(projectile_delay) >= 1.0)
    {
	projectiles.push_back(make_unique<Projectile>(position, true));
	projectile_delay = 0.0;
    }
}

/*
 * FUNCTION handle_collision(bool, Info_Strip &)
 *
 * Handles collision for the user, plays a sound, sleeps for
 * 2 seconds and then remove a life. If there only is one life
 * left, the user loses the game.
 */

void Player::handle_collision(bool enemy_collide, Info_Strip & strip)
{
    if (!hit_buffer.loadFromFile("sounds/wilhelm.wav"))
	throw invalid_argument("Wilhelm sound not found!");

    hit_sound.setBuffer(hit_buffer);
    hit_sound.play();
    
    sf::sleep(sf::seconds(2.0));
    
    if(strip.update_lives(-1) >= 1 && !enemy_collide)
	position.x = window_width/2 - texture.getSize().x / 2;
    else
	alive = false;
}

/*
 * --------------------------------------------------
 * --------------------- ENEMY ----------------------
 * --------------------------------------------------
 */

/*
 * FUNCTION Enemy(float, float, int)
 *
 * Constructor for an enemy. Takes in coordinates as floats
 * and enemy type (different texture for each enemy row in the swarm).
 */

Enemy::Enemy(float x, float y, int type)
{
    stringstream sprite_type;
    initialized_y = y; 
    position = sf::Vector2f(x, y - 200); //-100

    // Load different sprites for different enemy rows
    sprite_type << "sprites/enemy" << type << ".png";
	
    if(!texture.loadFromFile(sprite_type.str()))
	throw invalid_argument("Enemy not found!");
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

/*
 * FUNCTION update(sf::Time &)
 *
 * Handles movement for enemies and checks if they hit a window border
 * (turn direction) or hit the window bottom (finish the game).
 * In the begining of a new swarm of enemies they move from the top of the screen,
 * if the initialized_y coordinate is reached the enemies move side to side. 
 *
 */

void Enemy::update(sf::Time & delta)
{
    moving_delay += delta.asSeconds();
    projectile_delay += delta.asSeconds();
    change_direction_delay += delta.asSeconds();

    if (position.y <= initialized_y && moving_delay >= 0.03)
    {
	position.y += 5;
	sprite.setPosition(position);
	moving_delay = 0.0;
    }
    else if (moving_delay >= 0.5)
    {
	position.x += direction * 10;
	sprite.setPosition(position);
	moving_delay = 0.0;
    }

    if(position.x >= right_border || position.x <= left_border)
	if (change_direction_delay > 3.0)
	{
	    hit_border = true;
	    change_direction_delay = 0.0;
	}

    if(position.y > window_height)
	hit_bottom = true;
}

/*
 * FUNCTION change_direction()
 *
 * Changes direction of enemies movement and also moves them vertically
 * closer to the user.
 */

void Enemy::change_direction()
{
    hit_border = false; 
    direction = direction*-1;
    position.y += 30;
}

/*
 * FUNCTION create_projectile(std::vector<std::unique_ptr<Projectile>> &)
 *
 * Creates an enemy projectile, with a 10% chance of shooting each second.
 */

void Enemy::create_projectile(std::vector<std::unique_ptr<Projectile>> & projectiles)
{
    if (shoot)
    {
	if (projectile_delay > 1.0)
	{
	    // Enemies has a 10% chance of shooting a projectile
	    int random = rand() % 10 + 0;
	
	    if (random == 1)
		projectiles.push_back(make_unique<Projectile>(position, false));
	    
	    projectile_delay = 0.0;
	}

	shoot = false; 
    }
}

/*
 * FUNCTION handle_collision(bool, Info_Strip &)
 *
 * Handles collision for enemies. Updates the score if the enemy is hit
 * by a player projectile.
 */

void Enemy::handle_collision(bool enemy_collide, Info_Strip & strip)
{
    if(!enemy_collide)
    {
	strip.update_score(50);
	removed = true;
    }
}

/*
 * --------------------------------------------------
 * ------------------- BOSS ENEMY -------------------
 * --------------------------------------------------
 */

/*
 * FUNCTION Boss_Enemy()
 *
 * Constructor for a boss enemy, loads the texture and sets
 * starting position.
 */

Boss_Enemy::Boss_Enemy()
{
    if(!texture.loadFromFile("sprites/boss_enemy.png"))
       throw invalid_argument("Boss sprite not found!");
    sprite.setTexture(texture);
    sprite.setScale(0.7, 0.7);

    position = sf::Vector2f(-105.0, 50.0);
    
    sprite.setPosition(position);
}

/* 
 * FUNCTION update(sf::Time &)
 * 
 * Spawns a boss each 30 seconds of the game play.
 */

void Boss_Enemy::update(sf::Time & delta)
{
    boss_delay += delta.asSeconds();

    if (round(boss_delay) >= 30.0)
    {
	float distance = 250.0f * (delta.asMicroseconds() / 1500000.0f);
	position.x += distance;
	sprite.setPosition(position);
	
	if(position.x >= window_width)
	{
	    make_new_boss = true;
	    boss_delay = 0.0;
	}
    }
}

/* 
 * FUNCTION handle_collision(bool, Info_Strip &)
 * 
 * Handles collision for the boss enemy, except if it collides with another enemy.
 * Removes health for the first projectile hit, and kills for the second hit.
 */

void Boss_Enemy::handle_collision(bool enemy_collide, Info_Strip & strip)
{
    if(!enemy_collide)
    {
	if (health == 1)
	{
	    strip.update_lives(1);
	    strip.update_score(250);
	    removed = true;
	}
	else
	{
	    sprite.setScale(0.5,0.5); 
	    --health; 
	}
    }
}

/*
 * --------------------------------------------------
 * --------------------- BLOCK ----------------------
 * --------------------------------------------------
 */

/* 
 * FUNCTION Block(float, float)
 * 
 * Constructor for block, takes in coordinates as floats and loads three
 * textures for degrading.
 */

Block::Block(float x, float y)
{
    position = sf::Vector2f(x, y);

    if(!texture.loadFromFile("sprites/crate.png"))
	throw invalid_argument("Broken crate sprite not found!");
	
    if(!broken.loadFromFile("sprites/crate_broken.png"))
	throw invalid_argument("Broken crate sprite not found!");
    	
    if(!more_broken.loadFromFile("sprites/crate_broken2.png"))
	throw invalid_argument("Broken crate sprite not found!");
    
    sprite.setTexture(texture);
    sprite.setPosition(position); 
}

/* 
 * FUNCTION update(sf::Time &)
 * 
 * Degrades the block depending on health.
 */

void Block::update(sf::Time &)
{
    if (health == 1)
	sprite.setTexture(more_broken);
    else if (health == 2)
	sprite.setTexture(broken);
}

/* 
 * FUNCTION handle_collision(bool, Info_Strip &)
 * 
 * Degrades the block or removes it if health = 1.
 */

void Block::handle_collision(bool, Info_Strip &)
{
    if (health == 1)
	removed = true;
    else
	--health;
}

/*
 * --------------------------------------------------
 * ------------------- PROJECTILE -------------------
 * --------------------------------------------------
 */

/* 
 * FUNCTION Projectile(sf::Vector2f, bool)
 * 
 * Constructor for projectiles, depending on if it's from a player or enemy
 */

Projectile::Projectile(sf::Vector2f shooter_position, bool direction) : 
    from_player{direction}
{
    position = shooter_position;
    
    if (from_player)
    {	
	if(!texture.loadFromFile("sprites/player_projectile.gif"))
	    throw invalid_argument("Player projectile sprite not found!");

	if (!player_buffer.loadFromFile("sounds/no.wav"))
	    throw invalid_argument("Projectile sound not found!");

	position.y -= 40;
    
	player_sound.setBuffer(player_buffer);
	player_sound.play();
    }
    else
    {	
	if(!texture.loadFromFile("sprites/enemy_projectile.gif"))
	    throw invalid_argument("Enemy projectile sprite not found!");

	if (!enemy_buffer.loadFromFile("sounds/paper_toss.wav"))
	    throw invalid_argument("Projectile sound not found!");

        enemy_sound.setBuffer(enemy_buffer);
        enemy_sound.play();

	position.y += 40;
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);

}

/* 
 * FUNCTION update(sf::Time &)
 * 
 * Moves the projectile vertically, up or down depending on
 * if it's from player or enemy
 */

void Projectile::update(sf::Time & delta)
{
    float distance{};
    
    if (from_player)
    {
	distance = 250.0f * (delta.asMicroseconds() / 600000.0f);
	position.y -= distance;
    }
    else
    {
	distance = 250.0f * (delta.asMicroseconds() / 400000.0f);
        position.y -= -distance;
    }
    
    sprite.setPosition(position);

    if (get_position().y > 800 || get_position().y < 0)
	removed = true;
}

/* 
 * FUNCTION handle_collision(bool, Info_Strip &)
 * 
 * Removes the projectile if it collides.
 */

void Projectile::handle_collision(bool, Info_Strip &)
{
    removed = true;
}
