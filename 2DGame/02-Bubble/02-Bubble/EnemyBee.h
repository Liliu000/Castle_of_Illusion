#pragma once
#include "Enemy.h"

enum EnemyBeeStates
{
	BEE_FLY_RIGHT, BEE_DIE
}; 

class EnemyBee : public Enemy
{
public:
	EnemyBee() { }
	~EnemyBee() override {}
	void update(int deltaTime) override;
	void initMov(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const ZoneEnemy& initParams) override;
	void render() override;
	void Damaged() override;
	void collideVertical() override;
	void collideHorizontal() override {}
	void collisionBlockHorizontal(Block* b) override;

private:

	int attackDistance = 2 * 16;//5*mapTileSize
	int attackSpeed;
	int elapsedTime = 0;
	int timeDyingAnim = 500; //0,5 s
	int moveY = 1;
	int countY = 2;
	EnemyBeeStates enemyBeeState = EnemyBeeStates::BEE_FLY_RIGHT;
};

