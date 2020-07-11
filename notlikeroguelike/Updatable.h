#pragma once
#include "KeyboardAndMouseState.h"

class Updatable 
{
public:

	virtual ~Updatable() = default;

	virtual void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState) = 0;

};