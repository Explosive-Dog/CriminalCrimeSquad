#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Camera.h"
#include "Character.h"
#include "Joinable.h"
#include "KeyboardAndMouseState.h"
#include "Physical.h"
#include "Player.h"
#include "QuaterStaff.h"
#include "Renderable.h"
#include "SelectionBox.h"
#include "Spear.h"
#include "Sword.h"
#include "Updatable.h"
#include "Weapon.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

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
            view.setSize(static_cast<float>(event.size.width / 20), static_cast<float>(event.size.height / 20));
        }
        keyboardAndMouseState.updateKeyboardAndMouseState(window, view, event);
    }
}

void prepLevel(std::vector<std::unique_ptr<Updatable>> &updatables,
               std::vector<const Renderable*>& renderables,
               b2World& physicsWorld,
               Camera& camera,
               std::vector<const Grabable*>& grabables,
               std::vector<Physical*>& phyicsUpdatables)
{
    {
        float x = static_cast<float>(rand() % 10);
        float y = static_cast<float>(rand() % 10);
        new Player(physicsWorld, x, y, updatables, renderables, camera, phyicsUpdatables);
    }

    // random non-player controlled characters.

    for (size_t index = (static_cast<size_t>(rand() % 1) + 1); index != 0; --index)
    {
        new Character(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables);
    }

    for (size_t index = (static_cast<size_t>(rand() % 4) + 1); index != 0; --index)
    {
        auto* newCharacter = new Character(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables);
        int randWeapon = (rand() % 3);
        switch (randWeapon)
        {
        case 0:
        {
            auto* weapon1 = new QuaterStaff(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
            newCharacter->joinRightHand(weapon1); 
        }
        break;
        case 1:
        {
            auto * weapon2 = new Spear(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
            newCharacter->joinRightHand(weapon2); 
        }
        break;
        case 2:
        {
            auto * weapon3 = new Sword(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
            newCharacter->joinRightHand(weapon3);
        }
            break;
        default:
            break;
        }
    }

    new Sword(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
    new Spear(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);
    new QuaterStaff(physicsWorld, static_cast<float>(rand() % 10), static_cast<float>(rand() % 10), updatables, renderables, grabables);

    // set up the selection box as part of the level generation.
    new SelectionBox(updatables, renderables);
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
    std::vector<const Grabable*> grabables;
    std::vector<Physical*> phyicsUpdatables;

    Camera* playerView = new Camera;
    updatables.emplace_back(playerView);

    b2World physicsWorld({0.f, 0.f});
    prepLevel(updatables, renderables, physicsWorld, *playerView, grabables, phyicsUpdatables);

    int32 velocityIterations = 10;
    int32 positionIterations = 10;
    constexpr float physicsTimeStep = 1.f / 144.f;
    float deltaTime = 0.f;
    float timeSinceLastPhysicsUpdate = 0.f;
    while (mainWindow.isOpen())
    {
        deltaTime = deltaTimeClock.restart().asSeconds();
        timeSinceLastPhysicsUpdate += deltaTime;

        events(mainWindow, keyboardAndMouseState, *playerView->getView());

        UpdateParameters updateParameters(mainWindow, *playerView->getView(), keyboardAndMouseState, grabables);
        for (auto &updatable : updatables)
        {
            updatable->update(deltaTime, updateParameters);
        }

        while (timeSinceLastPhysicsUpdate > physicsTimeStep) {
            for (auto physicsObject : phyicsUpdatables) {
                physicsObject->physicsUpdate(physicsTimeStep, updateParameters);
            }
            physicsWorld.Step(physicsTimeStep, velocityIterations, positionIterations);
            timeSinceLastPhysicsUpdate -= physicsTimeStep;
        }

        mainWindow.setView(*playerView->getView());
        mainWindow.clear(sf::Color::Black);
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