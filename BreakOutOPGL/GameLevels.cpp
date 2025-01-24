#include "GameLevels.h"

GameLevels::GameLevels(){}

void GameLevels::LoadLevels(const char * path, unsigned int levelWidth, unsigned int levelHeight) {
	this->bricks.clear();
	GameLevels level;
	unsigned int tileCode;
	std::string ligne;
	std::ifstream fStream(path);
	std::vector<std::vector<unsigned int>> tiledata;
	if (fStream) {
		while (std::getline(fStream,ligne)) {
			std::istringstream sStream(ligne);
			std::vector<unsigned int> row;
			while (sStream >> tileCode) {
				row.push_back(tileCode);

			}
			tiledata.push_back(row);
		}
		if(tiledata.size() > 0)
			Init(tiledata, levelWidth, levelHeight);
	}
	else {
		std::cout << "Erreur chargement du level" << std::endl;
	}
	
}

void GameLevels::Init(std::vector<std::vector<unsigned  int>> tiledata, unsigned int levelWidth, unsigned int levelHeight) {

	unsigned int width, height;

	height = tiledata.size();
	width = tiledata[0].size();
	float tileWidth = levelWidth / static_cast<float>(width);
	float tileHeight = levelHeight / height;

	for (unsigned int i = 0; i < tiledata.size(); i++) {
		for (unsigned int j = 0; j < tiledata[0].size(); j++) {
			
			glm::vec2 position = glm::vec2(j * tileWidth, i * tileHeight);
			glm::vec2 size = glm::vec2(tileWidth, tileHeight);
			glm::vec4 color = glm::vec4(1.0f);
			switch (tiledata[i][j]) {
			case 1://valeur pour une brique indestructible
			{//bracket nécessaire due à la création de l'instance GameObject dans un switch
				color = glm::vec4(0.8f, 0.8f, 0.7f, 1.0f);
				GameObject brick = GameObject(Ressource::GetTexture("solidBlock"), position, size, color);
				brick.isSolid = true;
				this->bricks.push_back(brick);
				break;
			}
				
			case 2://valeur pour brique destructible, couleur différente
			{
				color = glm::vec4(0.2f, 0.6f, 1.0f, 1.0f);
				GameObject brick = GameObject(Ressource::GetTexture("block"), position, size, color);
				this->bricks.push_back(brick);
				break;
			}
			
			case 3:
			{
				color = glm::vec4(0.0f, 0.7f, 0.0f, 1.0f);
				GameObject brick = GameObject(Ressource::GetTexture("block"), position, size, color);
				this->bricks.push_back(brick);
				break;
			}
			case 4:
			{
				color = glm::vec4(0.8f, 0.8f, 0.4f, 1.0f);
				GameObject brick = GameObject(Ressource::GetTexture("block"), position, size, color);
				this->bricks.push_back(brick);
				break;
			}
			case 5:
			{
				color = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
				GameObject brick = GameObject(Ressource::GetTexture("block"), position, size, color);
				this->bricks.push_back(brick);
				break;
			}
			}
			
		}
	}
	
}

void GameLevels::DrawLevels(SpriteRenderer & renderer) {
	for (GameObject &obj : this->bricks) {
		if(!obj.isDestroyed)
			obj.draw(renderer);
	}
}