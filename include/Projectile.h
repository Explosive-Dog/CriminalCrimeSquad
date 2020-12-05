#pragma once
/*
#include <SFML/Graphics.hpp>

#include "Renderable.h"
#include "Updatable.h"

class Projectile : public sf::CircleShape, public Updatable, public Renderable,
{
public:

    Projectile(sf::Vector2f heading, sf::Vector2f momentum);

    virtual ~Projectile() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters);

    bool getActive();

    void setActive(bool newActiveState);

    sf::Vector2f getMovementMomentum();

    void changeMovementMomentum(sf::Vector2f momentumToAccelerateBy);

    void setMovementMomentum(sf::Vector2f desiredMomentum);

    sf::Vector2f getMovementHeading();

    void setMovementHeading(sf::Vector2f desiredHeading);

private:

    sf::Vector2f movementMomentum = { 0.f,0.f };
    sf::Vector2f movementHeading = { 0.f,0.f };

    sf::Clock projectileTimer;

    bool active = true;
};
*/