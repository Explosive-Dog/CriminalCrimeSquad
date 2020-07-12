#include <SFML/Graphics.hpp>
#include "Player.h"
#include "SelectionBox.h"
#include "KeyboardAndMouseState.h"
#include "Renderable.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>

void events(sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState, sf::View& view) {
    sf::Event event;
    keyboardAndMouseState.mouseLeftReleased = false;
    keyboardAndMouseState.mouseRightReleased = false;
    keyboardAndMouseState.mouseMiddleReleased = false;
    keyboardAndMouseState.mouseWheelDelta = 0.f;
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
        if (event.type == sf::Event::EventType::MouseButtonPressed)
        {
            if (sf::Mouse::Button::Left == event.mouseButton.button && keyboardAndMouseState.mouseLeft == false)
            {
                keyboardAndMouseState.mousePositionInWindowWhenLeftMouseButtonWasLastPressed.x = event.mouseButton.x;
                keyboardAndMouseState.mousePositionInWindowWhenLeftMouseButtonWasLastPressed.y = event.mouseButton.y;
                keyboardAndMouseState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                keyboardAndMouseState.mouseLeft = true;
            }
            if (sf::Mouse::Button::Right == event.mouseButton.button || sf::Mouse::Button::Middle == event.mouseButton.button)
            {
                keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta.x = event.mouseButton.x;
                keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta.y = event.mouseButton.y;
                if (sf::Mouse::Button::Right == event.mouseButton.button && keyboardAndMouseState.mouseRight == false)
                {
                    keyboardAndMouseState.mousePositionInWorldWhenRightMouseButtonWasLastPressed = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                    keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.x = event.mouseButton.x;
                    keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.y = event.mouseButton.y;
                }
                if (sf::Mouse::Button::Right == event.mouseButton.button) 
                {
                    keyboardAndMouseState.mouseRight = true;
                }
                if (sf::Mouse::Button::Middle == event.mouseButton.button)
                {
                    keyboardAndMouseState.mouseMiddle = true;
                }

            }
        }
        if (event.type == sf::Event::EventType::MouseButtonReleased)
        {
            if (sf::Mouse::Button::Left == event.mouseButton.button)
            {
                keyboardAndMouseState.mouseLeft = false;
                keyboardAndMouseState.mouseLeftReleased = true;
            }
            if (sf::Mouse::Button::Right == event.mouseButton.button)
            {
                keyboardAndMouseState.mouseRight = false;
                keyboardAndMouseState.mouseRightReleased = true;
            }
            if (sf::Mouse::Button::Middle == event.mouseButton.button)
            {
                keyboardAndMouseState.mouseMiddle = false;
                keyboardAndMouseState.mouseMiddleReleased = true;
            }
        }
        if (event.type == sf::Event::EventType::MouseMoved)
        {
            keyboardAndMouseState.currentMousePosition.x = event.mouseMove.x;
            keyboardAndMouseState.currentMousePosition.y = event.mouseMove.y;
        }
        if (event.type == sf::Event::EventType::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Key::Up) {
                keyboardAndMouseState.keyUp = true;
            }
            if (event.key.code == sf::Keyboard::Key::Down) {
                keyboardAndMouseState.keyDown = true;
            }
            if (event.key.code == sf::Keyboard::Key::Left) {
                keyboardAndMouseState.keyLeft = true;
            }
            if (event.key.code == sf::Keyboard::Key::Right) {
                keyboardAndMouseState.keyRight = true;
            }
        }
        if (event.type == sf::Event::EventType::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Key::Up) {
                keyboardAndMouseState.keyUp = false;
            }
            if (event.key.code == sf::Keyboard::Key::Down) {
                keyboardAndMouseState.keyDown = false;
            }
            if (event.key.code == sf::Keyboard::Key::Left) {
                keyboardAndMouseState.keyLeft = false;
            }
            if (event.key.code == sf::Keyboard::Key::Right) {
                keyboardAndMouseState.keyRight = false;
            }
        }
        if (event.type == sf::Event::EventType::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                keyboardAndMouseState.mouseWheelDelta -= event.mouseWheelScroll.delta;
            }
        }
    }
    //std::cout << keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.x << " " << keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.y << std::endl;
}

//TO DO: Make a procedural terrain generator. and remove this lol.

void prepLevel(std::vector<std::unique_ptr<Updatable>> &updatables, std::vector<const Renderable*>& listOfRenderables, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables)
{

    for (size_t index = (static_cast<size_t>(rand() % 50) + 1); index != 0; --index)
    {
        PlayerClass* newCharacter = new PlayerClass({ static_cast<float>(rand() % 4000),static_cast<float>(rand() % 4000) }, (rand() % 5));
        updatables.emplace_back(newCharacter);
        listOfRenderables.push_back(newCharacter);
        listOfCollidables.push_back(newCharacter);
        if (newCharacter->getSide() == 1)
        {
            listOfSelectables.push_back(newCharacter);
        }
    }
    SelectionBox* selectionBox = new SelectionBox;

    listOfRenderables.push_back(selectionBox);
    updatables.emplace_back(selectionBox);

}

/*
void generateLevel(std::vector<int>& level)
{
    for (size_t index = 16384; index != 0; --index)
    {
        level.push_back(rand() % 5);
    }
}
*/

int main()
{
    sf::Clock gameTimeClock;
    sf::Clock deltaTimeClock;
    sf::Joystick::update();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "A Game?", sf::Style::Default, settings);
    //mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setFramerateLimit(200);

    KeyboardAndMouseState keyboardAndMouseState;
    Camera* playerView = new Camera;

    //std::vector<int> level;
    //generateLevel(level);

    std::vector<std::unique_ptr<Updatable>> listOfUpdatables;
    std::vector<const Renderable*> listOfRenderables;
    std::vector<const Collidable*> listOfCollidables;
    std::vector<Selectable*> listOfSelectables;
    prepLevel(listOfUpdatables, listOfRenderables, listOfCollidables, listOfSelectables);

    listOfUpdatables.emplace_back(playerView);

    float deltaTime;
    while (mainWindow.isOpen())
    {
        deltaTime = deltaTimeClock.restart().asSeconds();
        events(mainWindow, keyboardAndMouseState, *playerView->getView());

        for (size_t index = 0; index != listOfUpdatables.size(); ++index)
        {
            listOfUpdatables[index]->update(deltaTime, mainWindow, *playerView->getView(), keyboardAndMouseState, listOfCollidables, listOfSelectables);
        }

        mainWindow.setView(*playerView->getView());
        mainWindow.clear(sf::Color::Black);
        for (size_t index = 0; index != listOfRenderables.size(); ++index)
        {
            if (listOfRenderables[index]->getDrawable() != nullptr)
            {
                mainWindow.draw(*listOfRenderables[index]->getDrawable());
            }
        }
        mainWindow.display();
    }
    return 0;
}