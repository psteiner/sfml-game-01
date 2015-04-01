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

class MenuState : public State
{
public:
                                MenuState(StateStack& stack, Context context);
    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);

    void                        updateOptionText();

private:
    enum OptionName
    {
        Play,
        Exit,
    };

private:
    sf::Sprite                  mBackgroundSprite;
    std::vector<sf::Text>       mOptions;
    std::size_t                 mOptionIndex;
};

