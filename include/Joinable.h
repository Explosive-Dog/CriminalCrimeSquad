#pragma once
#include <box2d/box2d.h>

class Joinable 
{
public:
    virtual ~Joinable() = default;
    virtual b2Body* getB2Body() const = 0;
};

//this class should be used if you want to be able to pick it up, since this is the class that will have a list associated to it.
class Grabable : public Joinable
{
public:
    virtual ~Grabable() = default;
};

