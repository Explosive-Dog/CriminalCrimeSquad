#include "KeyboardAndMouseState.h"

void KeyboardAndMouseState::resetKeyboardAndMouseStateCounters()
{
    mouseLeftReleased = false;
    mouseRightReleased = false;
    mouseMiddleReleased = false;
    mouseWheelDelta = 0.f;
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
        if (event.key.code == sf::Keyboard::Key::D) {
            horizontal += 1.f;
            horizontalBeingPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::A) {
            horizontal += -1.f;
            horizontalBeingPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::W) {
            vertical += 1.f;
            verticalBeingPressed = true;
        }
        if (event.key.code == sf::Keyboard::Key::S) {
            vertical += -1.f;
            verticalBeingPressed = true;
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
        if (event.key.code == sf::Keyboard::Key::D) {
            horizontalBeingPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::A) {
            horizontalBeingPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::W) {
            verticalBeingPressed = false;
        }
        if (event.key.code == sf::Keyboard::Key::S) {
            verticalBeingPressed = false;
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
