#pragma once
#include <SFML/Graphics.hpp>

struct KeyboardAndMouseState
{
    void resetKeyboardAndMouseStateCounters();

    void updateKeyboardAndMouseState(sf::RenderWindow& window, sf::View& view, sf::Event& event);

    float mouseWheelDelta = 0.f;
    bool mouseLeft = false;
    bool mouseLeftReleased = false;
    bool mouseRight = false;
    bool mouseRightReleased = false;
    bool mouseMiddle = false;
    bool mouseMiddleReleased = false;
    bool horizontalBeingPressed = false;
    bool verticalBeingPressed = false;

    bool spaceBarPressed = false;
    bool useKeyPressed = false;

    bool moveLeftKeyPressed = false;
    bool moveRightKeyPressed = false;
    bool moveDownKeyPressed = false;
    bool moveUpKeyPressed = false;
    bool rotateClockwise = false;
    bool rotateCounterClockwise = false;

    sf::Vector2f mousePositionInWorldWhenRightMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2f mousePositionInWorldWhenLeftMouseButtonWasLastPressed{ 0, 0 };

    sf::Vector2i mousePositionInWindowWhenLeftMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2i mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2i mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta{ 0, 0 };
    sf::Vector2i currentMousePosition{ 0, 0 };

    float horizontal = 0.f;
    float vertical = 0.f;

    bool arrowKeyUp = false;
    bool arrowKeyDown = false;
    bool arrowKeyLeft = false;
    bool arrowKeyRight = false;
};