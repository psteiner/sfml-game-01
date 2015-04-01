#pragma once
// System Includes
//

// SFML Includes
//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

// Game Includes
//
#include "Book/State.hpp"

class PauseState :  public State
{
public:
                        PauseState(StateStack& state, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    sf::Sprite          mBackgroundSprite;
    sf::Text            mPausedText;
    sf::Text            mInstructionText;
};

