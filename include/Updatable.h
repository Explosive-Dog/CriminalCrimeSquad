#pragma once
#include <SFML/Graphics.hpp>

#include "KeyboardAndMouseState.h"

struct UpdateParameters final
{
    const sf::RenderWindow& window;
    sf::View& view;
    const KeyboardAndMouseState& keyboardAndMouseState;


    UpdateParameters(const sf::RenderWindow& mainWindow,
        sf::View& playerView,
        const KeyboardAndMouseState& gameKeyboardAndMouseState)
        : window(mainWindow),
        view(playerView),
        keyboardAndMouseState(gameKeyboardAndMouseState)
    {   /* Intentionaly Blank. */   }
};

class Updatable
{
public:
    virtual ~Updatable() = default;
    virtual void update(const float deltaTime, UpdateParameters& updateParameters) = 0;
};