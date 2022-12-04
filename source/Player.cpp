#include "Player.h"

Player::Player(float positionX,
               float positionY, 
               std::vector<std::unique_ptr<Updatable>>& updatables,
               std::vector<const Renderable*>& renderables)
               : Character(positionX, positionY, updatables, renderables)

{
    m_characterRectangleShape.setFillColor(sf::Color::Red);
    isAPlayer = true;
}

void Player::update(UpdateParameters& updateParameters) {
    Character::update(updateParameters);
}