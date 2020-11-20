#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Renderable.h"

class Projectile : public sf::CircleShape, public Updatable, public Renderable, public Collidable
{
public:

	Projectile(sf::Vector2f heading, sf::Vector2f momentum);

	virtual ~Projectile() = default;

	void update(const float deltaTime,
                const sf::RenderWindow& window,
                sf::View& view,
                KeyboardAndMouseState& keyboardAndMouseState,
                std::vector<const Collidable*>& vectorOfCollidables,
                std::vector<Selectable*>& vectorOfSelectables);

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

