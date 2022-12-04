#pragma once
#include "Camera.h"
#include "Character.h"


class Player : public Character
{
public:
    Player(float positionX,
           float positionY,
           std::vector<std::unique_ptr<Updatable>>& updatables,
           std::vector<const Renderable*>& renderables);

    virtual ~Player() = default;

    void update(UpdateParameters& updateParameters) override;

private:
    bool m_useKeyAlreadyPressed = false;
};