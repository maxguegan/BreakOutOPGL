#include "Game.h"
SpriteRenderer * renderer;
ParticleGenerator* particles;

FrameBuffer * fBuffer;

float clamp(float val, float min, float max);


Game::Game(unsigned int width, unsigned int height) : width(width), height(height), gameState(GAMEOVER), keys(){
	
}

Game::~Game() {
	free(renderer);
	free(this->player);
	free(this->ball);
	free(particles);
	free(fBuffer);
}

void Game::Init() {
	Ressource::LoadShader("../Shader/RenderShader.vs", NULL, "../Shader/RenderShader.fs","shaderSprite");
	Ressource::LoadShader("../Shader/ParticleShader.vs", NULL, "../Shader/ParticleShader.fs", "particleShader");
	Ressource::LoadShader("../Shader/PostShader.vs", NULL, "../Shader/PostShader.fs", "postShader");
	Ressource::LoadTexture("../texture/floor.png","floor");
	Ressource::LoadTexture("../texture/block.png", "block");
	Ressource::LoadTexture("../texture/block_solid.png", "solidBlock");
	Ressource::LoadTexture("../texture/background.jpg", "background");
	Ressource::LoadTexture("../texture/paddle.png", "paddle");
	Ressource::LoadTexture("../texture/awesomeface.png", "ball");
	Ressource::LoadTexture("../texture/particle.png", "particle");

	glm::mat4 projection = glm::ortho(0.0f,static_cast<float>(width), static_cast<float>(height),0.0f,-1.0f,1.0f);
	Ressource::GetShader("shaderSprite").use();
	Ressource::GetShader("shaderSprite").setInt("aTexture",0);
	Ressource::GetShader("shaderSprite").setMat4("projection", projection);
	Ressource::GetShader("particleShader").use();
	Ressource::GetShader("particleShader").setInt("aTexture", 0);
	Ressource::GetShader("particleShader").setMat4("projection", projection);
	GameLevels first;
	fBuffer = new FrameBuffer(width, height,Ressource::GetShader("postShader"));
	player = new GameObject(Ressource::GetTexture("paddle"),glm::vec2(this->width / 2 - playerSize.x / 2, this->height - playerSize.y), playerSize
		,glm::vec4(1.0f));
	glm::vec2 ballPos = player->position + glm::vec2(playerSize.x / 2.0f - ballRadius, - ballRadius * 2.0f);
	ball = new BallObject(Ressource::GetTexture("ball"), ballPos, ballRadius, ballVelocity);
	first.LoadLevels("../level/standart.txt", this->width, this->height / 2);
	this->levels.push_back(first);
	this->level = 0;
	renderer = new SpriteRenderer(Ressource::GetShader("shaderSprite"));
	particles = new ParticleGenerator(Ressource::GetShader("particleShader"), Ressource::GetTexture("particle"), 1000, LOOP);

}

void Game::Update(float& deltaTime) {
	this->ball->Move(deltaTime, this->width);
	particles->Update(deltaTime, *this->ball, 1, glm::vec2(ball->radius / 2.0f));

	if (ball->position.y >= height) {
		this->Reset();
	}
	DoCollisions();
}

void Game::Render() {
	fBuffer->Bind();
	if (this->gameState == ACTIVE) {
		renderer->Render(Ressource::GetTexture("background"), glm::vec2(0.0f), glm::vec2(this->width, this->height),
			0.0f, glm::vec4(1.0f));
		this->levels[this->level].DrawLevels(*renderer);

		this->player->draw(*renderer);
		particles->Draw();
		this->ball->draw(*renderer);

	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	fBuffer->Draw();
}

void Game::ProcessInput(float& deltaTime) {

	if (this->gameState == ACTIVE) {
		float movement = playerSpeed * deltaTime;
		if (keys[GLFW_KEY_A]) {
			
			if (player->position.x > 0.0f)
			{
				player->position.x -= movement;
				if (ball->isStuck)
					ball->position.x -= movement;
			}
				
		}
		if (keys[GLFW_KEY_D]) {
			if (player->position.x < this->width - player->size.x) {
				player->position.x += movement;
				if (ball->isStuck)
					ball->position.x += movement;
			}
				
		}
		if (keys[GLFW_KEY_SPACE])
			ball->isStuck = false;
	}
}
void Game::Reset() {
	for (GameObject& obj : this->levels[this->level].bricks)
		obj.isDestroyed = false;
	player->position = glm::vec2(this->width / 2 - playerSize.x / 2, this->height - playerSize.y);
	glm::vec2 ballPos = player->position + glm::vec2(playerSize.x / 2.0f - ballRadius, -ballRadius * 2.0f);
	ball->reset(ballPos,ballVelocity);
}


bool Game::CheckCollisions(GameObject& prems, GameObject& dos) {
	bool colX = prems.position.x + prems.size.x >= dos.position.x && prems.position.x <= dos.position.x + dos.size.x;
	bool colY = prems.position.y + prems.size.y >= dos.position.y && prems.position.y <= dos.position.y + dos.size.y;
	return colX && colY;
}
Game::colVal Game::CheckBallCollisions(BallObject& ball, GameObject& obj) {

	glm::vec2 centerBall = ball.position + ball.radius;
	//get center of object (likely a box)
	glm::vec2 centerObj = glm::vec2(obj.position.x + obj.size.x / 2, obj.position.y + obj.size.y / 2);
	//get vector that's the translation of the center of the object to the ball
	glm::vec2 centerToCenter = centerBall - centerObj;
	//clamp the value of the previous vector to the edge of the box, get the closest point of the box to the ball
	glm::vec2 closestPoint = centerObj + glm::vec2(clamp(centerToCenter.x, -(obj.size.x / 2), obj.size.x / 2),
		clamp(centerToCenter.y, -(obj.size.y / 2), obj.size.y / 2));
	glm::vec2 dist = closestPoint- centerBall  ;
	if (glm::length(dist) < ball.radius) {
		return std::make_tuple(true, GetDirection(dist), dist);
	}
	else {
		return std::make_tuple(false, UP, glm::vec2(0.0f));
	}
}
void Game::DoCollisions() {
	colVal val = CheckBallCollisions(*ball, *player);
	if (std::get<0>(val) && !ball->isStuck) {
		float center = player->position.x + player->size.x / 2;
		float distance = (ball->position.x + ball->radius) - center;
		float percentage = distance / (player->size.x / 2.0f);

		float power = 2.0f;
		glm::vec2 oldVelocity = ball->velocity;

		ball->velocity.x = ballVelocity.x * percentage * power;
		ball->velocity.y = -1.0f * std::abs(ball->velocity.y);
		ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
	}
		
	else {
		for (GameObject& obj : this->levels[this->level].bricks) {
			if (!obj.isDestroyed) {
				val = CheckBallCollisions(*ball, obj);
				if (std::get<0>(val)) {
					
					if (std::get<1>(val) == RIGHT || std::get<1>(val) == LEFT) {
						float offset = ball->radius - std::abs(std::get<2>(val).x);
						if (std::get<1>(val) == RIGHT)
							ball->position.x += offset;
						else ball->position.x -= offset;
						ball->velocity.x = -ball->velocity.x;
						if(!obj.isSolid)
							obj.isDestroyed = true;
					}
					else {
						float offset = ball->radius - std::abs(std::get<2>(val).y);
						if (std::get<1>(val) == UP)
							ball->position.y -= offset;
						else ball->position.y += offset;
						ball->velocity.y = -ball->velocity.y;
						if (!obj.isSolid)
							obj.isDestroyed = true;
					}
					
				}
			}
		}
	}
	
}
float clamp(float val, float min, float max) {
	return std::max(min, std::min(max, val));
}

DIRECTION Game::GetDirection(glm::vec2 target) {

	glm::vec2 compass[] = {
		glm::vec2(1.0f,0.0f),
		glm::vec2(-1.0f,0.0f),
		glm::vec2(0.0f,1.0f),
		glm::vec2(0.0f,-1.0f)
	};
	float max = 0.0f;
	int index = -1;
	for (int i = 0; i < 4; i++) {
		float product = glm::dot(glm::normalize(target), compass[i]);
		if (product > max) {
			max = product;
			index = i;
		}
	}
	return (DIRECTION)index;
}