#include "ParticleGenerator.h"
Particle::Particle(glm::vec2 pos, glm::vec2 velocity, float lifeTime, glm::vec4 color):position(pos),velocity(velocity),lifeTime(lifeTime),color(color) {}

ParticleGenerator::ParticleGenerator(Shader& shader, Texture& texture, unsigned int amount, ParticleGenType type) 
	: shader(shader), textureParticle(texture), nbrParticle(amount), type(type) {
	ParticleGenerator::Init();
}

void ParticleGenerator::Update(float deltaTime, GameObject& obj, unsigned int newParticle, glm::vec2 offset) {
	
		for (unsigned int i = 0; i < newParticle; i++) {
			unsigned int unusedParticle = this->LastParticle();
			this->RespawnParticle(this->particles[unusedParticle], obj, offset);
		}
	
	
	for (unsigned int i = 0; i < nbrParticle; i++) {
		Particle& particle = this->particles[i];
		
		particle.lifeTime -= deltaTime;
		if (particle.lifeTime > 0.0f) {
			
			particle.position -= particle.velocity * deltaTime;
			
			particle.color.a -= deltaTime * 2.5f;
		}
	}
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.use();
	for (unsigned int i = 0; i < nbrParticle; i++) {
		Particle& particle = this->particles[i];
		if (particle.lifeTime > 0.0f) {
			
			shader.setVec2("offset", particle.position);
			
			shader.setVec4("color", particle.color);
			
			textureParticle.bind();
			
			glBindVertexArray(vao);
			
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::Init() {
	glGenVertexArrays(1, &vao);
	float vertexes[]{

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,// triangle supérieur
		1.0f, 0.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f
	};
	unsigned int vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), &vertexes, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	for (unsigned int i = 0; i < nbrParticle; i++)
		particles.push_back(Particle());
}


unsigned int lastParticleIndex = 0;
unsigned int ParticleGenerator::LastParticle() {
	for (unsigned int i = lastParticleIndex; i < this->nbrParticle; i++) {
		if (particles[i].lifeTime <= 0.0f)
		{
			lastParticleIndex = i;
			return i;
		}
	}
	for (unsigned int i = 0; i < lastParticleIndex; i++) {
		if (particles[i].lifeTime <= 0.0f)
		{
			lastParticleIndex = i;
			return i;
		}
	}
	lastParticleIndex = 0;
	return 0;
}

void ParticleGenerator::RespawnParticle(Particle& particle, GameObject& obj, glm::vec2 offset) {
	float random = ((rand() % 100) - 50.0f) / 10.0f;
	float rColor = ((rand() % 100) / 100.0f);
	particle.position = obj.position + random + offset;
	particle.color = glm::vec4(rColor,rColor,rColor,1.0f);
	particle.lifeTime = 1.0f;
	particle.velocity = obj.velocity * 0.1f;
}