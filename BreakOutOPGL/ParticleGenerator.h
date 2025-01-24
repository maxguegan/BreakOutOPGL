#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
enum ParticleGenType
{
	BURST,
	LOOP

};
struct Particle
{
	glm::vec2 position;
	glm::vec2 velocity;

	glm::vec4 color;

	float lifeTime;

	Particle(glm::vec2 pos = glm::vec2(0.0f), glm::vec2 velocity = glm::vec2(0.0f), float lifeTime = 1.0f,
		glm::vec4 color = glm::vec4(1.0f));
};
class ParticleGenerator
{
public:
	std::vector<Particle> particles;

	ParticleGenerator(Shader & shader, Texture & texture,unsigned int amount, ParticleGenType type = LOOP);
	void Update(float deltaTime, GameObject & obj, unsigned int newParticle, glm::vec2 offset = glm::vec2(0.0f));
	void Draw();

private:
	bool hasSpawned = false;
	ParticleGenType type;
	unsigned int vao;
	unsigned int nbrParticle;
	Shader shader;
	Texture textureParticle;
	void Init();
	void RespawnParticle(Particle & particle, GameObject & obj, glm::vec2 offset = glm::vec2(0.0f));
	unsigned int LastParticle();
};

