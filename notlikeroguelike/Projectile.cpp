#include "Projectile.h"

void Projectile::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& vectorOfCollidables, std::vector<Selectable*>& vectorOfSelectables)
{
    move({ movementMomentum.x * deltaTime, movementMomentum.y * deltaTime });
    if (5 < projectileTimer.getElapsedTime().asSeconds())
    {
        active = false;
    }
}

Projectile::Projectile(sf::Vector2f heading, sf::Vector2f momentum) {
    movementHeading = heading;
    movementMomentum = momentum;
    active = true;
    setRadius(2.f);
    setFillColor(sf::Color::Yellow);
    projectileTimer.restart();
}

bool Projectile::getActive() {
    return active;
}

void Projectile::setActive(bool newActiveState) {
    active = newActiveState;
}

sf::Vector2f Projectile::getMovementMomentum() {
    return movementMomentum;
}

void Projectile::setMovementMomentum(sf::Vector2f desiredMomentum) {
    movementMomentum = desiredMomentum;
}

sf::Vector2f Projectile::getMovementHeading() {
    return movementHeading;
}

void Projectile::changeMovementMomentum(sf::Vector2f momentumToAccelerateBy) {
    movementMomentum.x = movementMomentum.x + momentumToAccelerateBy.x;
    movementMomentum.y = movementMomentum.y + momentumToAccelerateBy.y;
}

void Projectile::setMovementHeading(sf::Vector2f desiredHeading) {
    movementHeading = desiredHeading;
}
