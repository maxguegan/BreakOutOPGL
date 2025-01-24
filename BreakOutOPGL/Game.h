#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include "glm/geometric.hpp"
#include "Ressource.h"
#include "SpriteRenderer.h"
#include "GameLevels.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "FrameBuffer.h"

enum GameState
{
	PAUSE,
	ACTIVE,
	GAMEOVER
};
enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};
class Game
{
public:

	//game data
	GameState gameState;
	std::vector<GameLevels> levels;

	unsigned int level;
	

	//size of game window
	unsigned int width, height;

	//player stat
	GameObject* player;
	const glm::vec2 playerSize = glm::vec2(100.0f, 20.0f);
	const float playerSpeed = 500.0f;

	//ball stat
	BallObject* ball;
	const float ballRadius = 12.5f;
	const glm::vec2 ballVelocity = glm::vec2(100.0f, -350.0f);

	//which keys are being pressed
	bool keys[1024];

	Game(unsigned int width, unsigned int height);

	~Game();
	typedef std::tuple<bool, DIRECTION, glm::vec2> colVal;
	void Init();
	void ProcessInput(float& deltaTime);
	void Update(float &deltaTime);
	void Render();
	bool CheckCollisions(GameObject& prems, GameObject& dos);
	colVal CheckBallCollisions(BallObject& ball, GameObject& obj);
	void DoCollisions();
	void Reset();
	DIRECTION GetDirection(glm::vec2(target));
};

