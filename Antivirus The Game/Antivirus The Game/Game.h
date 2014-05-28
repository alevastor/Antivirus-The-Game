#pragma once
#include "Player.h"
#include "Enemy.h"
#include "DeathCircle.h"
#include "GameObjectManager.h"
#include "Bonus.h"

class Game
{
public:
	static void start();
	static void restart();

	static sf::RenderWindow& getWindow();
	const static GameObjectManager& Game::getGameObjectManager();

	const static sf::InputStream& getInput();
	const static int SCREEN_WIDTH = 824;
	const static int SCREEN_HEIGHT = 624;
	const static int BORDER_LEFT = 4;
	const static int BORDER_RIGHT = SCREEN_WIDTH - 204;
	const static int BORDER_TOP = 4;
	const static int BORDER_BOTTOM = SCREEN_HEIGHT - 4;

	static float difficult;
	static int bestScore;
	static int currentScore;
	static void setGameState(string);
	static void addEnemy();
	static void subEnemy();
	static int getEnemiesCount();
	static void checkForBonus(int, int);

private:
	static bool isExiting();
	static void gameLoop();

	static void showSplashScreen();
	static void showMenu();
	static void showGameOver();

	enum GameState { Uninitialized, ShowingSplash, GameEnd, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;

	static sf::Sprite _sprite;
	static sf::Texture _texture;
	static int _enemiesCount;
};