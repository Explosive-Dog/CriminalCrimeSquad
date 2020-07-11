#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Renderable.h"

class PlayerClass : public sf::RectangleShape , public Updatable, public Renderable
{
public:

    PlayerClass(sf::Vector2f position, int sideIAmOn);

    virtual ~PlayerClass() = default;

    const sf::Drawable* getDrawable() const;

    void toggleSelected();

    bool amISelected();

    void setSelected(bool newValue);
    
    void setMovementDestination(sf::Vector2f);

    sf::Vector2f getMovementDestination();

    void setSide(int newSide);

    int getSide();

    void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState) override;


private:

    int sideIAmOn = 0;
    sf::Vector2f movementDestination = { 0.f, 0.f };
    bool selected = false;

};