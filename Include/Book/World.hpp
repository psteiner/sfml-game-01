#pragma once

// System includes
//
#include <array>
#include <queue>

// SFML Includes
//
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>

// Game includes
//
#include "Book/ResourceHolder.hpp"
#include "Book/ResourceIdentifiers.hpp"
#include "Book/SceneNode.hpp"
#include "Book/SpriteNode.hpp"
#include "Book/Aircraft.hpp"
#include "Book/Command.hpp"
#include "Book/CommandQueue.hpp"


// Forward Declaration
namespace sf
{
    class RenderWindow;
}

class World : public sf::NonCopyable
{
    public:
        explicit                            World(sf::RenderWindow& window);
        void                                update(sf::Time dt);
        void                                draw();
        sf::Vector2f                        playerPosition();

        CommandQueue&                       getCommandQueue();

    private:
        void                                loadTextures();
        void                                buildScene();
        void                                adaptPlayerPosition();
        void                                adaptPlayerVelocity();

    private:
        enum Layer
        {
            Background,
            Air,
            LayerCount
        };

    private:
        sf::RenderWindow&                   mWindow;
        sf::View                            mWorldView;
        TextureHolder                       mTextures;
        
        SceneNode                           mSceneGraph;
        std::array<SceneNode*, LayerCount>  mSceneLayers;
        CommandQueue                        mCommandQueue;

        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        float                               mScrollSpeed;
        Aircraft*                           mPlayerAircraft;
};
