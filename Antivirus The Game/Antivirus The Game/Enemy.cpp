#include "main.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>
#include "Bonus.h"

Enemy::Enemy() : 
	_velocity(sf::Vector2f(0.0f,0.0f)), _maxVelocity(170.0f)
{
	// chose direction && get speed
	setType("Enemy");
	int k = rand()%4+1;
	load("images/enemies/enemy1"+to_string(k)+".png");
	assert(isLoaded());
	_currentDifficult = (int)Game::difficult;
	getSprite().setOrigin(getSprite().getGlobalBounds().width/2,getSprite().getGlobalBounds().height/2);
	switch(rand()%4)
	{
	case 0:
		getSprite().setPosition(Game::BORDER_LEFT,Game::BORDER_TOP);
		_velocity.x = rand()%(int)_maxVelocity;
		_velocity.y = rand()%(int)_maxVelocity;
		break;
	case 1:
		getSprite().setPosition(Game::BORDER_RIGHT-Game::BORDER_LEFT,Game::BORDER_TOP);
		_velocity.x = -rand()%(int)_maxVelocity;
		_velocity.y = rand()%(int)_maxVelocity;
		break;
	case 2:
		getSprite().setPosition(Game::BORDER_LEFT,Game::BORDER_BOTTOM-Game::BORDER_TOP);
		_velocity.x = rand()%(int)_maxVelocity;
		_velocity.y = -rand()%(int)_maxVelocity;
		break;
	case 3:
		getSprite().setPosition(Game::BORDER_RIGHT-Game::BORDER_LEFT,Game::BORDER_BOTTOM-Game::BORDER_TOP);
		_velocity.x = -rand()%(int)_maxVelocity;
		_velocity.y = -rand()%(int)_maxVelocity;
		break;
	}
	Game::addEnemy();
}

Enemy::~Enemy(void)
{
	Game::subEnemy();
	Game::checkForBonus(getSprite().getPosition().x,getSprite().getPosition().y);
}

void Enemy::draw(sf::RenderWindow & window)
{
    VisibleGameObject::draw(window);
}

sf::Vector2f Enemy::getVelocity() const
{
    return _velocity;
}

void Enemy::update(float elapsedTime)
{
	getSprite().setOrigin(getSprite().getGlobalBounds().width/2,getSprite().getGlobalBounds().height/2);
	_maxVelocity = 170 + 10 * (int)Game::difficult;
	sf::Vector2f pos = this->getPosition();
	getSprite().rotate(rand()%2-1);
	_velocity.x += rand()%(int)((_maxVelocity*2) / 10 + 1) - _maxVelocity/10;
	_velocity.y += rand()%(int)((_maxVelocity*2) / 10 + 1) - _maxVelocity/10;
	if(_currentDifficult != (int)Game::difficult)
	{
		_currentDifficult = (int)Game::difficult;
		_velocity.x = -_velocity.x;
		_velocity.y = -_velocity.y;
	}
	if(_velocity.x > _maxVelocity)
		_velocity.x = _maxVelocity;
	if(_velocity.x < -_maxVelocity)
		_velocity.x = -_maxVelocity;
	if(_velocity.y > _maxVelocity)
		_velocity.y = _maxVelocity;
	if(_velocity.y < -_maxVelocity)
		_velocity.y = -_maxVelocity;

	if((pos.x  < getSprite().getGlobalBounds().width/2 + Game::BORDER_LEFT && _velocity.x < 0)
		|| (pos.x > (Game::BORDER_RIGHT - getSprite().getGlobalBounds().width/2) && _velocity.x > 0))
    {
		_velocity = sf::Vector2f(-_velocity.x,_velocity.y);
    }

	if((pos.y  < getSprite().getGlobalBounds().height/2 + Game::BORDER_TOP && _velocity.y < 0)
		|| (pos.y > (Game::BORDER_BOTTOM - getSprite().getGlobalBounds().height/2) && _velocity.y > 0))
    {
		_velocity = sf::Vector2f(_velocity.x,-_velocity.y);
    }

	getSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
}