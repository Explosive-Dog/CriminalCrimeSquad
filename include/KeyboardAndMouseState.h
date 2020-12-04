#pragma once
#include <SFML/Graphics.hpp>

#include <map>

class KeyboardAndMouseState final
{
public:
    enum class KeyName {
        moveLeft,
        moveDown,
        moveRight,
        moveUp,
        rotateClockwise,
        rotateCounterClockwise,
        use
    };

    void resetKeyboardAndMouseStateCounters();

    void updateKeyboardAndMouseState(sf::RenderWindow& window, sf::View& view, sf::Event& event);

    bool getKeyPressed(KeyName keyName) const;

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

private:
    std::map<sf::Keyboard::Key, bool> keysPressed;
};