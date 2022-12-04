#pragma once
#include <SFML/Graphics.hpp>

#include "Updatable.h"

class Camera : public Updatable
{
public:

    Camera();

    virtual ~Camera() = default;

    void update(UpdateParameters& updateParameters) override;

    sf::View* getView();

private:

    void Camera::scrollCameraView(UpdateParameters& updateParameters);

    void zoomCameraView(UpdateParameters& updateParameters);

    sf::View playerView;

};