#pragma once

#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include <vector>
#include "GameUI.h"
#include <map>

#define SCREEN_X 32
#define SCREEN_Y 16

class PlayScene : public Scene
{
public:
    PlayScene();
    virtual ~PlayScene();

    virtual void init() override;   // Initialize the scene
    virtual void update(int deltaTime) override; // Common update logic
    virtual void render() override; // Common rendering logic

protected:
    void initShaders();
    void updateCamera();

    void insideScreenObj();
    bool insideScreen(const glm::ivec2& pos);

    virtual void updateCollisionsWithBoss(int deltaTime) = 0;
    virtual void renderBoss() = 0;
    virtual bool checkIfInsideBossRoom() = 0;
    vector<Enemy*> playrunEnemies;
    vector<Block*> playrunBlocks;

    vector<Enemy*> allEnemies;
    vector<Block*> allBlocks;

    std::map<std::string, Enemy*> screenEnemies;
    std::map<std::string, Block*> screenBlocks;
    std::map<std::string, Block*> playrunMovBlocks;

    TileMap* map;
    Player* player;

    float currentTime;
    glm::mat4 projection;
    ShaderProgram texProgram;
    float zoomLevel;
    glm::vec2 cameraPosition;
    Cam cam;

    // Background
    Sprite* bgQuad;
    Texture bgTexture;
    TileMap* bgMap;

    GameUI gameUI;
    bool insideBossRoom = false;
   
};
