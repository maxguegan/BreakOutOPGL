#include "BallObject.h"

BallObject::BallObject(): GameObject(), radius(12.5f), isStuck(true) {}

BallObject::BallObject(Texture sprite, glm::vec2 position, float radius, glm::vec2 velocity)
	:GameObject(sprite, position, glm::vec2(radius * 2, radius * 2), glm::vec4(1.0f), 0.0f, velocity), radius(radius), isStuck(true){}

glm::vec2 BallObject::Move(float deltaTime, unsigned int windowWidth) {
	if (!this->isStuck) {
		this->position += this->velocity * deltaTime;
		if (this->position.x <= 0.0f) {
			this->velocity.x = -this->velocity.x;
			this->position.x = 0.0f;
		}
			
		
		if (this->position.x + this->size.x >= windowWidth) {
			this->velocity.x = -this->velocity.x;
			this->position.x = windowWidth - this->size.x;
		}
		
		if (this->position.y <= 0.0f) {
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}

		return this->position;
	}
}

void BallObject::reset(glm::vec2 position, glm::vec2 velocity) {
	this->position = position;
	this->velocity = velocity;
	this->isStuck = true;
}