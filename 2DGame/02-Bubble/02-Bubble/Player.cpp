#include "Player.h"
#include "Game.h"

#define FALL_STEP 2
#define WALK_SPEED 2
#define GRAVITY 0.5f
#define JUMP_SPEED -9.f
#define BUTT_JUMP_SPEED -12.f
#define STANDART_SIZE glm::ivec2(24, 32)
#define DODGE_SIZE glm::ivec2(24, 32)

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	jumpAvailable = true;
	objInteractionAvailable = true;
	yAxisSpeed = 0.f;
	oldState = newState = IDLE;

	pickedUpBlock = nullptr;

	sizeSprite = glm::ivec2(32, 48);

	//AÑADIR ANIMACIONES MAS CHULAS
	glm::vec2* vec2Array = new glm::vec2[6];
	
	vec2Array[0] = glm::vec2(0.066f * 2, 0.f);
	vec2Array[1] = glm::vec2(0.066f * 3, 0.f);
	vec2Array[2] = glm::vec2(0.066f * 4, 0.f);
	vec2Array[3] = glm::vec2(0.066f * 5, 0.f);
	vec2Array[4] = glm::vec2(0.066f * 6, 0.f);
	vec2Array[5] = glm::vec2(0.066f * 7, 0.f);

	particleEfect.init(tileMapPos, position, sizeSprite, shaderProgram, "images/Mickey_Mouse.png", glm::vec2(0.066, 0.098), 1);
	particleEfect.addAnimation(8, vec2Array, 6);

	delete vec2Array;
	//HASTA AQUI

	setSize(glm::ivec2(24, 32));
	setOffset(glm::ivec2(4, 8));

	spritesheet.loadFromFile("images/Mickey_Mouse.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(sizeSprite, glm::vec2(0.066, 0.098), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(TOTAL);

	sprite->setAnimationSpeed(IDLE, 4);
	sprite->addKeyframe(IDLE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(IDLE, glm::vec2(0.066f, 0.f));

	sprite->setAnimationSpeed(WALK, 8);
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 2, 0.f));
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 3, 0.f));
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 4, 0.f));
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 5, 0.f));
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 6, 0.f));
	sprite->addKeyframe(WALK, glm::vec2(0.066f * 7, 0.f));

	sprite->setAnimationSpeed(DODGE, 8);
	sprite->addKeyframe(DODGE, glm::vec2(0, 0.098 * 1));
	sprite->addKeyframe(DODGE, glm::vec2(0.066f * 1, 0.098 * 1));

	sprite->setAnimationSpeed(JUMP, 8);
	sprite->addKeyframe(JUMP, glm::vec2(0.066f * 2, 0.098 * 1));

	sprite->setAnimationSpeed(FALL, 8);
	sprite->addKeyframe(FALL, glm::vec2(0.066f * 3, 0.098 * 1));

	sprite->setAnimationSpeed(READY_TO_PICK, 8);
	sprite->addKeyframe(READY_TO_PICK, glm::vec2(0.066f * 0, 0.098 * 3));

	sprite->setAnimationSpeed(BUTT_FALL, 8);
	sprite->addKeyframe(BUTT_FALL, glm::vec2(0.066f * 5, 0.098 * 1));

	sprite->setAnimationSpeed(BUTT_JUMP, 8);
	sprite->addKeyframe(BUTT_JUMP, glm::vec2(0.066f * 6, 0.098 * 1));

	sprite->setAnimationSpeed(CLIMB_IDLE, 8);
	sprite->addKeyframe(CLIMB_IDLE, glm::vec2(0.066f * 11, 0.098 * 0));

	sprite->setAnimationSpeed(CLIMB, 8);
	sprite->addKeyframe(CLIMB, glm::vec2(0.066f * 12, 0.098 * 0));
	sprite->addKeyframe(CLIMB, glm::vec2(0.066f * 13, 0.098 * 0));

	sprite->setAnimationSpeed(B_PICK, 6);
	sprite->addKeyframe(B_PICK, glm::vec2(0.066f * 3, 0.098 * 3));
	sprite->addKeyframe(B_PICK, glm::vec2(0.066f * 2, 0.098 * 3));
	sprite->addKeyframe(B_PICK, glm::vec2(0.066f * 4, 0.098 * 3));

	sprite->setAnimationSpeed(B_IDLE, 8);
	sprite->addKeyframe(B_IDLE, glm::vec2(0.066f * 4, 0.098 * 3));
	sprite->addKeyframe(B_IDLE, glm::vec2(0.066f * 4, 0.098 * 3));
	sprite->addKeyframe(B_IDLE, glm::vec2(0.066f * 5, 0.098 * 3));

	sprite->setAnimationSpeed(B_WALK, 8);
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 0, 0.098 * 4));
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 1, 0.098 * 4));
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 2, 0.098 * 4));
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 3, 0.098 * 4));
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 4, 0.098 * 4));
	sprite->addKeyframe(B_WALK, glm::vec2(0.066f * 5, 0.098 * 4));

	sprite->setAnimationSpeed(B_JUMP, 8);
	sprite->addKeyframe(B_JUMP, glm::vec2(0.066f * 9, 0.098 * 4));

	sprite->setAnimationSpeed(B_FALL, 8);
	sprite->addKeyframe(B_FALL, glm::vec2(0.066f * 10, 0.098 * 4));

	sprite->changeAnimation(IDLE);
	tileMapDispl = tileMapPos;
	//setPosition(glm::ivec2(0, 0));
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	yAxisSpeed += GRAVITY;
	position.y += int(yAxisSpeed) + 1;

	colType = CollisionType::None;
	block = nullptr;

	switch (oldState)
	{
		case IDLE:
		{
			movementBehaviour();
			break;
		}
		case WALK:
		{
			newState = IDLE;
			movementBehaviour();
			break;
		}
		case JUMP:
		{
			if (Game::instance().getKey(GLFW_KEY_A)) {
				leftMove();
			}
			if (Game::instance().getKey(GLFW_KEY_D)) {
				rightMove();
			}
			if (Game::instance().getKey(GLFW_KEY_S)) {
				newState = BUTT_FALL;
			}
			if ((stopFallingCollision(block, colType) && yAxisSpeed < 0) || yAxisSpeed > 0)
			{
				yAxisSpeed = 0;
				newState = FALL;
			}
			if (colType == CollisionType::Stairs && Game::instance().getKey(GLFW_KEY_W))
			{
				changeToClimb();
			}
			break;
		}
		case FALL:
		{
			if (Game::instance().getKey(GLFW_KEY_A)) {
				leftMove();
			}
			if (Game::instance().getKey(GLFW_KEY_D)) {
				rightMove();
			}
			if (Game::instance().getKey(GLFW_KEY_S)) {
				newState = BUTT_FALL;
			}
			if (stopFallingCollision(block, colType))
			{
				yAxisSpeed = 0;
				newState = IDLE;
			}
			if (colType == CollisionType::Stairs && Game::instance().getKey(GLFW_KEY_W))
			{
				changeToClimb();
			}
			break;
		}
		case DODGE:
		{
			if (!Game::instance().getKey(GLFW_KEY_S)) {
				setSize(STANDART_SIZE);
				newState = IDLE;
			}
			if (stopFallingCollision(block, colType))
			{
				yAxisSpeed = 0;
			}

			if (checkJumpButton()) {
				newState = JUMP;
				yAxisSpeed = JUMP_SPEED;
			}
			break;
		}
		case BUTT_FALL:
		{
			buttJumpBehaviour();
			break;
		}
		case BUTT_JUMP:
		{
			buttJumpBehaviour();
			break;
		}
		case READY_TO_PICK:
		{
			newState = READY_TO_PICK;
			movementBehaviour();
			if (checkObjInteractionButton()) {
				pickUpBlock();
			}
			break;
		}
		case CLIMB_IDLE:
		{
			climbBehaviour();
			break;
		}
		case CLIMB:
		{
			newState = CLIMB_IDLE;
			climbBehaviour();
			break;
		}
		case B_PICK:
		{
			position.y -= int(yAxisSpeed) + 1;
			auto keyframe = sprite->getCurrentKeyframe();
			if (keyframe.x == keyframe.y-1)
				newState = B_IDLE;
			break;
		}
		case B_IDLE:
		{
			blockMovementBehaviour();
			break;
		}
		case B_WALK:
		{
			newState = B_IDLE;
			blockMovementBehaviour();
			break;
		}
		case B_JUMP:
		{
			if (Game::instance().getKey(GLFW_KEY_A)) {
				leftMove();
			}
			if (Game::instance().getKey(GLFW_KEY_D)) {
				rightMove();
			}
			if (checkObjInteractionButton()) {
				throwBlock();
			}
			if ((stopFallingCollision(block, colType) && yAxisSpeed < 0) || yAxisSpeed > 0)
			{
				yAxisSpeed = 0;
				newState = B_FALL;
			}
			break;
		}
		case B_FALL:
		{
			if (Game::instance().getKey(GLFW_KEY_A)) {
				leftMove();
			}
			if (Game::instance().getKey(GLFW_KEY_D)) {
				rightMove();
			}
			if (checkObjInteractionButton()) {
				//newState = BUTT_FALL;
				throwBlock();
			}
			if (stopFallingCollision(block, colType))
			{
				yAxisSpeed = 0;
				newState = B_IDLE;
			}
			break;
		}
	}

	if (oldState != newState) {
		oldState = newState;
		sprite->changeAnimation(newState);
	}

	setPosition(position);
	if (Game::instance().getKey(GLFW_KEY_P))
		cout << position.x << " " << position.y << " - State: " << PlayerStates(oldState) << endl;
	// TENEMOS QUE AÑADIR PARTICULAS CHULAS
	
	particleEfect.update(deltaTime);
	if (pickedUpBlock != nullptr)
	{
		pickedUpBlock->update(deltaTime);//hacemos el update (hay que cambiarle la posicion)
		if (left)
		{
			pickedUpBlock->setPosition(glm::ivec2(position.x, position.y + 10 - pickedUpBlock->getSize().y));
		}
		else
		{
			pickedUpBlock->setPosition(glm::ivec2(position.x + this->getSize().x - pickedUpBlock->getSize().x, position.y + 10 - pickedUpBlock->getSize().y));
		}
	}
}

void Player::render()
{
	if (pickedUpBlock != nullptr)
		pickedUpBlock->render();
	sprite->render();
	particleEfect.render();
}

void Player::pickUpBlock()
{
	newState = B_PICK;
	pickedUpBlock = readyToPickBlock;
	readyToPickBlock = nullptr;
	pickedUpBlock->grabbed();
	//collider desconectar block
	CollisionManager::instance().disAttachBlock(pickedUpBlock);
	pickedUpBlock->setPosition(glm::ivec2(position.x, position.y - 30));
}

void Player::throwBlock()
{
	//collider atach block
	glm::vec2 dir = glm::vec2(0, 0);
	if (left)
		dir.x *= -1;
	pickedUpBlock->throwBlock(dir);
	CollisionManager::instance().attachBlock(pickedUpBlock);
	pickedUpBlock = nullptr;

	switch (oldState)
	{
	case B_IDLE:
		newState = IDLE;
		break;
	case B_WALK:
		newState = WALK;
		break;
	case B_JUMP:
		newState = JUMP;
		break;
	case B_FALL:
		newState = FALL;
		break;
	}
}

bool Player::checkJumpButton()
{
	if ((Game::instance().getKey(GLFW_KEY_K) || Game::instance().getKey(GLFW_KEY_W)) && jumpAvailable)
	{
		jumpAvailable = false;
		return true;
	}
	if (!Game::instance().getKey(GLFW_KEY_K) && !Game::instance().getKey(GLFW_KEY_W))
		jumpAvailable = true;
	return false;
}

bool Player::checkObjInteractionButton()
{
	if (Game::instance().getKey(GLFW_KEY_L)) {
		if (objInteractionAvailable)
		{
			objInteractionAvailable = false;
			return true;
		}
	}
	else
		objInteractionAvailable = true;
	return false;
}

void Player::leftMove()
{
	left = true;
	sprite->setLeft(left);

	position.x -= WALK_SPEED;

	CollisionType colType = CollisionManager::instance().checkCollisionHorizontal(this);
	if (colType == CollisionType::Tile)
		position.x += WALK_SPEED;
	else if ((colType == CollisionType::Stairs || colType == CollisionType::TileStairs) && Game::instance().getKey(GLFW_KEY_W))
		changeToClimb();
	
	Block* b = CollisionManager::instance().collisionEntityBlockH(this);
	if (b != nullptr)
	{
		position.x += WALK_SPEED;
		if (oldState == WALK || oldState == READY_TO_PICK)
		{
			newState = READY_TO_PICK;
			readyToPickBlock = b;
		}
	}
}

void Player::rightMove()
{
	left = false;
	sprite->setLeft(left);
	position.x += WALK_SPEED;

	CollisionType colType = CollisionManager::instance().checkCollisionHorizontal(this);
	if (colType == CollisionType::Tile)
		position.x -= WALK_SPEED;
	else if ((colType == CollisionType::Stairs || colType == CollisionType::TileStairs) && Game::instance().getKey(GLFW_KEY_W))
		changeToClimb();

	Block* b = CollisionManager::instance().collisionEntityBlockH(this);
	if (b != nullptr)
	{
		position.x -= WALK_SPEED;
		if (oldState == WALK || oldState == READY_TO_PICK)
		{
			newState = READY_TO_PICK;
			readyToPickBlock = b;
		}
			
	}
}

void Player::changeToClimb()
{
	newState = CLIMB_IDLE;
	//calcular posicion de la escalera
}

bool Player::stopFallingCollision(Block*& block, CollisionType& colType)
{
	auto originalPos = position;
	colType = CollisionManager::instance().checkCollisionVertical(this);
	
	auto tileCorrectedPos = position;
	block = CollisionManager::instance().collisionEntityBlockV(this);

	if (originalPos != tileCorrectedPos && tileCorrectedPos != position)
		position = tileCorrectedPos;

	if (colType == CollisionType::Tile || colType == CollisionType::TileStairs)
		return true;
	if (block != nullptr) 
		return true;
	return false;
}

bool Player::stairCollision()
{
	auto oldPos = position;
	auto colType = CollisionManager::instance().checkCollisionVertical(this);
	position = oldPos;
	if (colType == CollisionType::Stairs || colType == CollisionType::TileStairs)
		return true;
	return false;
}

void Player::movementBehaviour()
{
	if (stopFallingCollision(block, colType))
	{
		yAxisSpeed = 0;
		if (checkJumpButton()) {
			newState = JUMP;
			yAxisSpeed = JUMP_SPEED;
			return;
		}
		else if (Game::instance().getKey(GLFW_KEY_S)) {
			if (colType == CollisionType::TileStairs) {
				changeToClimb();
				//position.y++;
				return;
			}
			else {
				newState = DODGE;
				return;
			}
				
			// change size, piensatelo: ???
		}
	}
	else
	{
		newState = FALL;
		return;
	}
	if (Game::instance().getKey(GLFW_KEY_A)) {
		newState = WALK;
		leftMove();
	}
	if (Game::instance().getKey(GLFW_KEY_D)) {
		newState = WALK;
		rightMove();
	}
}

void Player::climbBehaviour()
{
	position.y -= int(yAxisSpeed);
	yAxisSpeed = 0;

	if (!stairCollision())
	{
		newState = FALL;
	}
	else 
	{
		position.y--;
		if (Game::instance().getKey(GLFW_KEY_W)) {
			position.y -= WALK_SPEED;
			newState = CLIMB;
		}
		if (Game::instance().getKey(GLFW_KEY_S)) {
			position.y += WALK_SPEED;
			newState = CLIMB;
		}
		if (checkObjInteractionButton() && colType == CollisionType::Stairs) {
			newState = FALL;
		}
	}
}

void Player::buttJumpBehaviour()
{
	if (Game::instance().getKey(GLFW_KEY_A)) {
		leftMove();
	}
	if (Game::instance().getKey(GLFW_KEY_D)) {
		rightMove();
	}
	if (stopFallingCollision(block, colType))
	{
		if (yAxisSpeed > 0)
			newState = IDLE;
		yAxisSpeed = 0;
	}
	if (block != nullptr)
	{
		yAxisSpeed = BUTT_JUMP_SPEED;
		newState = BUTT_JUMP;
		// destruccion del objeto que devuelve
		// delete b;
	}
}

void Player::blockMovementBehaviour()
{
	if (stopFallingCollision(block, colType))
	{
		yAxisSpeed = 0;
		if (checkJumpButton()) {
			newState = B_JUMP;
			yAxisSpeed = JUMP_SPEED;
			return;
		}
	}
	else
	{
		newState = B_FALL;
		return;
	}
	if (Game::instance().getKey(GLFW_KEY_A)) {
		newState = B_WALK;
		leftMove();
	}
	if (Game::instance().getKey(GLFW_KEY_D)) {
		newState = B_WALK;
		rightMove();
	}
	if (checkObjInteractionButton()) {
		throwBlock();
	}
}
