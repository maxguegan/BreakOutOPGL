#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"

class SpriteRenderer
{
public:

	float height, width, rotate;
	glm::vec4 color;

	SpriteRenderer(Shader & shader);
	~SpriteRenderer();

	void Render(Texture &tex2D,glm::vec2 position = glm::vec2(0.0f),glm::vec2 size = glm::vec2(10.0f,10.0f), float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));
	

private:

	unsigned int vao;
	Shader shader;
	void setupQuad();
};

