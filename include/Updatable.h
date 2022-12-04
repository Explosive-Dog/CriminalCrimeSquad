#pragma once
#include <SFML/Graphics.hpp>

#include "GameState.h"

#include <vector>

struct UpdateParameters;

class Updatable
{
public:
    virtual ~Updatable() = default;
    virtual void update(UpdateParameters& updateParameters) = 0;
};

struct UpdateParameters final
{
    const sf::RenderWindow& window;
    sf::View& view;
    const GameState& gameState;
    const float& deltaTime;
    const std::vector<std::unique_ptr<Updatable>>& updatables;

    UpdateParameters(
        const sf::RenderWindow& mainWindow,
        sf::View& playerView,
        const GameState& gameKeyboardAndMouseState,
        const float& gameDeltaTime,
        const std::vector<std::unique_ptr<Updatable>>& theUpdatables
        )
        : window(mainWindow),
        view(playerView),
        gameState(gameKeyboardAndMouseState),
        deltaTime(gameDeltaTime),
        updatables(theUpdatables)

    {   /* Intentionaly Blank. */   }
};