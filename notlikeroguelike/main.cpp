#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Player.h"
#include "Character.h"
#include "SelectionBox.h"
#include "KeyboardAndMouseState.h"
#include "Renderable.h"
#include "Camera.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

void events(sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState, sf::View& view)
{
    sf::Event event;    
    keyboardAndMouseState.resetKeyboardAndMouseStateCounters();
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) 
        {
            window.close();
        }
        if (event.type == sf::Event::Resized)
        {
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        }
        keyboardAndMouseState.updateKeyboardAndMouseState(window, view, event);
    }
}

void prepLevel(std::vector<std::unique_ptr<Updatable>> &updatables,
               std::vector<const Renderable*>& renderables,
               std::vector<const Collidable*>& collidables,
               std::vector<Selectable*>& selectables,
               b2World& physicsWorld)
{

    // put one player controlable units into the updatable and renderable vectors
    {
        Character* newCharacter = new Character(physicsWorld, static_cast<float>(rand() % 4000), static_cast<float>(rand() % 4000));
        newCharacter->setPlayerControlled(true);
        updatables.emplace_back(newCharacter);
        renderables.push_back(newCharacter);
    }

    // random units into the list, either player or non player controlled.
    for (size_t index = (static_cast<size_t>(rand() % 50) + 1); index != 0; --index)
    {
        Character* newCharacter = new Character(physicsWorld, static_cast<float>(rand() % 4000), static_cast<float>(rand() % 4000));
        updatables.emplace_back(newCharacter);
        renderables.push_back(newCharacter);

    }

    // set up the selection box as part of the level generation.
    SelectionBox* selectionBox = new SelectionBox;
    updatables.emplace_back(selectionBox);
    renderables.push_back(selectionBox);

}

constexpr float radiansToDegrees(float toConvert) {
    return toConvert * (180 / b2_pi);
}

int main()
{
    sf::Clock gameTimeClock;
    sf::Clock deltaTimeClock;
    sf::Joystick::update();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    std::string seedString = std::to_string(seed);

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "A Game? seed: " + seedString, sf::Style::Default, settings);
    mainWindow.setFramerateLimit(200);

    KeyboardAndMouseState keyboardAndMouseState;
    std::vector<std::unique_ptr<Updatable>> updatables;
    std::vector<const Renderable*> renderables;
    std::vector<const Collidable*> collidables;
    std::vector<Selectable*> selectables;

    Camera* playerView = new Camera;
    updatables.emplace_back(playerView);

    b2World physicsWorld({0.f, 0.f});
    prepLevel(updatables, renderables, collidables, selectables, physicsWorld);

    float timeStep = 1.f / 60.f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    float deltaTime = 0.f;
    while (mainWindow.isOpen())
    {
        deltaTime = deltaTimeClock.restart().asSeconds();
        events(mainWindow, keyboardAndMouseState, *playerView->getView());


        for (size_t index = 0; index != updatables.size(); ++index)
        {
            updatables[index]->update(deltaTime, mainWindow, *playerView->getView(), keyboardAndMouseState, collidables, selectables);
        }

        mainWindow.setView(*playerView->getView());
        mainWindow.clear(sf::Color::Black);
        for (size_t index = 0; index != renderables.size(); ++index)
        {
            if (renderables[index]->getDrawable() != nullptr)
            {
                mainWindow.draw(*renderables[index]->getDrawable());
            }
        }
        mainWindow.display();
        physicsWorld.Step(timeStep, velocityIterations, positionIterations);
    }
    return 0;
}