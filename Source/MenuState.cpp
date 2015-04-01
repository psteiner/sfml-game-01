// System Includes
//

// SFML Includes
//
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

// Game Includes
//
#include "Book/MenuState.hpp"
#include "Book/Utility.hpp"
#include "Book/ResourceHolder.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mOptions()
    , mOptionIndex(0)
{
    sf::Texture& texture = context.textures->get(Textures::TitleScreen);
    sf::Font& font = context.fonts->get(Fonts::Main);
    
    mBackgroundSprite.setTexture(texture);

    // a simple menu demonstration
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);
    updateOptionText();

}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);

    for (const sf::Text& text : mOptions)
    {
        window.draw(text);
    }
}

bool MenuState::update(sf::Time dt)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    // THe demonstration menu logic
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        else if (mOptionIndex == Exit)
        {
            // Exit option chosen. By removing itself, the stack 
            // will be empty, and the game will know it is time
            // to close
            requestStackPop();
        }
    }
    else if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
        {
            mOptionIndex--;
        }
        else
        {
            mOptionIndex = mOptions.size() - 1;
        }

        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
        {
            mOptionIndex++;
        }
        else
        {
            mOptionIndex = 0;
        }

        updateOptionText();
    }

    return true;
}

void MenuState::updateOptionText()
{
    if (mOptions.empty())
    {
        return;
    }

    // Set all text white
    //
    for (sf::Text& text : mOptions)
    {
        text.setColor(sf::Color::White);
    }

    // set the selected option text to red
    mOptions[mOptionIndex].setColor(sf::Color::Red);
}