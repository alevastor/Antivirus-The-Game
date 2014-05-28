#pragma once
#include <list>
#include "Game.h"

class GameOver
{

public:
	enum GameOverResult { Nothing, Submit, Restart, Exit };	
	
	struct GameOverItem
		{
		public:
			sf::Rect<int> rect;
			GameOverResult action;
			sf::Texture texture;
			sf::Texture textureSelected;
			sf::Sprite sprite;
			sf::Sprite spriteSelected;
			float sc;
		};
	
	GameOverResult show(sf::RenderWindow& window);
	sf::String getUserName();

private:
	GameOverResult GetGameOverResponse(sf::RenderWindow& window);
	GameOverResult HandleClick(int x, int y);
	void highlightGameOver(int, int);
	std::list<GameOverItem> _GameOverItems;

	//staff for drawing
	
	sf::Sprite sprite;
	sf::Sprite logoImage;
	void drawTextes(sf::RenderWindow&);
	sf::String userName;
	
};