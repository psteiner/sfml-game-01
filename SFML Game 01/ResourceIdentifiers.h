#pragma once

// forward declaration of SFML classes
namespace sf
{
    class Texture;
}

namespace Textures
{
    enum ID
    {
        Eagle,
        Raptor,
    };
}

// forward declaration
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
