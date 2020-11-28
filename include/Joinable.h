#pragma once

#include <box2d/box2d.h>


class Joinable 
{
public:

    virtual ~Joinable() = default;

    virtual b2Body* getB2Body() = 0;

};

