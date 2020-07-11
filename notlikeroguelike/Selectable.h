#pragma once
#include <SFML/Graphics.hpp>

class Selectable
{
public:
	virtual ~Selectable() = default;

	virtual sf::FloatRect getGlobalBounds() const = 0;

	bool getSelected() const;

	void setSelected(bool newValue);

private:
	bool m_selected = false;
};
