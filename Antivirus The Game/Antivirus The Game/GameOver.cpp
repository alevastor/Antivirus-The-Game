#include "main.h"
#include "GameOver.h"
#include <sstream>

GameOver::GameOverResult GameOver::show(sf::RenderWindow& window)
{
	//Load GameOver image from file
	sf::Texture texture;
	texture.loadFromFile("images/game_bg2.png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255,255,255,76.5));

	userName = "no name";
	//TODO : read from file

	//Setup clickable regions

	//Restart item coordinates
	GameOverItem restartButton;
	restartButton.rect.top = 477;
	restartButton.rect.height = 80;
	restartButton.rect.left = 70;
	restartButton.rect.width = 298;
	restartButton.action = Restart;
	restartButton.sc = 0;
	restartButton.texture.loadFromFile("images/ui/gameoverbutton.png");
	restartButton.textureSelected.loadFromFile("images/ui/gameoverbutton_selected.png");
	restartButton.sprite.setTexture(restartButton.texture);
	restartButton.spriteSelected.setTexture(restartButton.textureSelected);
	restartButton.spriteSelected.setColor(sf::Color(255,255,255,restartButton.sc));
	restartButton.sprite.setPosition(restartButton.rect.left,restartButton.rect.top);
	restartButton.spriteSelected.setPosition(restartButton.rect.left,restartButton.rect.top);

	//Exit GameOver item coordinates
	GameOverItem submitButton;
	submitButton.rect.left = 456;
	submitButton.rect.width = 298;
	submitButton.rect.top = 477;
	submitButton.rect.height = 80;
	submitButton.action = Submit;
	submitButton.sc = 0;
	submitButton.texture.loadFromFile("images/ui/gameoverbutton.png");
	submitButton.textureSelected.loadFromFile("images/ui/gameoverbutton_selected.png");
	submitButton.sprite.setTexture(submitButton.texture);
	submitButton.spriteSelected.setTexture(submitButton.textureSelected);
	submitButton.spriteSelected.setColor(sf::Color(255,255,255,submitButton.sc));
	submitButton.sprite.setPosition(submitButton.rect.left,submitButton.rect.top);
	submitButton.spriteSelected.setPosition(submitButton.rect.left,submitButton.rect.top);

	_GameOverItems.push_back(restartButton);
	_GameOverItems.push_back(submitButton);

	return GetGameOverResponse(window);
}

void GameOver::highlightGameOver(int x, int y)
{
	std::list<GameOverItem>::iterator it;

	for ( it = _GameOverItems.begin(); it != _GameOverItems.end(); it++)
	{
		sf::Rect<int> GameOverItemRect = it->rect;
		if (GameOverItemRect.contains(sf::Vector2<int>(x, y)))
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

GameOver::GameOverResult GameOver::HandleClick(int x, int y)
{
	std::list<GameOverItem>::iterator it;

	for ( it = _GameOverItems.begin(); it != _GameOverItems.end(); it++)
	{
		sf::Rect<int> GameOverItemRect = it->rect;
		if (GameOverItemRect.contains(sf::Vector2<int>(x, y)))
		{
			return it->action;
		}
	}
	return Nothing;
}

GameOver::GameOverResult GameOver::GetGameOverResponse(sf::RenderWindow& window)
{
	while(true)
	{
		sf::Event GameOverEvent;
		while(window.pollEvent(GameOverEvent))
		{
			/*if(GameOverEvent.type == sf::Event::EventType::KeyPressed)
			{
				if(GameOverEvent.key.alt && GameOverEvent.key.code == sf::Keyboard::Return)
				{
					if(fmode)										
						fmode = false;
					else
						fmode = true;
					createWindow(window, fmode);
				}
			}*/
			if(GameOverEvent.type == sf::Event::KeyPressed)
			{
				if(GameOverEvent.key.code == sf::Keyboard::BackSpace)
				{ 
					if(userName.getSize() > 0)
						userName.erase(userName.getSize() - 1);
				}
			}
			if (GameOverEvent.type == sf::Event::TextEntered)
			{
				if(GameOverEvent.text.unicode < 127 && GameOverEvent.text.unicode != 8 && userName.getSize() < 16)
				{
					userName.insert(userName.getSize(), GameOverEvent.text.unicode);
				}
			}
			if(GameOverEvent.type == sf::Event::MouseButtonPressed)
			{
				if(GameOverEvent.mouseButton.button == sf::Mouse::Left)
					return HandleClick(GameOverEvent.mouseButton.x,GameOverEvent.mouseButton.y);
			}
			if(GameOverEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
		highlightGameOver(GameOverEvent.mouseMove.x,GameOverEvent.mouseMove.y);
		window.clear();
		window.draw(sprite);
		window.draw(logoImage);

		drawTextes(window);

		std::list<GameOverItem>::iterator it;
		for ( it = _GameOverItems.begin(); it != _GameOverItems.end(); it++)
		{
			window.draw(it->sprite);
			window.draw(it->spriteSelected);
		}

		window.display();

		Sleep(10); // TODO: fix it
	}
}

void GameOver::drawTextes(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFont(defaultFont);

	text.setString("Name: "+userName);
	text.setPosition(102,211);
	text.setCharacterSize(34);
	window.draw(text);

	text.setString("Game Over");
	text.setPosition(102,80);
	text.setCharacterSize(103);
	window.draw(text);

	text.setPosition(196,271);
	text.setString("Score");
	text.setCharacterSize(58);
	window.draw(text);

	text.setPosition(233,364);
	text.setString("Best");
	window.draw(text);

	text.setPosition(456,271);
	text.setString(to_string(Game::currentScore));
	window.draw(text);

	text.setPosition(456,364);
	text.setString(to_string(Game::bestScore));
	window.draw(text);

	text.setCharacterSize(51);
	text.setPosition(79,480);
	text.setString("New Game");
	window.draw(text);

	text.setPosition(515,480);
	text.setString("Submit");
	window.draw(text);

	if(Game::bestScore == Game::currentScore)
		text.setColor(sf::Color(168,22,22,255));
	else
		text.setColor(sf::Color(168,22,22,0));
	text.setPosition(140,400);
	text.setString("New");
	text.setRotation(-45);
	window.draw(text);
}

sf::String GameOver::getUserName()
{
	return userName;
}