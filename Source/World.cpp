// System Includes
//
#include <algorithm>
#include <cmath>

// SFML Includes
//
#include <SFML/Graphics/RenderWindow.hpp>

// Game Includes
//
#include "Book/World.hpp"


World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures()
    , mSceneGraph()
    , mSceneLayers()
    , mWorldBounds(
        0.f,                    // left X position
        0.f,                    // top Y position
        mWorldView.getSize().x, // width
        2000.f                  // height
    )
    , mSpawnPosition(
        mWorldView.getSize().x / 2.f,                       // X
        mWorldBounds.height - mWorldView.getSize().y / 2.f  // Y
    )
    , mScrollSpeed(-50.f)
    , mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    // prepare the view
    mWorldView.setCenter(mSpawnPosition);
}


void World::update(sf::Time dt)
{
    // Scroll the world view, reset player velocity
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    mPlayerAircraft->setVelocity(0.f, 0.f);

    // Forward commands to the scene graph
    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    adaptPlayerVelocity();
    mSceneGraph.update(dt);
    adaptPlayerPosition();
}


void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

// my own method for reporting player position on UI?
sf::Vector2f World::playerPosition()
{
    return mPlayerAircraft->getWorldPosition();
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    // add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Add player's aircraft
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(leader));
}

void World::adaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, 
    // at least borderDistance units from the border
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float borderDistance = 40.f;

    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    // if moving diagonally, reduce velocity (to always have the save velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    }

    // Add scrolling velocity
    mPlayerAircraft->accelerate(0.f, mScrollSpeed);


}