#include "main.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("images/game_bg2.png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255,255,255,76.5));
	
	//Load small logo image
	sf::Texture logoTexture;
	logoTexture.loadFromFile("images/small_logo.png");
	logoImage.setTexture(logoTexture);
	logoImage.setPosition(197,0);

	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 303;
	playButton.rect.height = 107;
	playButton.rect.left = 57;
	playButton.rect.width = 210;
	playButton.action = Play;
	playButton.sc = 0;
	playButton.texture.loadFromFile("images/menu/play.png");
	playButton.textureSelected.loadFromFile("images/menu/play_selected.png");
	playButton.sprite.setTexture(playButton.texture);
	playButton.spriteSelected.setTexture(playButton.textureSelected);
	playButton.spriteSelected.setColor(sf::Color(255,255,255,playButton.sc));
	playButton.sprite.setPosition(playButton.rect.left,playButton.rect.top);
	playButton.spriteSelected.setPosition(playButton.rect.left,playButton.rect.top);

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 57;
	exitButton.rect.width = 183;
	exitButton.rect.top = 430;
	exitButton.rect.height = 88;
	exitButton.action = Exit;
	exitButton.sc = 0;
	exitButton.texture.loadFromFile("images/menu/exit.png");
	exitButton.textureSelected.loadFromFile("images/menu/exit_selected.png");
	exitButton.sprite.setTexture(exitButton.texture);
	exitButton.spriteSelected.setTexture(exitButton.textureSelected);
	exitButton.spriteSelected.setColor(sf::Color(255,255,255,exitButton.sc));
	exitButton.sprite.setPosition(exitButton.rect.left,exitButton.rect.top);
	exitButton.spriteSelected.setPosition(exitButton.rect.left,exitButton.rect.top);

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	return GetMenuResponse(window);
}

void MainMenu::highlightMenu(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = it->rect;
		if (menuItemRect.contains(sf::Vector2<int>(x, y)))
		{
			if(it->sc<255)
				it->sc+=15;
		}
		else
		{
			if(it->sc>0)
				it->sc-=15;
		}
		it->spriteSelected.setColor(sf::Color(255,255,255,it->sc));
	}
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = it->rect;
		if (menuItemRect.contains(sf::Vector2<int>(x, y)))
		{
			return it->action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	while(true)
	{
		sf::Event menuEvent;
		while(window.pollEvent(menuEvent))
		{
			/*if(menuEvent.type == sf::Event::EventType::KeyPressed)
			{
				if(menuEvent.key.alt && menuEvent.key.code == sf::Keyboard::Return)
				{
					if(fmode)										
						fmode = false;
					else
						fmode = true;
					createWindow(window, fmode);
				}
			}*/
			if(menuEvent.type == sf::Event::MouseButtonPressed)
			{
				if(menuEvent.mouseButton.button == sf::Mouse::Left)
					return HandleClick(menuEvent.mouseButton.x,menuEvent.mouseButton.y);
			}
			if(menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
		highlightMenu(menuEvent.mouseMove.x,menuEvent.mouseMove.y);
		window.clear();
		window.draw(sprite);
		window.draw(logoImage);

		std::list<MenuItem>::iterator it;
		for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
		{
			window.draw(it->sprite);
			window.draw(it->spriteSelected);
		}

		window.display();

		Sleep(10); // TODO: fix it
	}
}