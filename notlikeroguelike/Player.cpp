#include "Player.h"
#include <SFML/Graphics.hpp>

PlayerClass::PlayerClass(sf::Vector2f position, int sideIAmOn) {
    
    setSide(sideIAmOn);
    setPosition(position);
    setSize({ 16.f,16.f });
    setOrigin(getSize().x/2,getSize().y/2 );
    setMovementDestination(getPosition());
}

const sf::Drawable* PlayerClass::getDrawable() const
{
    return this;
}

void PlayerClass::toggleSelected()
{
    selected =! selected;
}

bool PlayerClass::amISelected() 
{
    return selected;
}

void PlayerClass::setSelected(bool newSelectionValue) 
{
    selected = newSelectionValue;
}

void PlayerClass::setMovementDestination(sf::Vector2f newDestination)
{
    movementDestination = newDestination;
}

sf::Vector2f PlayerClass::getMovementDestination()
{
    return movementDestination;
}

void PlayerClass::setSide(int newSide)
{
    sideIAmOn = newSide;
}

int PlayerClass::getSide()
{
    return sideIAmOn;
}

void PlayerClass::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState)
{ 

    float moveX = 0.f, moveY = 0.f;
    moveX = (getMovementDestination().x - getPosition().x) / 2;
    moveY = (getMovementDestination().y - getPosition().y) / 2;
    move(moveX * deltaTime, moveY * deltaTime);
    /*
    for (size_t index = 0; index != characters.size() && this != &characters[index]; ++index)
    {
        if (getGlobalBounds().intersects(characters[index].getGlobalBounds()))
        {
            setPosition(getPosition() - characters[index].getPosition());
            characters[index].setPosition(getPosition() + characters[index].getPosition());
        }
    }
    */
}
