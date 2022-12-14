#pragma once
#include <SFML/Graphics.hpp>

#include "Renderable.h"
#include "Updatable.h"

//this class is likely to be removed in the furture.
class SelectionBox : public Updatable, public Renderable
{
public:
    SelectionBox(std::vector<std::unique_ptr<Updatable>>& updatables,
                 std::vector<const Renderable*>& renderables);

    virtual ~SelectionBox() = default;

    const sf::Drawable* getDrawable() const;

    void render(sf::RenderWindow& drawingWindow) const override;

    void update(UpdateParameters& updateParameters) override;

private:
    void setVisible(const GameState& gameState);

    sf::RectangleShape m_selectionBoxRectangleShape;

    void createOrModifySelectionBox(sf::View& view, const GameState& gameState, const sf::RenderWindow& window);

    void updateUnitsWithinOrOutsideOfSelectionBox(const sf::RenderWindow& window, GameState& gameState);

    bool m_visible = false;
};