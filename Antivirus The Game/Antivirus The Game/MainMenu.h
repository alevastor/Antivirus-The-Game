#pragma once
#include <list>
#include "Game.h"

class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };	
	
	struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
			sf::Texture texture;
			sf::Texture textureSelected;
			sf::Sprite sprite;
			sf::Sprite spriteSelected;
			float sc;
		};
	
	MenuResult show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	void highlightMenu(int, int);
	std::list<MenuItem> _menuItems;

	//staff for drawing
	
	sf::Sprite sprite;
	sf::Sprite logoImage;
	
};