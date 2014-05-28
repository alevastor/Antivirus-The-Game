#include "main.h"
#include "Game.h"

void createWindow(sf::RenderWindow &window, bool fmode)
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	mode = sf::VideoMode::getDesktopMode();
	if(fmode==true)
	{
		window.create(mode, GAME_TITLE+" "+GAME_VERSION, sf::Style::Fullscreen);
	}
	else
	{
		//int resizexy;
		//resizexy=mode.width/10;  // uncomment for FullScreen
		//mode.width-=resizexy;
		//mode.height-=resizexy;
		mode.width=Game::SCREEN_WIDTH;
		mode.height=Game::SCREEN_HEIGHT;
		window.create(mode, GAME_TITLE+" "+GAME_VERSION, sf::Style::Close);
	}
	scaleSize=mode.height*1./SCREEN_HEIGHT_DEFAULT;

	window.setFramerateLimit(60);
}