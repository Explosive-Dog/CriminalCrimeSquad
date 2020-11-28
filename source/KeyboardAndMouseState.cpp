#include "KeyboardAndMouseState.h"

#include <iostream>

void KeyboardAndMouseState::resetKeyboardAndMouseStateCounters()
{
    mouseLeftReleased = false;
    mouseRightReleased = false;
    mouseMiddleReleased = false;
    mouseWheelDelta = 0.f;
    horizontal = 0.f;
    vertical = 0.f;
}

void KeyboardAndMouseState::updateKeyboardAndMouseState(sf::RenderWindow& window, sf::View& view, sf::Event& event)
{
    if (event.type == sf::Event::EventType::MouseButtonPressed)
    {
        if (sf::Mouse::Button::Left == event.mouseButton.button && mouseLeft == false)
        {
            mousePositionInWindowWhenLeftMouseButtonWasLastPressed.x = event.mouseButton.x;
            mousePositionInWindowWhenLeftMouseButtonWasLastPressed.y = event.mouseButton.y;
            mousePositionInWorldWhenLeftMouseButtonWasLastPressed = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            mouseLeft = true;
        }
        if (sf::Mouse::Button::Right == event.mouseButton.button || sf::Mouse::Button::Middle == event.mouseButton.button)
        {
            mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta.x = event.mouseButton.x;
            mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta.y = event.mouseButton.y;
            if (sf::Mouse::Button::Right == event.mouseButton.button && mouseRight == false)
            {
                mousePositionInWorldWhenRightMouseButtonWasLastPressed = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.x = event.mouseButton.x;
                mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed.y = event.mouseButton.y;
            }
            if (sf::Mouse::Button::Right == event.mouseButton.button)
            {
                mouseRight = true;
            }
            if (sf::Mouse::Button::Middle == event.mouseButton.button)
            {
                mouseMiddle = true;
            }

        }
    }
    if (event.type == sf::Event::EventType::MouseButtonReleased)
    {
        if (sf::Mouse::Button::Left == event.mouseButton.button)
        {
            mouseLeft = false;
            mouseLeftReleased = true;
        }
        if (sf::Mouse::Button::Right == event.mouseButton.button)
        {
            mouseRight = false;
            mouseRightReleased = true;
        }
        if (sf::Mouse::Button::Middle == event.mouseButton.button)
        {
            mouseMiddle = false;
            mouseMiddleReleased = true;
        }
    }
    if (event.type == sf::Event::EventType::MouseMoved)
    {
        currentMousePosition.x = event.mouseMove.x;
        currentMousePosition.y = event.mouseMove.y;
    }
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Up) {
            arrowKeyUp = true;
        }
        if (event.key.code == sf::Keyboard::Key::Down) {
            arrowKeyDown = true;
        }
        if (event.key.code == sf::Keyboard::Key::Left) {
            arrowKeyLeft = true;
        }
        if (event.key.code == sf::Keyboard::Key::Right) {
            arrowKeyRight = true;
        }
        if (event.key.code == sf::Keyboard::Key::Space) {
            spaceBarPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::D) {
            horizontalBeingPressed = true;
            moveRightKeyPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::A) {
            horizontalBeingPressed = true;
            moveLeftKeyPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::W) {
            verticalBeingPressed = true;
            moveUpKeyPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::S) {
            verticalBeingPressed = true;
            moveDownKeyPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::Q) {
            rotateCounterClockwise = true;
        }
        if (event.key.code == sf::Keyboard::Key::E) {
            rotateClockwise = true;
        }

    }
    if (event.type == sf::Event::EventType::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Key::Up) {
            arrowKeyUp = false;
        }
        if (event.key.code == sf::Keyboard::Key::Down) {
            arrowKeyDown = false;
        }
        if (event.key.code == sf::Keyboard::Key::Left) {
            arrowKeyLeft = false;
        }
        if (event.key.code == sf::Keyboard::Key::Right) {
            arrowKeyRight = false;
        }
        if (event.key.code == sf::Keyboard::Key::Space) {
            spaceBarPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::D) {
            horizontalBeingPressed = false;
            moveRightKeyPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::A) {
            horizontalBeingPressed = false;
            moveLeftKeyPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::W) {
            verticalBeingPressed = false;
            moveUpKeyPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::S) {
            verticalBeingPressed = false;
            moveDownKeyPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::Q) {
            rotateCounterClockwise = false;
        }
        if (event.key.code == sf::Keyboard::Key::E) {
            rotateClockwise = false;
        }
    }
    if (event.type == sf::Event::EventType::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            mouseWheelDelta -= event.mouseWheelScroll.delta;
        }
    }
}