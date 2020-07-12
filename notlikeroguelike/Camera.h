#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.h"

class Camera : public Updatable
{
public:

    Camera();

    virtual ~Camera() = default;

    void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables) override;

    sf::View* getView();

private:

    void scrollCameraView(const float deltaTime, const sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState);

    void zoomCameraView(const float deltaTime, const KeyboardAndMouseState& keyboardAndMouseState);

    sf::View playerView;
};