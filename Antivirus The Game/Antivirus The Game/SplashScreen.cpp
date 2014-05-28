#include "main.h"
#include "SplashScreen.h"
#include "Game.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	sf::Image image;
	if(!image.loadFromFile("images/SplashScreen.png"))
	{
		// error
		return;
	}
	
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	int opacity=0;
	bool isAppear=false;
	sf::Clock Clock;

	sf::Event event;
	while(true)
	{
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::EventType::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Space)
				{
					return;
				}
				/*if(event.key.alt && event.key.code == sf::Keyboard::Return)
				{
					if(fmode)										
						fmode = false;
					else
						fmode = true;
					createWindow(renderWindow, fmode);
				}*/
			}
			if(event.type == sf::Event::EventType::Closed )
			{
				Game::setGameState("Exiting");
				return;
			}
		}
		if(!isAppear)
		{
			opacity+=5;
			if(opacity >= 255) 
			{
				isAppear = true;
				Clock.restart();
			}			
		}
		float elapsedTime = Clock.getElapsedTime().asSeconds();
		if(isAppear && elapsedTime > 2.5)
		{
			opacity -= 5;
			if(opacity <= 0) return;
		}
		sprite.setColor(sf::Color(255,255,255,opacity));
		sprite.setScale(scaleSize,scaleSize);
		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}
}