#pragma once

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>

#include "Category.h"

// Forward reference
class SceneNode;

struct Command
{
                                                Command();
    std::function<void(SceneNode&, sf::Time)>   action;
    unsigned int                                category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return[=](SceneNode& node, sf::Time dt)
    {
        // Ensure cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node), dt);
    };
}