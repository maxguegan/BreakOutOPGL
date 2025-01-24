#include "GameObject.h"

GameObject::GameObject(): position(glm::vec2(0.0f)), size(glm::vec2(1.0f)), velocity(glm::vec2(0.0f)), sprite(),rotation(0.0f), color(glm::vec4(1.0f)), isSolid(false), isDestroyed(false) {

}
GameObject::GameObject(Texture tex, glm::vec2 position, glm::vec2 size,  glm::vec4 color,  float rotation, glm::vec2 velocity)
	: position(position), size(size), velocity(velocity), sprite(tex), rotation(rotation), color(color), isSolid(false), isDestroyed(false) 
{

}

void GameObject::draw(SpriteRenderer & renderer) {
	if(!isDestroyed)
		renderer.Render(this->sprite, this->position, this->size, this->rotation, this->color);
}

GameObject::~GameObject(){}