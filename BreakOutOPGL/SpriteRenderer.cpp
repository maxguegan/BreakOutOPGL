#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader) : width(0.0f), height(0.0f), rotate(0.0f), color(glm::vec4(1.0f)) {
	this->shader = shader;
	this->setupQuad();
}


void SpriteRenderer::Render(Texture& tex2D,glm::vec2 position, glm::vec2 size , float rotate, glm::vec4 color) {
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,glm::vec3(position,0.0f));

	//offset la matrice pour avoir une rotation sur le centre plutôt que d'utiliser le coin haut gauche 
	model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y,0.0f));
	model = glm::rotate(model, glm::radians(rotate),glm::vec3(0.0f,0.0f,1.0f));
	model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
	
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.setMat4("model", model);
	this->shader.setVec3("aColor", color);

	glActiveTexture(GL_TEXTURE0);
	tex2D.bind();

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void SpriteRenderer::setupQuad() {
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4* sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1,&vao);
}