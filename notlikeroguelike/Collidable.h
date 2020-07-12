#pragma once
#include <SFML/Graphics.hpp>

class Collidable
{
public:
	virtual ~Collidable() = default;

	virtual  sf::FloatRect getCollidable()const = 0;

	virtual void onCollide(const Collidable*) = 0;

	virtual void checkCollidables(std::vector<const Collidable*> listOfCollidables) = 0;

protected:
	bool m_colliding = false;
};