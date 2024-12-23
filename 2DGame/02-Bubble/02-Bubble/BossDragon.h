#pragma once

#include "Enemy.h"
#include <vector>
#include "BossShoot.h"

enum BossDragonStates
{
	BOSS_LEFT, BOSS_LEFT_DOWN, BOSS_RIGHT_DOWN, BOSS_DOWN, BOSS_IDLE
};

enum BossBodyStates
{
	BOSS_BODY_IDLE
};

class BossDragon : public Enemy
{
public:
	BossDragon();
	~BossDragon() override;
	void update(int deltaTime) override;
	void initMov(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const ZoneEnemy& initParams) override;
	void render() override;
	void setBossPosition(const glm::vec2& pos) {
		posBody = pos;
		bodySprite->setPosition(glm::vec2(float(tileMapDispl.x + posBody.x - offset.x), float(tileMapDispl.y + posBody.y - offset.y)));
		setHeadSpritePos();
	}

	void Damaged() override;
	void reLive() override {}
	void collideVertical() override {}
	void collideHorizontal() override {}
	void collisionBlockHorizontal(Block* b) override {}

	void resetDragon();
	bool getActive() { return active; }
	void appear() { active = true; entityState = STILL; }

	vector<BossShoot*> getShoots() { return shoots; }

private:
	void setHeadSpritePos();
	void setBodyAnimations(ShaderProgram& shaderProgram);
	void setHeadAnimations(ShaderProgram& shaderProgram);
	void changeHeadState(BossDragonStates objective);
	void shoot(int deltaTime);

	bool active = false;

	//cycle var
	int state = 0;                       // Boss's state

	int timeSinceLastStateChange = 0;    // Time accumulator for state changes during idle
	int timeSinceLastShoot = 0;           // Time accumulator for shoot during move shooting
	int cycleTime = 0;                   // Total time for the current cycle

	const int idleDuration = 200 * 10;          // 160ms idle period
	const int stateChangeInterval = 200;   // 16ms interval for state change during idle
	const int shootInterval = 150;          // 8ms interval for each shoot during shooting phase

	int shootCount = 0;                   // Count the number of shoots made during the shooting phase

	int timeDyingAnim = 500; //0,5 s
	int elapsedTime = 0;

	Texture bodySpritesheet;
	Sprite* bodySprite;

	glm::ivec2 sizeObjBody, sizeObjHead;
	glm::ivec2 posBody, posHead;
	glm::ivec2 positionStartShoot;

	vector<BossShoot*> shoots;
	vector<vector<float>> angleShoots;
	int indexAngleShoot, indexQuadrantShoot = 0;
	int MaxShoots = 3;
	int actualLives = MAX_LIVES_BOSS;
	bool paint = true;


	BossDragonStates bossDragonState = BossDragonStates::BOSS_LEFT;
	BossBodyStates bossBodyState = BossBodyStates::BOSS_BODY_IDLE;
	vector<BossDragonStates> states;
};
