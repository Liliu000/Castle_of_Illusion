#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Entity.h"
#include <cmath>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

enum PlayerStates
{
	IDLE, WALK, JUMP, FALL, DODGE, BUTT_FALL, BUTT_JUMP, READY_TO_PICK, CLIMB_IDLE, CLIMB, TOTAL //Importante que TOTAL este al final
};

class Player : public Entity
{

public:
	static Player& instance()
	{
		static Player P;

		return P;
	}
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

private:
	bool bClimbing, bTouchBlock, bJumping;
	float velocity;

	PlayerStates oldState, newState;

	void leftMove();
	void rightMove();
	void jump(int v);
	void setSize(glm::ivec2 newSize);
};


#endif // _PLAYER_INCLUDE


