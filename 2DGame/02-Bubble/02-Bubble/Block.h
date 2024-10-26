#pragma once

#include "Entity.h"
#include <cmath>


enum BlockState
{
	STILL, GRABBED, FALLING
};

class Block : public Entity
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	void update(int deltaTime);
	void render();
	BlockType getBlockType() { return blockType; }
	void collisionEnemy(const glm::ivec2& posEnemy);
	void collisionBlockHorizontal(HColType hBlockCollision, const Block*& b);
	void collisionBlockVertical(VColType vBlockCollision, const Block*& b);
	void collisionVertical(CollisionType verticalCollision);
	void collisionHorizontal(CollisionType horizontalCollision);

	void throwBlock(glm::vec2 speed);
	void grabbed();
	void explode();

private:
	BlockState state;// = BlockState::STILL;
	glm::vec2 speed;// = glm::vec2(0, 0);
	
protected:
	BlockType blockType;
};

