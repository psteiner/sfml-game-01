// System Includes
//

// SFML Includes
//
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

// Game Includes
//
#include "Book/PauseState.hpp"
#include "Book/Utility.hpp"
#include "Book/ResourceHolder.hpp"


PauseState::PauseState(StateStack& stack, Context context) 
    : State(stack, context)
    , mBackgroundSprite()
    , mPausedText()
    , mInstructionText()
{
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f viewSize = context.window->getView().getSize();

    mPausedText.setFont(font);
    mPausedText.setString("Game Paused");
    mPausedText.setCharacterSize(70);
    centerOrigin(mPausedText);
    mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

    mInstructionText.setFont(font);
    mInstructionText.setString("(Press Backspace to return to the main menu)");
    centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}


void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::Escape)
    {
        // Escape pressed, remove itself to return to the game
        requestStackPop();
    }

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        // Backspace pressed, end game and return to menu
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;
}