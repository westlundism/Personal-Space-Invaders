/*
 * IDENTIFICATION
 * File name:  Game_State.cpp
 * Type:       Definitions for module Game_State
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Game_State classes including the child
 * classes Startscreen, Field, Pause and Lose.
 */

#include "Game_State.hpp"

#define window_width 1024
#define window_height 768

using namespace std;


/*
 * CONSTRUCTOR Game_State(Game & game_init) 
 *
 * Constructs the Game_States with a reference to the 
 * current game. 
 * Loads font from file. 
 *  
 * INPUT
 * Game &: a reference to the current game
 *
 */
Game_State::Game_State(Game & game_init) :
    game(game_init)
{
    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");
}


/*
 * --------------------------------------------------
 * --------------------- STARTSCREEN ----------------
 * --------------------------------------------------
 */

/*
 * CONSTRUCTOR Startscreen(Game & game_init) 
 *
 * Constructs the Game_States with a reference to the 
 * current game. 
 * Loads background from file and creates all the buttons
 * needed on the startscreen. 
 *  
 * INPUT
 * Game &: a reference to the current game
 *
 */
Startscreen::Startscreen(Game & game_init) :
    Game_State(game_init)
{
    if(!background.loadFromFile("sprites/startbg.png"))
	throw invalid_argument("Background not found!");
    sprite.setTexture(background);

    
    buttons.push_back( make_unique<Start_Button> ("1-PLAYER", window_height/2));
    buttons.push_back( make_unique<Quit_Button>  ("QUIT", window_height/2 + 80)); 

    
    version = sf::Text("v1.0", font, 25);
    version.setPosition(window_width - 200, window_height - 50);
    
    madeby = sf::Text("Made by:\nKarl Palm\nAlexander Nikonoff"
		      "\nFrida Flodin\nAlexander Westlund", font, 16);
    madeby.setPosition(125, window_height - 100);

    controllerinfo = sf::Text("CONTROLLERS\n"
			      "LEFT: Move left\nRIGHT: Move right\n"
			     "SPACE: Shoot\nLSHIFT: Run\nP: Pause", font, 16);
    controllerinfo.setPosition(125, window_height/2);
}

/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws the component on the startscreen in the window.
 *
 * INPUT: 
 * sf::RenderWindow &: a reference to the game window.
 * 
 */

void Startscreen::draw(sf::RenderWindow & window)
{
    window.draw(sprite);

    for (auto && button : buttons)
	button -> draw(window);
    
    game.draw_toplist(window);
    game.draw_textbox(window);
    
    window.draw(version);
    window.draw(madeby);
    window.draw(controllerinfo);
}

/*
 * FUNCTION handle_input(sf::Event &)
 *
 * Takes care of user input like if the user have entered an alias
 * or pressed a button.
 *
 * INPUT: passes a sf::Event on to the components handle_input
 *
 */

void Startscreen::handle_input(sf::Event & event)
{
    for (auto && button : buttons)
    {
	button -> handle_input(event, game);
    }

    game.handle_alias_input(event);
}

/*
 * --------------------------------------------------
 * --------------------- FIELD ----------------------
 * --------------------------------------------------
 */

/*
 * CONSTRUCTOR Field(Game &) 
 *
 * Loads the background file to the sprite. 
 * Creates all the actors on the Field and push them to the actor vector
 *  
 *
 * INPUT: a Game reference that base class Game_State saves as a member
 *
 * USES: help functions make_blocks() and make_enemies() 
 */
Field::Field(Game & game_init) :
    Game_State(game_init)
{
    if(!background.loadFromFile("sprites/mbacken.png"))
	throw invalid_argument("Background not found!");
    sprite.setTexture(background);

    actors.push_back(make_unique<Player>());
    actors.push_back(make_unique<Boss_Enemy>());
    make_enemies();
    make_blocks();

    FPS_text = sf::Text("FPS: __", font, 20);
    FPS_text.setPosition(150, window_height - 20);
    FPS_text.setOrigin(FPS_text.getLocalBounds().width / 2,
		       FPS_text.getLocalBounds().height / 2);

    energy_text = sf::Text("ENERGY", font, 20);
    energy_text.setPosition(window_width/2, 10);
    energy_text.setOrigin(energy_text.getLocalBounds().width / 2,
			  energy_text.getLocalBounds().height / 2);
}


/*
 * FUNCTION make_enemies() 
 *
 * Help function to create all the enemies on the field
 * Pushes the enemies to the actors vector
 *
 */
void Field::make_enemies()
{
    int columns{12};
    int rows{4};
    
    for (int column_count{}; column_count < columns; column_count++)
    {
	for (int row_count{}; row_count < rows; row_count++)
	{
	    actors.push_back(make_unique<Enemy>( (column_count + 1) * 50 + 40,
						 100 + row_count * 75, row_count + 1) );
	}
    }
}


/*
 * FUNCTION make_blocks() 
 *
 * Help function to create all the blocks on the field
 * Pushes the blocks to the actors vector
 *
 */
void Field::make_blocks()
{
    Block temp{0,0};
    sf::FloatRect block_size{temp.get_size()}; 
 
    int number_of_blocks{3};
    int columns{4};
    int rows{3};
    
    double start{160};
    double step{(1024 - 2*start - block_size.width * columns)/(number_of_blocks - 1)}; 
    
    for (double block_batches{start} ;
	 block_batches <= start + (number_of_blocks - 1) * step ;
	 block_batches += step) 
    {
	for (int row_count{} ; row_count < rows ; ++row_count)
	{
	    for (int column_count{} ; column_count < columns ; ++column_count)
	    {
		actors.push_back(make_unique<Block>
				 (block_batches + block_size.width * column_count,
				  550 + block_size.height * row_count)); 
	    }
	}
    }
}


/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws all the actors and projectiles on the window
 *
 * INPUT: 
 * sf:RenderWindow 
 *
 * USES: 
 * function: Actor::draw(sf::RenderWindow &)
 * function: Strip::draw(sf::RenderWindow &) 
 *
 */
void Field::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
    strip.draw(window);
    window.draw(FPS_text);
    window.draw(energy_text);
    
    for (auto && actor : actors)
	actor -> draw(window);
    
    for (auto && projectile : projectiles)
	projectile -> draw(window);
}


/*
 * FUNCTION update(sf::Time &) 
 *
 * Updates all actors and projctiles by calling their update function.
 * Also removes actors if needed.
 *
 * INPUT: 
 * sf::Time &
 *
 *
 * USES: 
 * Function: actor_update(sf::Time &)
 * Function: make_enemies_shoot()
 * Function: collision_controll()
 * Function: Actor::update()
 *
 */
void Field::update(sf::Time & delta)
{
    
    projectile_delay += delta.asSeconds();

    // Measure FPS
    {
	frame_delay += delta.asMilliseconds();
	++frame_counter;

	if(frame_delay >= 1000)
	{
	    FPS = frame_counter / (frame_delay / 1000);
	    frame_counter = 0;
	    frame_delay = 0;
	    FPS_text.setString("FPS: " + to_string(FPS));
	    FPS_text.setOrigin(FPS_text.getLocalBounds().width/2,
			       FPS_text.getLocalBounds().height/2);
	}
    }
    
    // Update projectiles and remove projectiles if hit, loop in reverse 
    for (int index{(int)projectiles.size() - 1}; index >= 0; --index)
    {
	projectiles.at(index) -> update(delta);
	
	if (projectiles.at(index) -> removed)
	    projectiles.erase(projectiles.begin() + index);
    }

    actor_update(delta);
    
    make_enemies_shoot();
    collision_control();
    strip.update();
}


/*
 * FUNCTION actor_update(sf::Time &) 
 *
 * Help function that updates all actors by calling their update function.
 * Also removes actors if needed. Checks if any enemies have reached the border
 * of the screen. 
 * Counts all the enemies, if there are no left it calls the function make_enemies()
 * Creates new Boss_Enemy if needed.
 *
 * INPUT: 
 * sf::Time & 
 *
 *
 * USES: 
 * Function: make_enemies()
 * Function: Actor::update()
 *
 */
void Field::actor_update(sf::Time & delta)
{
	int enemy_counter{};
	bool border_hit{false};

	for (auto && actor : actors)
	{
	    actor -> update(delta);
	    actor -> create_projectile(projectiles);
	
	    if (actor -> hit_border)
		border_hit = true;

	    if (actor -> make_new_boss)
		actor = make_unique<Boss_Enemy>();
	
	    Enemy * temp = dynamic_cast<Enemy*>(actor.get());
	
	    if(temp != nullptr)
	    {
		++enemy_counter;
	    }
	}

	// Check if all enemies are gone, and make a new swarm if needed
	if(enemy_counter == 0)
	    make_enemies();
    

	// Loop in reverse to see if any actors have been removed
	for (int index{(int)actors.size() - 1}; index >= 0; --index)
	{
	    if (actors.at(index) -> removed)
	    {
		actors.erase(actors.begin() + index);
	    }
	} 

	// Check if enemies should change direction 
	if (border_hit == true)
	    for (auto && actor : actors)
		actor -> change_direction();
}



/*
 * FUNCTION actor_update() 
 *
 * Help function to calculate which enemy that will shoot.
 * It checks if an enemy is the lowest of its column, 
 * if it's the lowest it can shoot.
 *
 * USES: 
 * Function: Actor::get_position()
 *
 */
void Field::make_enemies_shoot()
{
    int index{};
    bool first_enemy{true};
    sf::Vector2f prev_enemy_pos{};
    sf::Vector2f this_enemy_pos{}; 
    
    for (auto && actor : actors)
    {
	Player * temp = dynamic_cast<Player*>( actor.get() );
	
	if (temp == nullptr)
	{
	    if (first_enemy)
	    {
		this_enemy_pos = actor -> get_position();
		first_enemy = false;
	    }
	    
	    prev_enemy_pos = this_enemy_pos; 

	    this_enemy_pos = actor -> get_position();

	    if (this_enemy_pos.x != prev_enemy_pos.x)
	    {
		actors.at(index - 1) -> shoot = true; 
	    }
	}
	++index; 
    }
}


/*
 * FUNCTION collision_control() 
 *
 * This function checks if any actors instersects which means 
 * that a collision has occurred. 
 * This function calls the actors handle_collision if needed
 * If the player is no longer alive the Game_State changes.
 * 
 *
 * INPUT: 
 * none 
 *
 *
 * USES: 
 * Function: Actor::get_size
 * Function: Actor::handle_collision
 * Function: Game::update_state
 * Function: Game::update_toplist
 * Function: Game::get_alias
 * Function: Info_Strip::update_score
 *
 */
void Field::collision_control()
{
    // Projectiles vs. Actors
    
    for (auto && projectile : projectiles)
	for (auto && actor : actors)
	    if (projectile -> get_size().intersects(actor -> get_size()))
	    {
		actor -> handle_collision(false, strip);
		projectile -> handle_collision(false, strip);

		if (!(actor -> alive))
		{
		    game.update_state(3);
		    game.update_toplist(game.get_alias(), strip.update_score(0));
		}
	    }

    // Actors vs. Actors
    
    for (auto && actor_one : actors)
	for (auto && actor_two : actors)
	    if (actor_one != actor_two &&
		actor_one -> get_size().intersects(actor_two -> get_size()))
	    {
		actor_one -> handle_collision(true, strip);

		if (!(actor_one -> alive))
		{
		    game.update_state(3);
		    game.update_toplist(game.get_alias(), strip.update_score(0));
		}
	    }

    // Projectiles vs. Projectiles

    for (auto && projectile_one : projectiles)
	for (auto && projectile_two : projectiles)
	    if (projectile_one != projectile_two &&
		projectile_one -> get_size().intersects(projectile_two -> get_size()))
		projectile_one -> handle_collision(false, strip);
    
}


/*
 * FUNCTION handle_input(sf::Event &) 
 *
 * This function handles the user input.
 * If the key 'P' is pressed the Game_State changes to Pause
 *
 *
 * INPUT: 
 * sf::Event & 
 *
 *
 * USES: 
 * Function: Actor::handle_input
 * Function: Game::update_toplist
 * Function: Game::update_state
 * Function: Game::get_alias
 * Function: Info_Strip::update_score
 *
 *
 */
void Field::handle_input(sf::Event & event)
{   
    for (auto && actor : actors)
	actor -> handle_input(event);
    
    switch (event.key.code)
    {
    case sf::Keyboard::P:
	if(event.type == sf::Event::KeyReleased)
	{
	    game.update_toplist(game.get_alias(), strip.update_score(0));
	    game.update_state(2);
	}
	break; 
    default:
	break;
    }
}


/*
 * --------------------------------------------------
 * --------------------- PAUSE ----------------------
 * --------------------------------------------------
 */

/*
 * CONSTRUCTOR Pause(Game &)
 *
 * Calls the Game_State constructor with the Game reference.
 * Loads the background from file and creates all the buttons.
 *
 */
Pause::Pause(Game & game_init) :
    Game_State(game_init)
{
    if(!background.loadFromFile("sprites/startbg.png"))
	throw invalid_argument("Background not found!");
    sprite.setTexture(background);

    buttons.push_back( make_unique< Resume_Button >  ("CONTINUE", window_height/2) );
    buttons.push_back( make_unique< Restart_Button > ("RESTART", window_height/2 + 100) );
    buttons.push_back( make_unique< Quit_Button >    ("QUIT", window_height/2 + 200) );

}


/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws the background on window and calls
 * the buttons draw-function
 *
 * INPUT: 
 * sf::RenderWindow & 
 *
 *
 * USES: 
 * function: Button::draw(sf:Event &, Game &)
 *
 */
void Pause::draw(sf::RenderWindow & window)
{
    window.draw(sprite);
    for (auto && button : buttons)
    {
	button -> draw(window); 
    }
}


/*
 * FUNCTION handle_input(sf::Event &) 
 *
 * This function calls all the buttons handle_input.
 *
 * INPUT: 
 * sf::Event & 
 *
 * USES: 
 * function: Button::handle_input(sf::Event &, Game &)
 *
 */
void Pause::handle_input(sf::Event & event)
{
    for (auto && button : buttons)
    {
	button -> handle_input( event, game ); 
    }
}




/*
 * --------------------------------------------------
 * --------------------- LOSE -----------------------
 * --------------------------------------------------
 */

/*
 * CONSTRUCTOR Lose(Game &)
 *
 * Calls the Game_State constructor with the Game reference.
 * Loads the background from file and creates all the buttons.
 *
 */
Lose::Lose(Game & game_init) :
    Game_State(game_init)
{
    if(!background.loadFromFile("sprites/startbg.png"))
	throw invalid_argument("Background not found!");
    sprite.setTexture(background);

    buttons.push_back( make_unique<Restart_Button> ("RESTART", window_height/2) );
    buttons.push_back( make_unique<Quit_Button>    ("QUIT", window_height/2 + 100) );

    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");

    lose_text = sf::Text("YOU LOSE!", font, 60);
    lose_text.setFillColor(sf::Color::Red);
    lose_text.setPosition(window_width/2, window_height/2 - 60);
    sf::FloatRect textRect = lose_text.getLocalBounds();
    lose_text.setOrigin(textRect.width/2,textRect.height/2);
}


/*
 * FUNCTION draw(sf::RenderWindow &) 
 *
 * Draws the background on window and calls
 * the buttons draw-function.
 * Also calls the draw_toplist-function in Game
 *
 * INPUT: 
 * sf::RenderWindow & 
 *
 *
 * USES: 
 * function: Button::draw(sf:Event &, Game &)
 * function: Game::draw_toplist(sf::RenderWindow &)
 *
 */
void Lose::draw(sf::RenderWindow & window)
{
    window.draw(sprite);

    for (auto && button : buttons)
    {
	button -> draw(window); 
    }
    
    game.draw_toplist(window);
    window.draw(lose_text);
}


/*
 * FUNCTION handle_input(sf::Event &) 
 *
 * This function calls all the buttons handle_input.
 *
 * INPUT: 
 * sf::Event & 
 *
 * USES: 
 * function: Button::handle_input(sf::Event &, Game &)
 *
 */
void Lose::handle_input(sf::Event & event)
{
    for (auto && button : buttons)
    {
	button -> handle_input(event, game); 
    }
}
