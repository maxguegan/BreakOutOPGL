#pragma once

#include "GameObject.h"
#include "Texture.h"

class BallObject : public GameObject
{
public:

	float radius;

	bool isStuck;

	BallObject();

	BallObject(Texture sprite, glm::vec2 position, float radius, glm::vec2 velocity);

	glm::vec2 Move(float deltaTime, unsigned int windowWidth);
	void reset(glm::vec2 pos, glm::vec2 velocity);

};

