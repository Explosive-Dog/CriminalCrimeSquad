#include "SelectionBox.h"

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

void SelectionBox::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState)
{
    createOrModifySelectionBox(view, keyboardAndMouseState, window);
    updateUnitsWithinOrOutsideOfSelectionBox(window, keyboardAndMouseState);
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

    float thickness = 2.f;
    //TO DO: selection box thickness depending on window zoom level.
    m_selectionBoxRectangleShape.setOutlineThickness(thickness);

    if (keyboardAndMouseState.mouseLeft == true)
    {
        sf::Vector2f currentWorldMousePosition = window.mapPixelToCoords(keyboardAndMouseState.currentMousePosition);
        m_selectionBoxRectangleShape.setPosition(keyboardAndMouseState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
        m_selectionBoxRectangleShape.setSize(currentWorldMousePosition - keyboardAndMouseState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
    }
}

// Placeholder. TODO: Selecting a unit should put an information graphic over the selectable unit which then displays HP and so on.
void SelectionBox::updateUnitsWithinOrOutsideOfSelectionBox(const sf::RenderWindow& window, KeyboardAndMouseState& keyboardAndMouseState) {
    /*
    for (size_t index = 0; index != selectables.size(); ++index)
    {
        if (selectables[index].amISelected() && keyboardAndMouseState.mouseLeftReleased) {
            selectables[index].setSelected(false);
        }
        if (m_selectionBoxRectangleShape.getGlobalBounds().intersects(selectables[index].getGlobalBounds()) && keyboardAndMouseState.mouseLeftReleased) {
            if (selectables[index].getSide() == 1)
            {
                selectables[index].setSelected(true);
            }
        }
        else if (keyboardAndMouseState.mouseLeftReleased && keyboardAndMouseState.currentMousePosition != keyboardAndMouseState.mousePositionInWindowWhenLeftMouseButtonWasLastPressed)
        {
            selectables[index].setSelected(false);
        }

        if (selectables[index].amISelected()) {
            selectables[index].setFillColor(sf::Color::Red);
        }

        if (!selectables[index].amISelected()) {
            if (selectables[index].getSide() == 1)
            {
                selectables[index].setFillColor(sf::Color::White);
            }
            if (selectables[index].getSide() == 2)
            {
                selectables[index].setFillColor(sf::Color::Yellow);
            }
        }

        if (keyboardAndMouseState.mouseRightReleased && keyboardAndMouseState.currentMousePosition == keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed && selectables[index].amISelected())
        {
            selectables[index].setMovementDestination(keyboardAndMouseState.mousePositionInWorldWhenRightMouseButtonWasLastPressed);
        }
    }*/
}