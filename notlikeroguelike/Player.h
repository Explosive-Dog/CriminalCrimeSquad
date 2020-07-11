#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Renderable.h"


class PlayerClass : public sf::RectangleShape , public Updatable, public Renderable, public Selectable, public Collidable
{
public:

    PlayerClass(sf::Vector2f position, int sideIAmOn);

    virtual ~PlayerClass() = default;

    const sf::Drawable* getDrawable() const;
    
    void setMovementDestination(sf::Vector2f);

    sf::Vector2f getMovementDestination();

    void setSide(int newSide);

    int getSide();

    sf::FloatRect getGlobalBounds() const override;

    void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables) override;


private:

    int m_sideIAmOn = 0;
    sf::Vector2f m_movementDestination = { 0.f, 0.f };

};