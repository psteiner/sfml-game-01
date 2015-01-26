
// disable warning about getenv()
#pragma warning(disable:4996)

#include "Game.h"

#include "StringHelpers.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
    , mWorld(mWindow)
    , mFont()
    , mStatisticsText()
    , mAirplanePositionText()
    , mStatisticsUpdateTime()
    , mStatisticsNumFrames(0)
    , mDebugGUI(false)
{

    // See https://github.com/LaurentGomila/SFML/wiki/FAQ#graphics-vsync-framelimit
    // mWindow.setVerticalSyncEnabled(true);
    mWindow.setFramerateLimit(60);

    // Check for existence of DEBUG environment variable
    //
    if (getenv("DEBUG"))
    {
        mDebugGUI = true;
    }
    
    if (mDebugGUI)
    {
        mFont.loadFromFile("Media/Sansation.ttf");

        mStatisticsText.setFont(mFont);
        mStatisticsText.setPosition(5.f, 5.f);
        mStatisticsText.setCharacterSize(10);

        mAirplanePositionText.setFont(mFont);
        mAirplanePositionText.setPosition(5.f, 50.f);
        mAirplanePositionText.setCharacterSize(10);
    }
}


void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        if (mDebugGUI)
        {
            updateStatistics(elapsedTime);
        }
        
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}


void Game::update(sf::Time elapsedTime)
{
    mWorld.update(elapsedTime);
}


void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.draw(mAirplanePositionText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString(
            "Frames/Second: " + toString(mStatisticsNumFrames) + "\n" +
            "Time/Update: " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us"
            );
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }

    sf::Vector2f position = mWorld.playerPosition();
    mAirplanePositionText.setString("Airplane Position: " +
        toString(std::ceil(position.x)) +
        "/" + toString(std::ceil(position.y)));
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}


