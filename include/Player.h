#pragma once

#include "Camera.h"
#include "Character.h"

class Player : public Character
{
public:
	Player(b2World& world,
		  float positionX,
		  float positionY,
		  std::vector<std::unique_ptr<Updatable>>& updatables,
		  std::vector<const Renderable*>& renderables,
		  Camera& camera);
	virtual ~Player() = default;
	void update(const float deltaTime, UpdateParameters& updateParameters) override;
private:
	Camera& m_camera;
};