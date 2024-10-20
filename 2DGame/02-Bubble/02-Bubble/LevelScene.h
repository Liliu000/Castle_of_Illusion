#pragma once

#ifndef _LEVEL_SCENE_INCLUDE
#define _LEVEL_SCENE_INCLUDE

#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include <vector>
#include "GameUI.h"

class LevelScene : public Scene
{
public:
	LevelScene();
	~LevelScene();
	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	void initShaders();
	void updateCamera();
	void initZoneEnemyTree();
	void initZoneEnemyBug();

	vector<Enemy*> enemiesObj;
	vector<Block*> blocksObj;


	TileMap* map;
	Player* player;

	float currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;
	float zoomLevel;
	glm::vec2 cameraPosition;
	Cam cam;


	//background
	Sprite* bgQuad;
	Texture bgTexture;
	TileMap* bgMap;


	 GameUI gameUI;
};

#endif // _LEVEL_SCENE_INCLUDE



