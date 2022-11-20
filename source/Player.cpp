#include "Player.h"

Player::Player(float positionX,
               float positionY, 
               std::vector<std::unique_ptr<Updatable>>& updatables,
               std::vector<const Renderable*>& renderables,
               Camera& camera)
               : Character(positionX, positionY, updatables, renderables),
               m_camera(camera)
{
    m_characterRectangleShape.setFillColor(sf::Color::Red);
    isAPlayer = true;
}

void Player::update(const float deltaTime, UpdateParameters& updateParameters) {
    Character::update(deltaTime, updateParameters);
    m_camera.getView()->setCenter(m_characterRectangleShape.getPosition());
}