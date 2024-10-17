#include "BgScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>
#include "Scene.h"
#include "Game.h"


BgScene::BgScene()
{
	map = NULL;
	bgQuad = NULL;

}

BgScene::~BgScene()
{
	if (map != NULL)
		delete map;
	if (bgQuad != NULL)
		delete bgQuad;

}

void BgScene::init()
{
	initShaders();
	//map = TileMap::createTileMap("levels/levelMatrix.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	bgTexture.loadFromFile("images/portada.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bgQuad = Sprite::createSprite(glm::vec2(map->getMapSize() * map->getTileSize()), glm::vec2(1.f, 1.f), &bgTexture, &texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);

}

void BgScene::update(int deltaTime)
{
}


void BgScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection); // Projection is now affected by camera
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	//level
	bgTexture.use();
	bgQuad->render();
	//map->render();
}