#include "main.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameOver.h"
#include<sstream>
#include "shlobj.h"

sf::Clock _enemyClock;
sf::Clock _difficultClock;

void Game::start()
{
	if(_gameState != Uninitialized)
		return;

	srand(time(0));
	createWindow(_mainWindow,fmode);
	if(!defaultFont.loadFromFile("megatron.ttf"))
	{
		// error with titleFont
	}

	ifstream in("antivirus.game",ios::binary|ios::in);
	in.read((char*)&bestScore,sizeof bestScore);
	in.close();

	difficult = 1;

	_texture.loadFromFile("images/game_bg1.png");
	_sprite.setTexture(_texture);

	_gameState= Game::ShowingSplash;
	while(!isExiting())
	{
		gameLoop();
	}
	_mainWindow.close();
}

void Game::restart()
{
	if(_gameState != Uninitialized)
		return;

	std::map<std::string, VisibleGameObject*>::const_iterator itr;
	for(itr = _gameObjectManager._gameObjects.begin(); itr != _gameObjectManager._gameObjects.end(); itr++)
	{
		if(itr != _gameObjectManager._gameObjects.end())
		{
			itr->second->setExisted(false);
		}
	}
	_gameObjectManager.removeNotExisted();

	Player *player = new Player();

	_gameObjectManager.add("Player",player);
	DeathCircle *deathCircle = new DeathCircle();
	_gameObjectManager.add("DeathCircle",deathCircle);
	difficult = 1;
	_enemiesCount = 0;

	_gameState= Game::Playing;
	while(!isExiting())
	{
		gameLoop();
	}

	_mainWindow.close();
}

bool Game::isExiting()
{
	if(_gameState == Game::Exiting)
	{
		std::map<std::string, VisibleGameObject*>::const_iterator itr;
		for(itr = _gameObjectManager._gameObjects.begin(); itr != _gameObjectManager._gameObjects.end(); itr++)
		{
			if(itr != _gameObjectManager._gameObjects.end())
			{
				itr->second->setExisted(false);
			}
		}
		_gameObjectManager.removeNotExisted();
		return true;
	}
	else 
		return false;
}

sf::RenderWindow& Game::getWindow()
{
	return _mainWindow;
}

const GameObjectManager& Game::getGameObjectManager()
{
	return Game::_gameObjectManager;
}

void Game::gameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch(_gameState)
	{
	case Game::ShowingMenu:
		{
			showMenu();
			break;
		}
	case Game::ShowingSplash:
		{
			showSplashScreen();
			break;
		}
	case Game::Playing:
		{
			_mainWindow.clear(sf::Color(0,0,0));
			_mainWindow.draw(_sprite);
			if(_difficultClock.getElapsedTime().asSeconds() > 2) _difficultClock.restart();
			if(_difficultClock.getElapsedTime().asSeconds() > 1)
			{
				difficult+=0.1;
				_difficultClock.restart();
			}

			if(_enemyClock.getElapsedTime().asSeconds() > 2) _enemyClock.restart();
			if(_enemyClock.getElapsedTime().asSeconds() > (1. - Game::difficult/100))
			{
				Enemy *enemy = new Enemy();
				ostringstream iss;
				iss << enemy;
//				_gameObjectManager.add("Enemy1" + to_string(rand()%50000+1),enemy); // TODO: fix it
				_gameObjectManager.add("Enemy1" + iss.str(),enemy); // TODO: fix it
				_enemyClock.restart();
			}
			_gameObjectManager.updateAll();
			_gameObjectManager.removeNotExisted();
			_gameObjectManager.drawAll(_mainWindow);
			_mainWindow.display();
		
			if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
			if(currentEvent.type == sf::Event::KeyPressed)
			{
				if(currentEvent.key.code == sf::Keyboard::Escape) _gameState = Game::ShowingMenu;
				/*if(currentEvent.key.alt && currentEvent.key.code == sf::Keyboard::Return)
				{
					if(fmode)										
						fmode = false;
					else
						fmode = true;
					createWindow(_mainWindow, fmode);
				}*/
			}
			break;
		}
	case Game::GameEnd:
		{
			if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
			if(currentEvent.type == sf::Event::KeyPressed)
			{
				if(currentEvent.key.code == sf::Keyboard::Escape) _gameState = Game::ShowingMenu;
			}

			ofstream out("antivirus.game",ios::binary|ios::out);
			out.write((char*)&bestScore,sizeof bestScore);
			out.close();

			showGameOver();
			return;
			break;
		}
		break;
	}
}

void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	if(_gameState != Game::Exiting)
		_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Uninitialized;
		sf::Mouse mouse;
		mouse.setPosition(sf::Vector2i(((Game::BORDER_RIGHT-Game::BORDER_LEFT)/2),((Game::BORDER_BOTTOM-Game::BORDER_TOP)/2)),_mainWindow);
		Game::restart();
		break;
	}
}

void Game::showGameOver()
{
	GameOver gameOver;
	GameOver::GameOverResult result = gameOver.show(_mainWindow);
	switch(result)
	{
	case GameOver::Exit:
		_gameState = Game::Exiting;
		break;
	case GameOver::Restart:
		_gameState = Game::Uninitialized;
		sf::Mouse mouse;
		mouse.setPosition(sf::Vector2i(((Game::BORDER_RIGHT-Game::BORDER_LEFT)/2),((Game::BORDER_BOTTOM-Game::BORDER_TOP)/2)),_mainWindow);
		Game::restart();
		break;
	case GameOver::Submit:
		//do nothing
		break;
	}
}

void Game::addEnemy()
{
	_enemiesCount++;
}

void Game::subEnemy()
{
	_enemiesCount--;
}

int Game::getEnemiesCount()
{
	return _enemiesCount;
}

void Game::setGameState(string s)
{
	if(s=="GameOver")
		_gameState = Game::GameEnd;
	if(s=="Playing")
		_gameState = Game::Playing;
	if(s=="Exiting")
		_gameState = Game::Exiting;
	if(s=="ShowingMenu")
		_gameState = Game::ShowingMenu;
}

void Game::checkForBonus(int x, int y)
{
	if(_gameState == Game::Playing)
	{
		int bonusChance = rand()%100+1;
		if(bonusChance <= 20)
		{
			Bonus *bonus = new Bonus(x, y);
			_gameObjectManager.add("Bonus"+to_string(rand()%50000+1),bonus);
		}
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
float Game::difficult;
int Game::bestScore;
sf::Sprite Game::_sprite;
sf::Texture Game::_texture;
int Game::_enemiesCount;
int Game::currentScore;