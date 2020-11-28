#pragma once
#include <SFML/Graphics.hpp>


class Renderable
{
public:

	virtual ~Renderable() = default;

	virtual const sf::Drawable* getDrawable() const = 0;

	const unsigned int getRenderPriority() {
		return m_renderPriority;
	}

protected:

	unsigned int m_renderPriority = 99;
};