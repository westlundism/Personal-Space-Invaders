/*
 * IDENTIFICATION
 * File name:  Top_List.cpp
 * Type:       Definitions for module Top_List
 * Written by: A. Westlund
 *             F. Flodin
 *             A. Nikonoff
 *             K. Palm
 *
 * DESCRIPTION
 * Defenitions for the class Top_List
 */

#include "Top_List.hpp"

#define window_width 1024

using namespace std; 
/*
 * FUNCTION Top_List(string const) 
 *
 *  takes a string that is a file name that is used to store-
 *  this sessions result in.
 */
Top_List::Top_List(string const & file_) :
    file{file_}
{
    ifstream in_file{file};
    string alias;
    int score;
    
    while (getline(in_file, alias, ':') >> score >> ws)
	toplist.emplace(alias, score);

    if(!font.loadFromFile("fonts/LCD_Solid.ttf"))
	throw invalid_argument("Font not found!");
}

/*
 * Destructor ~Top_List()
 *
 * Removes the Top_List Object and runs function save_to_file()
 */
Top_List::~Top_List()
{
    save_to_file(); 
}

/*
 * FUNCTION insert(string const &, int score)
 * 
 * sets the toplist variable to the score from this session
 */
void Top_List::insert(string const & alias, int score)
{
    toplist[alias] = score; 
}
//
std::vector<pair<string, int>> Top_List::get(unsigned const & list_rows) const
{
    vector<pair<string, int>> list{begin(toplist), end(toplist)};
    auto middle = begin(list);
    
    if (list.size() >= list_rows)
	advance( middle, list_rows);
    else
	middle = end(list);
    
    partial_sort(begin(list), middle, end(list),
		 [](pair<string, int> const& item,
		    pair<string, int> const& other)->bool
		 {
		     if ( item.second == other.second )
			 return item.first < other.first;
		     else
			 return item.second > other.second;
		 }
	);
  
    list.erase(middle, end(list));
  
    return list;
}
/*
 * FUNCTION save_to_file()
 * 
 * Sends the top liat to the save file
 */
void Top_List::save_to_file() const
{
    ofstream out_file{file};

    for (pair<string, int> const & item : toplist)
	out_file << item.first << ':' << item.second << endl;
}
/*
 * FUNCTION draw(Renderwindow &)
 * 
 * Draws the top_list object
 */
void Top_List::draw(sf::RenderWindow & window) const
{
    sf::Text highscore{"Highscore", font, 23};
    sf::FloatRect textRect = highscore.getLocalBounds();
    sf::Text text{to_string(5), font, 16};
    
    highscore.setOrigin(textRect.width/2, textRect.height/2);
    highscore.setPosition(window_width/2, 570);
    window.draw(highscore);
    
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2, textRect.height/2);
    text.setPosition(window_width/2, 680);
    window.draw(text);
}
/*
 * FUNCTION insert(string const &, int score)
 * 
 * sets the toplist variable to the score from this session
 */
string Top_List::to_string(unsigned const & list_rows) const 
{
    vector< pair<string, int>> list{}; 
    list = get(list_rows);

    ostringstream stream{};

    for (auto item : list)
    {
	stream.width(15);
	stream << left << item.first;
	stream.width(15);  
	stream << right << item.second << "\n\n"; 
    }

    return stream.str();
}
