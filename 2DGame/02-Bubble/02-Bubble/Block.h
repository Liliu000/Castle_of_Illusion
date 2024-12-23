#pragma once

#include "Entity.h"
#include <cmath>
#include "ParticleEfect.h"
#include "SoundManager.h"


class Block : public Entity
{
public:
	~Block();
	Block(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	//virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	void update(int deltaTime);
	void render();
	BlockType getBlockType() { return blockType; }
	void setOgPosition(const glm::vec2& pos) { ogPosition = pos; }
	glm::ivec2 getOgPosition() { return ogPosition; }
	virtual void collisionEnemy(const glm::ivec2& posEnemy);
	virtual void collisionBlockHorizontal(HColType hBlockCollision, const Block*& b);
	virtual void collisionBlockVertical(VColType vBlockCollision, const Block*& b);
	virtual void collisionVertical(CollisionType verticalCollision);
	virtual void collisionHorizontal(CollisionType horizontalCollision);

	void throwBlock(glm::vec2 speed);

	virtual void explode() = 0;
	void dropBlock(glm::ivec2 pos, glm::ivec2 size, bool left);
	glm::vec2 getSpeed() { return speed; };

protected:
	BlockType blockType;
	glm::ivec2 ogPosition;
	int elapsedTime = 0;
	int timeDyingAnim = 6 * 1000/15;
	glm::vec2 speed = glm::vec2(0, 0);
	ParticleEfect* explosionEfect;
};