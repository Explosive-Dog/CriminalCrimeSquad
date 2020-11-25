#pragma once
#include <SFML/Graphics.hpp>


class Renderable
{
public:

	virtual ~Renderable() = default;

	virtual const sf::Drawable* getDrawable() const = 0;

	virtual const unsigned int getRenderPriority() const = 0;

private:

};