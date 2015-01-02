#include "Game.h"

#include "StringHelpers.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

const float Game::PlayerSpeed = 300.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
    , mTexture()
    , mPlayer()
    , mFont()
    , mStatisticsText()
    , mAirplanePositionText()
    , mStatisticsUpdateTime()
    , mStatisticsNumFrames(0)
    , mIsMovingUp(false)
    , mIsMovingDown(false)
    , mIsMovingLeft(false)
    , mIsMovingRight(false)
    , mDebugGUI(false)
{

    mWindow.setVerticalSyncEnabled(true);

    if (getenv("DEBUG"))
    {
        mDebugGUI = true;
    }

    try
    {
        mTextures.load(Textures::Airplane, "Media/Textures/Eagle.png");
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    mPlayer.setTexture(mTextures.get(Textures::Airplane));
    mPlayer.setPosition(100.f, 100.f);

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


Game::~Game()
{
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
            updateAirplanePosition();
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


void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
    {
        movement.y -= PlayerSpeed;
    }

    if (mIsMovingDown)
    {
        movement.y += PlayerSpeed;
    }

    if (mIsMovingLeft)
    {
        movement.x -= PlayerSpeed;
    }

    if (mIsMovingRight)
    {
        movement.x += PlayerSpeed;
    }

    mPlayer.move(movement * deltaTime.asSeconds());
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
}

void Game::updateAirplanePosition()
{
    sf::Vector2f position = mPlayer.getPosition();
    mAirplanePositionText.setString("Airplane Position: " + 
        toString(std::ceil(position.x)) + 
        "/" + toString(std::ceil(position.y)));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
    {
        mIsMovingUp = isPressed;
    }
    else if (key == sf::Keyboard::S)
    {
        mIsMovingDown = isPressed;
    }
    else if (key == sf::Keyboard::A)
    {
        mIsMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::D)
    {
        mIsMovingRight = isPressed;
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.draw(mStatisticsText);
    mWindow.draw(mAirplanePositionText);
    mWindow.display();
}

