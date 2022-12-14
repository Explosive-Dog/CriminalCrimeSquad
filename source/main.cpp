#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Character.h"
#include "GameState.h"
#include "Player.h"
#include "Renderable.h"
#include "SelectionBox.h"
#include "Updatable.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void events(sf::RenderWindow& window, GameState& gameState, sf::View& view)
{
    sf::Event event;    
    gameState.resetKeyboardAndMouseStateCounters();
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) 
        {
            window.close();
        }
        if (event.type == sf::Event::Resized)
        {
            view.setSize(static_cast<float>(event.size.width / 20), static_cast<float>(event.size.height / 20));
        }
        gameState.updateKeyboardAndMouseState(window, view, event);
    }
}

void prepLevel(std::vector<std::unique_ptr<Updatable>> &updatables,
               std::vector<const Renderable*>& renderables)
{

    float x = static_cast<float>(rand() % 10);
    float y = static_cast<float>(rand() % 10);
    new Player(x, y, updatables, renderables);

    // random non-player controlled characters.

    for (size_t index = (static_cast<size_t>(rand() % 60) + 1); index != 0; --index)
    {
        new Character(20.f, 20.f, updatables, renderables);
    }

    for (size_t index = (static_cast<size_t>(rand() % 10) + 1); index != 0; --index)
    {
        new Character(static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables);
    }

    // set up the selection box as part of the level generation.
    new SelectionBox(updatables, renderables);
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    std::string seedString = std::to_string(seed);

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "A Game? seed: " + seedString, sf::Style::Default, settings);
    mainWindow.setFramerateLimit(200);
    mainWindow.setKeyRepeatEnabled(false);

    GameState gameState;
    std::vector<std::unique_ptr<Updatable>> updatables;
    std::vector<const Renderable*> renderables;

    Camera* playerView = new Camera;
    updatables.emplace_back(playerView);

    prepLevel(updatables, renderables);

    float deltaTime = 0.f;
    while (mainWindow.isOpen())
    {
        deltaTime = gameState.deltaTimeClock.restart().asSeconds();

        events(mainWindow, gameState, *playerView->getView());
        UpdateParameters updateParameters( mainWindow, *playerView->getView(), gameState, deltaTime, updatables);

        for (auto &updatable : updatables)
        {
            updatable->update(updateParameters);
        }

        mainWindow.setView(*playerView->getView());
        mainWindow.clear(sf::Color(75, 123, 34, 255));
        auto renderPriority = [](const Renderable* x, const Renderable* y) {return x->getRenderZLevel() < y->getRenderZLevel();};
        std::stable_sort(renderables.begin(), renderables.end(), renderPriority);
        for (auto &renderable : renderables)
        {
            renderable->render(mainWindow);
        }
        mainWindow.display();

        //system("cls");
    }
    return 0;
}