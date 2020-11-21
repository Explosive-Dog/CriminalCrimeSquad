#include "Camera.h"

void Camera::update(const float deltaTime, UpdateParameters& updateParameters)
{
    scrollCameraView(deltaTime, updateParameters);
    zoomCameraView(deltaTime, updateParameters);
}

sf::View* Camera::getView()
{
    return &playerView;
}

void Camera::scrollCameraView(const float deltaTime, UpdateParameters& updateParameters)
{
    if (updateParameters.keyboardAndMouseState.arrowKeyUp) {
        playerView.move(0.f, -playerView.getSize().y * deltaTime);
    }
    if (updateParameters.keyboardAndMouseState.arrowKeyDown) {
        playerView.move(0.f, playerView.getSize().y * deltaTime);
    }
    if (updateParameters.keyboardAndMouseState.arrowKeyLeft) {
        playerView.move(-playerView.getSize().x * deltaTime, 0.f);
    }
    if (updateParameters.keyboardAndMouseState.arrowKeyRight) {
        playerView.move(playerView.getSize().x * deltaTime, 0.f);
    }

    if (updateParameters.keyboardAndMouseState.mouseRight == true || updateParameters.keyboardAndMouseState.mouseMiddle)
    {
        sf::Vector2f difference = updateParameters.window.mapPixelToCoords(updateParameters.keyboardAndMouseState.currentMousePosition) - updateParameters.window.mapPixelToCoords(updateParameters.keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta);
        if (updateParameters.keyboardAndMouseState.mouseRight == true)
        {
            difference = -difference;
            updateParameters.keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta = updateParameters.keyboardAndMouseState.currentMousePosition;
        }
        else
        {
            difference = difference * deltaTime * 10.f;
        }
        playerView.move(difference);
    }
}

void Camera::zoomCameraView(const float deltaTime, UpdateParameters& updateParameters)
{
    float zoomLevel = (updateParameters.keyboardAndMouseState.mouseWheelDelta * deltaTime * 50.f) + 1.f;
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
