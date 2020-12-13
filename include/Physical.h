#pragma once
#include <box2d/box2d.h>

#include "Updatable.h"

class Physical
{
public:
    Physical::Physical(std::vector<Physical*>& physicalUpdatables){
        physicalUpdatables.push_back(this);
    }
    virtual void physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters) = 0;
    virtual ~Physical() = default;
};