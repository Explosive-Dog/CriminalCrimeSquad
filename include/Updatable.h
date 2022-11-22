#pragma once
#include <SFML/Graphics.hpp>

#include "GameState.h"

struct UpdateParameters final
{
    const sf::RenderWindow& window;
    sf::View& view;
    const GameState& gameState;


    UpdateParameters(const sf::RenderWindow& mainWindow,
        sf::View& playerView,
        const GameState& gameKeyboardAndMouseState)
        : window(mainWindow),
        view(playerView),
        gameState(gameKeyboardAndMouseState)
    {   /* Intentionaly Blank. */   }
};

class Updatable
{
public:
    virtual ~Updatable() = default;
    virtual void update(const float deltaTime, UpdateParameters& updateParameters) = 0;
};