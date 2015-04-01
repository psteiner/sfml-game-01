#pragma once
// System Includes
//

#include "Book/ResourceHolder.hpp"
#include "Book/ResourceIdentifiers.hpp"
#include "Book/Player.hpp"
#include "Book/StateStack.hpp"

// SFML Includes
//
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

// Game Includes
//

class Application
{
public:
                            Application();
    void                    run();

private:
    void                    processInput();
    void                    update(sf::Time dt);
    void                    render();

    void                    updateStatistics(sf::Time dt);
    void                    registerStates();

private:
    static const sf::Time   TimePerFrame;

    sf::RenderWindow        mWindow;
    TextureHolder           mTextures;
    FontHolder              mFonts;
    Player                  mPlayer;

    StateStack              mStateStack;

    sf::Text                mStatisticsText;
    sf::Time                mStatisticsUpdateTime;
    sf::Text                mAirplanePositionText;
    std::size_t             mStatisticsNumFrames;

    bool                    mDebugGUI;
};

