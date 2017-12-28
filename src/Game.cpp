/*
 * IDENTIFICATION
 * File name:  Game.cpp
 * Type:       Definitions for module Game
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Definitions for the Game class which mainly
 * includes the game loop.
 */

#include "Game.hpp"

#define width 1024
#define height 768

using namespace std;

/*
 * FUNCTION Game()
 *
 * Constructor for Game. Pushes the four different Game States to
 * a vector.
 */

Game::Game()
{
    states.push_back(make_unique<Startscreen>(*this));
    states.push_back(make_unique<Field>(*this));
    states.push_back(make_unique<Pause>(*this));
    states.push_back(make_unique<Lose>(*this));
}

/*
 * FUNCTION run()
 *
 * Running the actual game. Renders the window, starts background music
 * and starts the game loop.
 */

void Game::run()
{
    // Render main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Personal Space Invaders",
			    sf::Style::Titlebar | sf::Style::Close);
    
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);

    // Add window icon
    sf::Image icon;
    if(!icon.loadFromFile("sprites/enemy1.png"))
	throw invalid_argument("Icon not found!");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Add framerate clock
    sf::Clock clock;

    // Start background music
    sf::Music music;
    if(!music.openFromFile("sounds/background.wav"))
	throw invalid_argument("Background sound not found!");
    music.setLoop(true);
    music.play();

    // Game loop
    auto delta = clock.restart();

    while (!quit)
    { 
	sf::Event event;
	while (window.pollEvent(event))
	{
	    switch (event.type) 
	    {
	    case sf::Event::Closed:
		quit_game();
		break;  
	    default:
		states.at(active_state) -> handle_input(event);
		break;
	    }
	}
	
	window.clear();

	states.at(active_state) -> update(delta);
	
	delta = clock.restart();
	
	states.at(active_state) -> draw(window);

	window.display();
    }
    
    window.close();
}

/*
 * FUNCTION update_state(int)
 *
 * Updates the game state.
 */

void Game::update_state(int new_state)
{
    active_state = new_state;
}

/*
 * FUNCTION quit_game()
 *
 * Quits the game.
 */

void Game::quit_game()
{
    quit = true;
}

/*
 * FUNCTION restart()
 *
 * Replaces the current Field state with a new one and updates
 * the game state to Startscreen.
 */

void Game::restart()
{
    states.at(1) = make_unique<Field>(*this);
    update_state(0);
}

/*
 * FUNCTION draw_toplist(sf::RenderWindow &)
 *
 * Draws the top list owned by Game.
 */

void Game::draw_toplist(sf::RenderWindow & window)
{
    toplist.draw(window);
}

/*
 * FUNCTION update_toplist(string, int)
 *
 * Updates the top list with the users alias and score.
 */

void Game::update_toplist(string alias, int score)
{
    toplist.insert(alias, score);
}

/*
 * FUNCTION draw_textbox(sf::RenderWindow & window)
 *
 * Draws the box for alias input.
 */

void Game::draw_textbox(sf::RenderWindow & window)
{
    namebox.draw(window);
}

/*
 * FUNCTION get_alias()
 *
 * Returns the user alias.
 */

string Game::get_alias() const
{
    return namebox.get_alias();
}

/*
 * FUNCTION handle_alias_input(sf::Event &)
 *
 * Handles the alias input in the name box.
 */

void Game::handle_alias_input(sf::Event & event)
{
    namebox.handle_input(event);
}
