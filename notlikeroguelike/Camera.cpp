#include "Camera.h"

void Camera::update(const float deltaTime, 
                    const sf::RenderWindow& window,
                    sf::View& view,
                    KeyboardAndMouseState& keyboardAndMouseState,
                    std::vector<const Collidable*>& vectorOfCollidables,
                    std::vector<Selectable*>& vectorOfSelectables)
{
    scrollCameraView(deltaTime, window, keyboardAndMouseState);
    zoomCameraView(deltaTime, keyboardAndMouseState);
}

sf::View* Camera::getView()
{
    return &playerView;
}

void Camera::scrollCameraView(const float deltaTime, const sf::RenderWindow& window,KeyboardAndMouseState& keyboardAndMouseState)
{
    if (keyboardAndMouseState.arrowKeyUp) {
        playerView.move(0.f, -playerView.getSize().y * deltaTime);
    }
    if (keyboardAndMouseState.arrowKeyDown) {
        playerView.move(0.f, playerView.getSize().y * deltaTime);
    }
    if (keyboardAndMouseState.arrowKeyLeft) {
        playerView.move(-playerView.getSize().x * deltaTime, 0.f);
    }
    if (keyboardAndMouseState.arrowKeyRight) {
        playerView.move(playerView.getSize().x * deltaTime, 0.f);
    }

    if (keyboardAndMouseState.mouseRight == true || keyboardAndMouseState.mouseMiddle)
    {
        sf::Vector2f difference = window.mapPixelToCoords(keyboardAndMouseState.currentMousePosition) - window.mapPixelToCoords(keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta);
        if (keyboardAndMouseState.mouseRight == true)
        {
            difference = -difference;
            keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta = keyboardAndMouseState.currentMousePosition;
        }
        else
        {
            difference = difference * deltaTime * 10.f;
        }
        playerView.move(difference);
    }
}

void Camera::zoomCameraView(const float deltaTime, const KeyboardAndMouseState& keyboardAndMouseState)
{
    float zoomLevel = (keyboardAndMouseState.mouseWheelDelta * deltaTime * 50.f) + 1.f;
    if (zoomLevel > 1.4f)
    {
        zoomLevel = 1.4f;
    }
    else if (zoomLevel < 0.6f)
    {
        zoomLevel = 0.6f;
    }
    playerView.zoom(zoomLevel);
}

Camera::Camera()
{
    playerView.setSize({ 800.f, 600.f });
}
