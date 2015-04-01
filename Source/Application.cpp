// System Includes
//

// SFML Includes
//

// Game Includes
//
#include "Book/Application.hpp"
#include "Book/Utility.hpp"
#include "Book/State.hpp"
#include "Book/StateIdentifiers.hpp"
#include "Book/TitleState.hpp"
#include "Book/GameState.hpp"
#include "Book/MenuState.hpp"
#include "Book/PauseState.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
    : mWindow(sf::VideoMode(640,480), "States", sf::Style::Close)
    , mTextures()
    , mFonts()
    , mPlayer()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
    , mStatisticsText()
    , mStatisticsUpdateTime()
    , mStatisticsNumFrames(0)
    , mAirplanePositionText()
    , mDebugGUI(false)
{
    mWindow.setKeyRepeatEnabled(false);

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
        mFonts.load(Fonts::Main, "Media/Sansation.ttf");
        mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

        mStatisticsText.setFont(mFonts.get(Fonts::Main));
        mStatisticsText.setPosition(5.f, 5.f);
        mStatisticsText.setCharacterSize(10u);

        mAirplanePositionText.setFont(mFonts.get(Fonts::Main));
        mAirplanePositionText.setPosition(5.f, 50.f);
        mAirplanePositionText.setCharacterSize(10u);
    }

    registerStates();
    mStateStack.pushState(States::Title);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time  timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
            {
                mWindow.close();
            }
        }

        if (mDebugGUI)
        {
            updateStatistics(dt);
        }

        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.draw(mAirplanePositionText);

    mWindow.display();

}

void Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }

    /* TODO: implement player aircraft position text

    sf::Vector2f position = mPlayer.playerPosition();
    mAirplanePositionText.setString("Airplane Position: " +
    toString(std::ceil(position.x)) +
    "/" + toString(std::ceil(position.y)));

    */
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
}
