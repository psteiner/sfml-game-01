// System Includes
//

// SFML Includes
//
#include <SFML/Graphics/RenderTarget.hpp>

// Game Includes
//
#include "Book/SpriteNode.hpp"


SpriteNode::SpriteNode(const sf::Texture& texture) : mSprite(texture)
{
    
}

SpriteNode::SpriteNode(const sf::Texture& texture, 
                        const sf::IntRect& textureRect) : mSprite(texture, textureRect)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}