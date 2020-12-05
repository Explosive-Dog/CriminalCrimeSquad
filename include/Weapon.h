#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Joinable.h"
#include "Renderable.h"
#include "Updatable.h"

class Weapon : public Updatable, public Renderable, public Grabable
{
public:
    Weapon::Weapon(std::vector<const Grabable*>& grabables) : Grabable(grabables)
    { /* Intentionally Blank */ }
    virtual ~Weapon() = default;
protected:
};