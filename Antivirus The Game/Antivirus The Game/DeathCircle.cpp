#include "main.h"
#include "DeathCircle.h"
#include "Player.h"
#include "Game.h"

DeathCircle::DeathCircle() : _radius(0), _isPlayerDamaged(false)
{
	setExisted(true);
	Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("Player"));
	_minRadius = (player->getSprite().getGlobalBounds().width/2 + player->getSprite().getGlobalBounds().height/2)/2;
	circle.setRadius(_minRadius);
	circle.setFillColor(sf::Color(255,255,255,30));
	circle.setOutlineColor(sf::Color(255,255,255,60));
	circle.setOutlineThickness(4);
	circle.setPointCount(500);
	setType("DeathCircle");
}

DeathCircle::~DeathCircle(void)
{
}

void DeathCircle::draw(sf::RenderWindow & window)
{
	window.draw(circle);
}

void DeathCircle::update(float elapsedTime)
{
	Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("Player"));
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_radius+=0.5+player->radiusPlus;
		circle.setRadius(_radius);
	}
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || _isPlayerDamaged == true)
	{
		// check if enemies in circle
		if(_radius != _minRadius)
		{
			std::map<std::string, VisibleGameObject*>::const_iterator itr;
			for(itr = Game::getGameObjectManager()._gameObjects.begin(); itr != Game::getGameObjectManager()._gameObjects.end(); itr++)
			{
				if(itr->second->getType() == "Enemy")
				{
					int enemyWidth = itr->second->getSprite().getGlobalBounds().width;
					int enemyHeight = itr->second->getSprite().getGlobalBounds().height;
					double difX = pow(circle.getPosition().x - itr->second->getPosition().x,2);
					double difY = pow(circle.getPosition().y - itr->second->getPosition().y,2);
					if((sqrt(difX + difY) + enemyWidth/2. <= _radius+circle.getOutlineThickness()) && 
						(sqrt(difX + difY) + enemyHeight/2. <= _radius+circle.getOutlineThickness()))
					{
					   itr->second->setExisted(false);
					   Player* player = dynamic_cast<Player*>(Game::getGameObjectManager().get("Player"));
					   player->addScore(Game::difficult);
					}
				}
			}
		}
		_radius = _minRadius;
		_isPlayerDamaged = false;
		circle.setRadius(_radius);
		circle.setOrigin(circle.getGlobalBounds().width/2,circle.getGlobalBounds().height/2);
	}
	if(_radius == _minRadius)
	{
		circle.setFillColor(sf::Color(255,255,255,0));
		circle.setOutlineColor(sf::Color(255,255,255,0));
	}
	else
	{
		circle.setFillColor(sf::Color(255,255,255,30));
		circle.setOutlineColor(sf::Color(255,255,255,60));
	}
	circle.setOrigin(circle.getGlobalBounds().width/2-circle.getOutlineThickness(),
		circle.getGlobalBounds().height/2-circle.getOutlineThickness());
	circle.setPosition(player->getPosition());
	circle.move(player->getVelocity()*elapsedTime);
}

void DeathCircle::setRadius(float r)
{
	_radius = r;
}

void DeathCircle::setPlayerDamaged(bool b)
{
	_isPlayerDamaged = b;
}