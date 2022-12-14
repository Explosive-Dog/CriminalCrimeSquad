#pragma once
#include <SFML/Graphics.hpp>

class Renderable
{
public:

    virtual ~Renderable() = default;

    virtual const sf::Drawable* getDrawable() const = 0;

    float getRenderZLevel() const {
        return m_renderZLevel;
    }

    void setRenderZLevel(float newZLevel) {
        m_renderZLevel = newZLevel;
    }

    virtual void render(sf::RenderWindow& drawingWindow) const = 0;

protected:
    float m_renderZLevel = 0.f;
};