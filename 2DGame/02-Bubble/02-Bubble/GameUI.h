#pragma once

#include "Scene.h"
#include "Quad.h"
#include "Sprite.h"
#include "TexturedQuad.h"
#include "Text.h"

class GameUI : public Scene
{
public:
	GameUI();
	~GameUI();
	void init() override;
	void update(int deltaTime) override;
	void render() override;
	void setStars(int newStars) { stars = newStars; }
	void setPoints(int newPoints) { points = newPoints; }
	void setTries(int newTries) { tries = newTries; }

private:
	void initShaders();
	Quad* quad;

	int stars = 5; int starSize = 40; int time = 400;
	int tries = 3;
	int points = 153;
	Texture starTexture;
	TexturedQuad* star;

	Texture bgTexture;
	TexturedQuad* bg;
	ShaderProgram simpleProgram, texProgram;
	float currentTime;
	glm::mat4 projection;
	int textSize = 25;
	Text text;
};

