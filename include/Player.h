#pragma once
#include "Camera.h"
#include "Character.h"
#include "Joinable.h"
#include "Physical.h"

class Player : public Character , public Physical
{
public:
    Player(b2World& world,
           float positionX,
           float positionY,
           std::vector<std::unique_ptr<Updatable>>& updatables,
           std::vector<const Renderable*>& renderables,
           Camera& camera,
           std::vector<Physical*>& physicalUpdatables);

    virtual ~Player() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    virtual void physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters) override;

private:
    Camera& m_camera;
    bool m_useKeyAlreadyPressed = false;
};