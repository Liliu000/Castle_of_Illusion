#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Scene.h"
#include "SceneMenu.h"
#include "ScenePlayLevel.h"
#include "ScenePlayPractice.h"
#include "SceneInstructions.h"
#include "SceneCredits.h"
#include "SceneFinalScreen.h"

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application

enum GameState {
	MENU,
	INSTRUCTIONS,
	CREDITS,
	PLAY_LEVEL,
	PLAY_PRACTICE
};
class Game
{

private:
	Game() {}

public:
	static Game& instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;


	int getStars() { return stars; }
	int getScore() { return score; }
	int getTries() { return tries; }
	//void addStar() { stars += 1; }
	//void substractStar() { stars -= 1; }
	void onPlayerKilledEnemy();
	void onPlayerFallDownHole();
	void onPlayerKilled();
	void onPracticeLevelWon();
	void onLevelWon();
	void onGetCake();
	void onGetCoin();
	void onExceededTimeLimit();
	void onHeal();
	bool isOnGodMode() { return godMode; }
	void setScene(GameState gs);
	void exitGame() { bPlay = false; }

private:
	void looseGame();

	bool bPlay; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time
	Scene* currentScene;
	GameState currentState;
	SceneMenu sceneMenu;
	ScenePlayLevel scenePlayLevel;
	ScenePlayPractice scenePlayPractice;
	SceneInstructions sceneInstructions;
	SceneCredits sceneCredits;
	SceneFinalScreen sceneFinalScreen;

	int score = 0;
	int tries = 3;
	int stars = 3;
	bool godMode = false;
};


#endif // _GAME_INCLUDE


