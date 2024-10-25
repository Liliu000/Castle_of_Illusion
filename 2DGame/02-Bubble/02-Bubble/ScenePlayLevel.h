#pragma once

#include "ScenePlay.h"
#include "BossDragon.h"

class ScenePlayLevel : public ScenePlay
{
public:
	ScenePlayLevel();
	~ScenePlayLevel();
	void init() override;   // Initialize NormalPlayScene-specific elements

protected:
	// Override these methods to handle boss logic and room detection for NormalPlayScene
	void reStartLevelSpecific() override {}

	void updateCollisionsWithBoss(int deltaTime) override;
	bool checkIfInsideBossRoom() override;
	void collisionMovBlockInsideBossRoom(Block* movBlock) override {}

	void renderBoss() override;
	void initZoneEnemyTree();
	void initZoneEnemyBug();
	BossDragon boss;
	Cam bossRoom;
	vector<BossShoot*> shoots;
};
