#pragma once
// System Includes
//

// SFML Includes
//
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

// Game Includes
//
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "World.h"
#include "Player.h"

class Game : private sf::NonCopyable
{
public:
                            Game();
    void	                run();


private:

    void	                processInput();
    void	                update(sf::Time deltaTime);
    void	                render();

    void                    updateStatistics(sf::Time elapsedTime);

private:
    static const sf::Time   TimePerFrame;

    sf::RenderWindow	    mWindow;
    World                   mWorld;
    Player                  mPlayer;

    sf::Font                mFont;
    sf::Text                mStatisticsText;
    sf::Text                mAirplanePositionText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;

    bool                    mDebugGUI;
};

