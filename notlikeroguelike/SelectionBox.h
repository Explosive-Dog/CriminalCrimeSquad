#pragma once
#include <SFML/Graphics.hpp>
#include "KeyboardAndMouseState.h"
#include "Player.h"
#include "Updatable.h"
#include "Renderable.h"

class SelectionBox : public Updatable, public Renderable
{

public:

	SelectionBox();

	virtual ~SelectionBox() = default;

	const sf::Drawable* getDrawable() const;

	void update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState) override;

private:

	void setVisible(const KeyboardAndMouseState& keyboardAndMouseState);

	sf::RectangleShape m_selectionBoxRectangleShape;

	void createOrModifySelectionBox(sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, const sf::RenderWindow& window);

	// Placeholder. TODO: Selecting a unit should put an information graphic over the selectable unit which then displays HP and so on.
	void updateUnitsWithinOrOutsideOfSelectionBox(const sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState);

	bool m_visible = false;

};

