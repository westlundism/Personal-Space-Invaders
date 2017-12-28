#ifndef TOP_LIST_H
#define TOP_LIST_H

#include <SFML/Graphics.hpp>
#include <string>
/*
 * IDENTIFICATION
 * File name:  Top_List.hpp
 * Type:       Module declaration
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Declarations for the class Top_List
 * 
 */

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
 /* CLASS Top_List
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
 * insert, input string &, output none
 * draw, input RenderWindow & output none
 * save_to_file, input none, output none
 *
 * DATA MEMBERS
 * vector<std::pair<std::string, int>>
 * string to_string
 * string file
 * map<std::string, int> toplist
 * Font font
 * Text highscore
 * Text text
 */
class Top_List 
{
public:
    Top_List(std::string const &);
    ~Top_List();
    void insert(std::string const &, int);
    void draw(sf::RenderWindow &) const;
private:
    void save_to_file() const;
    std::vector<std::pair<std::string, int>> get(unsigned const &) const;
    std::string to_string(unsigned const &) const;
    
    std::string file;
    std::map<std::string, int> toplist{};
    sf::Font font{};
    sf::Text highscore{};
    sf::Text text{};
};

#endif
