/*
 * IDENTIFICATION
 * File name:  Game.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the Game class which mainly
 * includes the game loop.
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game_State.hpp"
#include "Top_List.hpp"
#include "Text_Box.hpp"

class Game_State;

/* CLASS Game
 *
 * PARENT CLASS
 * None
 * 
 * CONSTRUCTORS
 * Game(), default constructor.
 *
 * OPERATIONS
 * run, input none, output none
 * update_state, input int, output none
 * quit_game, input none, output none
 * restart, input none, output none
 * draw_toplist, input RenderWindow &, output none
 * update_toplist, input string, int, output none
 * draw_textobx, input RenderWindow &, output none
 * get_alias, input none, output string
 * handle_alias_input, input Event &, output none
 *
 * DATA MEMBERS
 * vector<unique_ptr<Game_State>> states
 * int active_state
 * bool quit
 * Top_List toplist
 * Text_Box namebox
 */

class Game
{
public:
    Game();
    ~Game() = default;
    void run();
    void update_state(int);
    void quit_game();
    void restart();
    void draw_toplist(sf::RenderWindow &);
    void update_toplist(std::string, int);
    void draw_textbox(sf::RenderWindow &);
    std::string get_alias() const;
    void handle_alias_input(sf::Event &);
private:
    std::vector<std::unique_ptr<Game_State>> states{};
    int active_state{}; //index till active_state;
    bool quit{false};
    Top_List toplist{"Top_List/toplist.txt"};
    Text_Box namebox{};
};

#endif
