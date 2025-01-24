#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Ressource.h"
class GameLevels
{
public:
	std::vector<GameObject> bricks;

	GameLevels();

	void LoadLevels(const char* path, unsigned int levelWidth, unsigned int levelHeight);

	void DrawLevels(SpriteRenderer & renderer);

	bool IsOver();

private:
	void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

};

