#pragma once

// System Includes
//
#include <sstream>

// SFML Includes
//

// Game Includes
//


namespace sf
{
    class Sprite;
    class Text;
}

template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#include "Utility.inl"