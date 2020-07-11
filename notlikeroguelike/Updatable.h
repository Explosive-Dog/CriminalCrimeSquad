#pragma once
#include "KeyboardAndMouseState.h"
#include "Collidable.h"
#include "Selectable.h"

class Updatable 
{
public:

	virtual ~Updatable() = default;

	virtual void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables) = 0;

};