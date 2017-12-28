#include "Game.hpp"
#include <iostream>

int main()
{
    Game game;

    try
    {
	game.run();
    }
    catch (...)
    {
	std::cout << "Unknown error!" << std::endl;
    }

    return 0;
}
