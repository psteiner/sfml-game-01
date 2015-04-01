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
#include "Book/World.hpp"
#include "Book/Player.hpp"

class GameState :
    public State
{
public:
                        GameState(StateStack& stack, Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    World               mWorld;
    Player&             mPlayer;
};

