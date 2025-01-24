#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Shader.h"
#include "Texture.h"
class Ressource
{
public :

	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;
	static void LoadShader(const char* vsPath, const char* gsPath, const char* fsPath, std::string name);
	static void LoadTexture(const char* path, std::string name);
	static Shader& GetShader(std::string nom);
	static Texture& GetTexture(std::string nom);
	static void Clear();
private :
	Ressource();

};

