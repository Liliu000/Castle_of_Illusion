#pragma once
#include <vector>


using namespace std;

#define MAX_STARS 5
#define INIT_STARS 3
#define ENEMY_POINTS 50
#define COIN_POINTS 100

struct Zone
{
	float min_x;
	float max_x;
	float min_y;
	float max_y;
};
enum EnemyType
{
	Tree,
	Bug,
};

enum EntityState
{
	Alive,
	Dead,
	Dying
};

enum BlockType
{
	Destroyable,
	NonDestroyable,
	Chest,
	Coin,
	Cake
};
enum CollisionType
{
	None,
	Tile,
	Stairs,
	TileStairs
};

enum VColType
{
	NoVcol,
	Down,
	Up,
};

enum HColType
{
	NoHcol,
	Left,
	Right,
};
struct BlockObj
{
	int type;
	glm::ivec2 pos;
};

struct ZoneEnemy
{
	Zone limit;
	glm::ivec2 initPos;
	bool left;
};

struct Cam {
	float left, right, bottom, top;
};

struct InitEnemy
{
	EnemyType enemyType;
	Zone limit;
	glm::ivec2 initPos;
	bool left;
};

struct PosSizeObject
{
	glm::ivec2 posObject;
	glm::ivec2 sizeObject;
};
