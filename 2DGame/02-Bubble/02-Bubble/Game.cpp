#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "SoundManager.h"

void Game::init()
{
	bPlay = true;
	currentState = MENU;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	SoundManager::instance().init();
	sceneMenu.init();
	sceneInstructions.init();
	sceneCredits.init();
	sceneFinalScreen.init();
	sceneFinalScreen.setWon(false);
	scenePlayPractice.init();
	scenePlayLevel.init();
	currentScene = &sceneMenu;
	SoundManager::instance().setMusicVolume(30);
	SoundManager::instance().playMusic("menu", -1);
}

bool Game::update(int deltaTime)
{
	currentScene->update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentScene->render();
}

void Game::keyPressed(int key)
{
	SoundManager::instance().setMusicVolume(30);
	if (key == GLFW_KEY_ESCAPE) // Escape code
	{
		if (currentScene != &sceneMenu) 
			setScene(MENU);
		else
			bPlay = false;
	}
	else if (godMode && currentScene == &scenePlayPractice && key == GLFW_KEY_0) {
		currentScene = &scenePlayLevel;
		tries = 8;
		scenePlayLevel.reStart();
		SoundManager::instance().playMusic("level", -1);
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	if (keys[GLFW_KEY_G])
	{
		godMode = !godMode;
	}
	if (keys[GLFW_KEY_H]) {
		onHeal();
	}
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

void Game::onPlayerFallDownHole() {
	stars = INIT_STARS;
	tries -= 1;
	if (tries <= 0) {
		looseGame();
	}
	else {
		ScenePlay* playScene = dynamic_cast<ScenePlay*>(currentScene);
		if (playScene) {
			playScene->reStart();
		}
		SoundManager::instance().setMusicVolume(40);
		SoundManager::instance().playSoundEffect("playRestart", 0);
	}
}

void Game::onPlayerKilled() 
{
	if (godMode) return;
	SoundManager::instance().setMusicVolume(40);
	if (stars > 0)
	{
		stars -= 1;
	}
	if (stars <= 0)
	{
		stars = INIT_STARS;
		tries -= 1;
		//restart level
		ScenePlay* playScene = dynamic_cast<ScenePlay*>(currentScene);
		if (playScene) {
			playScene->reStart();
		}
		SoundManager::instance().playSoundEffect("playRestart", 0);
	}
	else {
		SoundManager::instance().playSoundEffect("playerDamage", 0);
	}
	if (tries <= 0)
	{
		looseGame();
	}
}

void Game::onExceededTimeLimit()
{
	looseGame();
}

void Game::onPracticeLevelWon()
{
	stars = INIT_STARS;
	tries = 8;
	currentScene = &scenePlayLevel;
	scenePlayLevel.reStart();
	SoundManager::instance().setMusicVolume(30);
	SoundManager::instance().playMusic("level", -1);
}

void Game::onLevelWon()
{
	sceneFinalScreen.setWon(true);
	currentScene = &sceneFinalScreen;
	SoundManager::instance().setMusicVolume(30);
	SoundManager::instance().playMusic("gameOver", -1);
}

void Game::looseGame()
{
	sceneFinalScreen.setWon(false);
	currentScene = &sceneFinalScreen;
	SoundManager::instance().setMusicVolume(40);
	SoundManager::instance().playSoundEffect("gameLose", 0);
	SoundManager::instance().setMusicVolume(30);
	SoundManager::instance().playMusic("gameOver", -1);
}

void Game::onPlayerKilledEnemy()
{
	score += ENEMY_POINTS;
	SoundManager::instance().setMusicVolume(40);
	SoundManager::instance().playSoundEffect("playerCoin", 0);
}
void Game::onGetCoin() {
	score += COIN_POINTS;
	SoundManager::instance().setMusicVolume(40);
	SoundManager::instance().playSoundEffect("playerCoin", 0);
}

void Game::onGetCake() { 
	if (stars < MAX_STARS) stars += 1; 
	SoundManager::instance().setMusicVolume(40);
	SoundManager::instance().playSoundEffect("playerCake", 0);
}

void Game::onHeal() { 
	stars = INIT_STARS; 
	SoundManager::instance().setMusicVolume(40);
	SoundManager::instance().playSoundEffect("playerCake", 0);
}

void Game::setScene(GameState gs)
{
	switch (gs)
	{
	case MENU:
		sceneFinalScreen.setWon(false);
		currentScene = &sceneMenu;
		SoundManager::instance().playMusic("menu", -1);
		break;
	case INSTRUCTIONS:
		currentScene = &sceneInstructions;
		break;
	case CREDITS:
		currentScene = &sceneCredits;
		break;
	case PLAY_LEVEL:
		currentScene = &scenePlayLevel;
		break;
	case PLAY_PRACTICE:
		currentScene = &scenePlayPractice;
		tries = 3;
		scenePlayPractice.reStart();
		SoundManager::instance().playMusic("level", -1);
		break;
	}
}


