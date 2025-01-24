#pragma once
#include <iostream>
#include "stb_image.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
class Texture
{
public :
	unsigned int idTex;

	int width, height;
	
	unsigned int format_tex, format_image;

	unsigned int Wrap_S; // wrapping mode on S axis
	unsigned int Wrap_T; // wrapping mode on T axis
	unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
	unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

	Texture();

	void generate(const char* path);

	void bind();

};

