#pragma once
#include <SFML/Graphics.hpp>

#include "KeyboardAndMouseState.h"
#include "Collidable.h"
#include "Selectable.h"

struct UpdateParameters final
{
	const sf::RenderWindow& window;
	sf::View& view;
	const KeyboardAndMouseState& keyboardAndMouseState;
	const std::vector<const Collidable*>& collidables;
	const std::vector<Selectable*>& selectables;

	UpdateParameters(const sf::RenderWindow& mainWindow,
		sf::View& playerView,
		const KeyboardAndMouseState& gameKeyboardAndMouseState,
		const std::vector<const Collidable*>& gameCollidables,
		const std::vector<Selectable*>& gameSelectables)
		: window(mainWindow),
		view(playerView),
		keyboardAndMouseState(gameKeyboardAndMouseState),
		collidables(gameCollidables),
		selectables(gameSelectables) 
	
	{
		// Intentionaly Blank.
	}
};

class Updatable 
{
public:

	virtual ~Updatable() = default;

	virtual void update(const float deltaTime, UpdateParameters& updateParameters) = 0;

};
