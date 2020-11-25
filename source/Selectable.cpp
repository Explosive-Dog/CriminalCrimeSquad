#include "Selectable.h"

bool Selectable::getSelected() const
{
    return m_selected;
}

void Selectable::setSelected(bool newSelectionValue)
{
    m_selected = newSelectionValue;
}