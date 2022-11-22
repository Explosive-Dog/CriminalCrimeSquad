#include "SelectionBox.h"

SelectionBox::SelectionBox(std::vector<std::unique_ptr<Updatable>>& updatables,
                           std::vector<const Renderable*>& renderables) {

    m_selectionBoxRectangleShape.setOutlineColor(sf::Color::White);
    m_selectionBoxRectangleShape.setFillColor(sf::Color::Transparent);
    m_renderZLevel = std::numeric_limits<float>::max();

    updatables.emplace_back(this);
    renderables.push_back(this);
}

const sf::Drawable* SelectionBox::getDrawable() const
{
    if (m_visible == true) {
        return &m_selectionBoxRectangleShape;
    }
    return nullptr;
}

void SelectionBox::render(sf::RenderWindow& drawingWindow) const
{
    if (m_visible == true) {
        drawingWindow.draw(m_selectionBoxRectangleShape);
    }
}

void SelectionBox::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)deltaTime;
    createOrModifySelectionBox(updateParameters.view, updateParameters.gameState, updateParameters.window);
    setVisible(updateParameters.gameState);
}

void SelectionBox::setVisible(const GameState& gameState)
{
    if (gameState.mouseLeft == true)
    {
        m_visible = true;
    }
    else
    {
        m_visible = false;
    }
}

void SelectionBox::createOrModifySelectionBox(sf::View& view, const GameState& gameState, const sf::RenderWindow& window) {

    //TO DO: refine selection box thickness depending on window zoom level so its better then this implimentation here.
    float thickness = (view.getSize().x / 2.f) * (view.getSize().y / 2.f) / 60000.f;
    if (thickness > 15.f) 
    {
        thickness = 15.f;
    }
    if (thickness < 0.05f)
    {
        thickness = 0.05f;
    }
    m_selectionBoxRectangleShape.setOutlineThickness(thickness);


    if (gameState.mouseLeft == true)
    {
        sf::Vector2f currentWorldMousePosition = window.mapPixelToCoords(gameState.currentMousePosition);
        m_selectionBoxRectangleShape.setPosition(gameState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
        m_selectionBoxRectangleShape.setSize(currentWorldMousePosition - gameState.mousePositionInWorldWhenLeftMouseButtonWasLastPressed);
    }
}

