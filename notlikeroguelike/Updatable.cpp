#include "Updatable.h"

UpdateParameters::UpdateParameters(const sf::RenderWindow& mainWindow,
									sf::View& playerView,
									KeyboardAndMouseState& gameKeyboardAndMouseState,
									const std::vector<const Collidable*>& gameCollidables,
									const std::vector<Selectable*>& gameSelectables) 
									: window(mainWindow),
									view (playerView),
									keyboardAndMouseState(gameKeyboardAndMouseState),
									collidables(gameCollidables), 
									selectables (gameSelectables){


}
