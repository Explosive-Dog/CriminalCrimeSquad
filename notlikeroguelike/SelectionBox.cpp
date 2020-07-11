#include "SelectionBox.h"
#include <iostream>

SelectionBox::SelectionBox() {

    m_selectionBoxRectangleShape.setOutlineColor(sf::Color::White);
    m_selectionBoxRectangleShape.setFillColor(sf::Color::Transparent);

}

const sf::Drawable* SelectionBox::getDrawable() const
{
    if (m_visible == true) {
        return &m_selectionBoxRectangleShape;
    }
    return nullptr;
}

void SelectionBox::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables)
{
    createOrModifySelectionBox(view, keyboardAndMouseState, window);
    updateUnitsWithinOrOutsideOfSelectionBox(window, keyboardAndMouseState, listOfSelectables);
    setVisible(keyboardAndMouseState);
}

void SelectionBox::setVisible(const KeyboardAndMouseState& keyboardAndMouseState)
{
    if (keyboardAndMouseState.mouseLeft == true)
    {
        m_visible = true;
    }
    else
    {
        m_visible = false;
    }
}

void SelectionBox::createOrModifySelectionBox(sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, const sf::RenderWindow& window) {

    //TO DO: refine selection box thickness depending on window zoom level so its better then this implimentation here.
    float thickness = (view.getSize().x / 2.f) * (view.getSize().y / 2.f) / 60000.f;
    if (thickness > 15.f) 
    {
        thickness = 15.f;
    }
    if (thickness < 1.f)
    {
        thickness = 1.f;
    }
    m_selectionBoxRectangleShape.setOutlineThickness(thickness);


    if (keyboardAndMouseState.mouseLeft == true)
    {
        sf::Vector2f currentWorldMousePosition = window.mapPixelToCoords(keyboardAndMouseState.currentMousePosition);
        m_selectionBoxRectangleShape.setPosition(keyboardAndMouseState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
        m_selectionBoxRectangleShape.setSize(currentWorldMousePosition - keyboardAndMouseState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
    }
}

// Placeholder. TODO: Selecting a unit should put an information graphic over the selectable unit which then displays HP and so on.
void SelectionBox::updateUnitsWithinOrOutsideOfSelectionBox(const sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState, std::vector<Selectable*> &selectables) {

    for (size_t index = 0; index != selectables.size(); ++index)
    {
        if (selectables[index]->getSelected() && keyboardAndMouseState.mouseLeftReleased)
        {
            selectables[index]->setSelected(false);
        }
        if (m_selectionBoxRectangleShape.getGlobalBounds().intersects(selectables[index]->getGlobalBounds()) && keyboardAndMouseState.mouseLeftReleased)
        {
            selectables[index]->setSelected(true);
        }
        else if (keyboardAndMouseState.mouseLeftReleased && keyboardAndMouseState.currentMousePosition != keyboardAndMouseState.mousePositionInWindowWhenLeftMouseButtonWasLastPressed)
        {
            selectables[index]->setSelected(false);
        }
    }
}