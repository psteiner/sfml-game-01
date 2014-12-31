#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "TextureHolder.h"

class Game
{
public:
                            Game();
    void	                run();

                            ~Game();
private:
    static const float      PlayerSpeed;
    static const sf::Time   TimePerFrame;

    void	                processEvents();
    void	                update(sf::Time deltaTime);
    void	                render();

    void                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void                    updateStatistics(sf::Time elapsedTime);
    void                    updateAirplanePosition();

    sf::RenderWindow	    mWindow;
    sf::Texture             mTexture;
    sf::Sprite     		    mPlayer;
    TextureHolder           mTextures;

    sf::Font                mFont;
    sf::Text                mStatisticsText;
    sf::Text                mAirplanePositionText;
    sf::Time                mStatisticsUpdateTime;
    std::size_t             mStatisticsNumFrames;

    bool                    mIsMovingUp;
    bool                    mIsMovingDown;
    bool                    mIsMovingLeft;
    bool                    mIsMovingRight;

    bool                    mDebugGUI;
};

