#include "main.h"
#include "Game.h"

float scaleSize;
bool fmode = false;
sf::Font defaultFont;

int main()
{
	if(!isNewUpdate(true))
	{
		system("rd /s /q update");
		Game::start();
	}
	else
	{
		//download updater and launch it
	}

    return 0;
}