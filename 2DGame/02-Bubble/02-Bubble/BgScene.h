#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "Sprite.h"

class BgScene :
    public Scene
{
public:
	BgScene();
	~BgScene();
	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	void initShaders();
	TileMap* map;
	ShaderProgram texProgram;
	glm::mat4 projection;

	Sprite* bgQuad;
	Texture bgTexture;
};

