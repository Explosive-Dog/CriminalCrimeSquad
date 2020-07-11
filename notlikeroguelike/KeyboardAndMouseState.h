#pragma once

struct KeyboardAndMouseState
{
    float mouseWheelDelta = 0.f;
    bool mouseLeft = false;
    bool mouseLeftReleased = false;
    bool mouseRight = false;
    bool mouseRightReleased = false;
    bool mouseMiddle = false;
    bool mouseMiddleReleased = false;
    sf::Vector2f mousePositionInWorldWhenRightMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2f mousePositionInWorldWhenLeftMouseButtonWasLastPressed{ 0, 0 };

    sf::Vector2i mousePositionInWindowWhenLeftMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2i mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed{ 0, 0 };
    sf::Vector2i mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta{ 0, 0 };
    sf::Vector2i currentMousePosition{ 0, 0 };
    bool keyUp = false;
    bool keyDown = false;
    bool keyLeft = false;
    bool keyRight = false;
};