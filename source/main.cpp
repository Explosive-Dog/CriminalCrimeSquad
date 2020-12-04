#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Camera.h"
#include "Character.h"
#include "Joinable.h"
#include "KeyboardAndMouseState.h"
#include "Player.h"
#include "Renderable.h"
#include "SelectionBox.h"
#include "Updatable.h"
#include "Weapon.h"

#include <algorithm>
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
            //view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        }
        keyboardAndMouseState.updateKeyboardAndMouseState(window, view, event);
    }
}

void prepLevel(std::vector<std::unique_ptr<Updatable>> &updatables,
               std::vector<const Renderable*>& renderables,
               std::vector<const Collidable*>& collidables,
               std::vector<Selectable*>& selectables,
               b2World& physicsWorld,
               Camera& camera,
               std::vector<const Grabable*>& grabables)
{
    {
        float x = static_cast<float>(rand() % -10);
        float y = static_cast<float>(rand() % -10);
        auto* newCharacter = new Player(physicsWorld, x, y, updatables, renderables, camera);
    }

    // random non-player controlled characters.
    for (size_t index = (static_cast<size_t>(rand() % 50) + 1); index != 0; --index)
    {
        Character* newCharacter = new Character(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables);
    }

    for (size_t index = (static_cast<size_t>(rand() % 10) + 2); index != 0; --index)
    {
        Weapon* spear = new Weapon(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
    }

    // set up the selection box as part of the level generation.
    SelectionBox* selectionBox = new SelectionBox(updatables, renderables);
}

constexpr float radiansToDegrees(float radiansToConvert) {
    return radiansToConvert * (180 / b2_pi);
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
    mainWindow.setKeyRepeatEnabled(false);
    KeyboardAndMouseState keyboardAndMouseState;
    std::vector<std::unique_ptr<Updatable>> updatables;
    std::vector<const Renderable*> renderables;
    std::vector<const Collidable*> collidables;
    std::vector<const Grabable*> grabables;
    std::vector<Selectable*> selectables;

    Camera* playerView = new Camera;
    updatables.emplace_back(playerView);

    b2World physicsWorld({0.f, 0.f});
    prepLevel(updatables, renderables, collidables, selectables, physicsWorld, *playerView, grabables);

    float timeStep = 1.f / 144.f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    float deltaTime = 0.f;
    while (mainWindow.isOpen())
    {
        deltaTime = deltaTimeClock.restart().asSeconds();

        events(mainWindow, keyboardAndMouseState, *playerView->getView());

        UpdateParameters updateParameters(mainWindow, *playerView->getView(), keyboardAndMouseState, collidables, selectables, grabables);
        for (auto &updatable : updatables)
        {
            updatable->update(deltaTime, updateParameters);
        }

        auto renderPriority = [](const Renderable* x, const Renderable* y) {return x->getRenderZLevel() < y->getRenderZLevel();};
        std::stable_sort(renderables.begin(), renderables.end(), renderPriority);

        mainWindow.setView(*playerView->getView());
        mainWindow.clear(sf::Color::Black);
        for (auto &renderable : renderables)
        {
            if (renderable->getDrawable() != nullptr)
            {
                mainWindow.draw(*renderable->getDrawable());
            }
        }
        mainWindow.display();

        physicsWorld.Step(timeStep, velocityIterations, positionIterations);
        //system("cls");
    }
    return 0;
}