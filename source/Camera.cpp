#include "Camera.h"

#include <iostream>

void Camera::update(const float deltaTime, UpdateParameters& updateParameters)
{
    zoomCameraView(deltaTime, updateParameters);
    scrollCameraView(deltaTime, updateParameters);
}

sf::View* Camera::getView()
{
    return &playerView;
}

void Camera::scrollCameraView(const float deltaTime, UpdateParameters& updateParameters)
{

    if (updateParameters.gameState.mouseRight == true || updateParameters.gameState.mouseMiddle == true)
    {
        sf::Vector2f distanceToMoveCameraBy = { 0, 0 };
        if (updateParameters.gameState.mouseRight == true)
        {
            distanceToMoveCameraBy = updateParameters.window.mapPixelToCoords(updateParameters.gameState.currentMousePosition);
            distanceToMoveCameraBy = distanceToMoveCameraBy - updateParameters.gameState.mousePositionInWorldWhenRightMouseButtonWasLastPressed;
            distanceToMoveCameraBy = -distanceToMoveCameraBy;
        }
        else
        {
            distanceToMoveCameraBy = updateParameters.window.mapPixelToCoords(updateParameters.gameState.currentMousePosition);
            distanceToMoveCameraBy = distanceToMoveCameraBy - updateParameters.window.mapPixelToCoords(updateParameters.gameState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta);
            distanceToMoveCameraBy = distanceToMoveCameraBy * deltaTime * 10.f;
        }
        playerView.move(distanceToMoveCameraBy);
    }
}

void Camera::zoomCameraView(const float deltaTime, UpdateParameters& updateParameters)
{
    float zoomLevel = (updateParameters.gameState.mouseWheelDelta * deltaTime * 50.f) + 1.f;
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
    playerView.setSize({ 40.f, 30.f });
    playerView.setCenter({ 0.f , 0.f });
}