
// System Includes
//
#include <stdexcept>
#include <iostream>

// SFML Includes
//

// Game Includes
//
#include "Game.h"


int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}