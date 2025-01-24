#pragma once
#include <iostream>
#include <glad/glad.h>
#include "Shader.h"
class FrameBuffer
{
public:
	unsigned int frameID, texID, quadVAO;
	Shader& shader;
	FrameBuffer(const int &screenWidth, const int &screenHeight,Shader & shader);
	~FrameBuffer();
	void const Bind();
	void Draw();
	private:
		unsigned int rbo, quadVBO;
		void setVAO();
};

