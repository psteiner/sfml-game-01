#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "World.h"

class Game : private sf::NonCopyable
{
public:
                            Game();
    void	                run();


private:

    void	                processEvents();
    void	                update(sf::Time deltaTime);
    void	                render();

    void                    updateStatistics(sf::Time elapsedTime);
    void                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    static const sf::Time   TimePerFrame;

    sf::RenderWindow	    mWindow;
    World                   mWorld;

    sf::Font                mFont;
    sf::Text                mStatisticsText;
    sf::Text                mAirplanePositionText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;

    bool                    mDebugGUI;
};

