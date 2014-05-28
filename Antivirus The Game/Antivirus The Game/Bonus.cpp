#include "main.h"
#include "Bonus.h"
#include "Game.h"
// todo: мигание бонусов и их пропадание через секунд 5-7, возможно, новые бонусы, иконки бонусов
// todo: окно Game Over
Bonus::Bonus()
{
}

Bonus::Bonus(int x,int y)
{
	setExisted(true);
	setType("Bonus0");
	//chose bonus type (0-radius 1-size 2-speed)
	int bonusTypeChance = rand()%100+1;

	if(bonusTypeChance <= 10)
	{
		setType("Bonus1");
		load("images/bonuses/bonus11.png");
	}
	if(bonusTypeChance > 10 && bonusTypeChance <= 50)
	{
		setType("Bonus0");
		load("images/bonuses/bonus12.png");
	}
	if(bonusTypeChance > 50 && bonusTypeChance <=100)
	{
		setType("Bonus2");
		load("images/bonuses/bonus13.png");
	}
	assert(isLoaded());
		
	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().width / 2);
	getSprite().setPosition(x,y);
	clock.restart();
}

Bonus::~Bonus()
{
}

void Bonus::draw(sf::RenderWindow & window)
{
    VisibleGameObject::draw(window);
}

void Bonus::update(float elapsedTime)
{
	int clockTime = clock.getElapsedTime().asMilliseconds();
	getSprite().setColor(sf::Color(255,255,255,255-clockTime*0.03642));
	if(clockTime*0.03642 > 254) setExisted(false);
}