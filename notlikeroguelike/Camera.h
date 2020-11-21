#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.h"

class Camera : public Updatable
{
public:

    Camera();

    virtual ~Camera() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    sf::View* getView();

private:

    void scrollCameraView(const float deltaTime, UpdateParameters& updateParameters);

    void zoomCameraView(const float deltaTime, UpdateParameters& updateParameters);

    sf::View playerView;
};