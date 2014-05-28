#include "main.h"
#include "Player.h"
#include "Game.h"
#include "Bonus.h"

sf::Clock _invulnerableClock;

Player::Player() : 
	_velocity(sf::Vector2f(0.0f,0.0f)), _maxVelocity(600.0f), _health(4), _isInvulnerable(false), _score(0), radiusPlus(0.f), speedPlus(0.f)
{
	load("images/player.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().width / 2);
	getSprite().setPosition(((Game::BORDER_RIGHT-Game::BORDER_LEFT)/2),((Game::BORDER_BOTTOM-Game::BORDER_TOP)/2));
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow & window)
{
	if(_isInvulnerable) 
		getSprite().setColor(sf::Color(255,255,255,20));
	else
		getSprite().setColor(sf::Color(255,255,255,255));
	
	sf::Text titleText;
	sf::Text valueText;

	titleText.setFont(defaultFont);
	titleText.setCharacterSize(30);
	titleText.setColor(sf::Color(255,255,255));

	valueText.setFont(defaultFont);
	valueText.setCharacterSize(50);
	valueText.setColor(sf::Color(255,255,255));
	//size title
	titleText.setString("Size");
	titleText.setPosition(631,6);
	window.draw(titleText);
	//size
	valueText.setString(to_string(_health)+" kb");
	valueText.setPosition(631,36);
	window.draw(valueText);
	//score title
	titleText.setString("Score");
	titleText.setPosition(631,113);
	window.draw(titleText);
	//score
	valueText.setString(to_string(_score));
	valueText.setPosition(631,143);
	window.draw(valueText);
	//bestScore
	titleText.setString("best " + to_string(Game::bestScore));
	titleText.setPosition(631,198);
	titleText.setCharacterSize(25);
	window.draw(titleText);
	titleText.setCharacterSize(30);
	//enemies title
	titleText.setString("Viruses");
	titleText.setPosition(631,253);
	window.draw(titleText);
	//enemies
	valueText.setString(to_string(Game::getEnemiesCount()));
	valueText.setPosition(631,283);
	window.draw(valueText);
	//difficulty title
	titleText.setString("Difficulty");
	titleText.setPosition(631,348);
	window.draw(titleText);
	//difficulty
	valueText.setString(to_string((int)Game::difficult));
	valueText.setPosition(631,383);
	window.draw(valueText);
	//bonus title
	titleText.setString("Bonuses");
	titleText.setPosition(631,448);
	window.draw(titleText);
	//bonus (radius) title
	titleText.setString("radius");
	titleText.setPosition(631,491);
	window.draw(titleText);

	valueText.setCharacterSize(33);
	//bonus (radius)
	valueText.setString("x"+to_string_with_precision((0.5+radiusPlus)/0.5,3));
	valueText.setPosition(741,488);
	window.draw(valueText);
	//bonus (speed) title
	titleText.setString("speed");
	titleText.setPosition(631,536);
	window.draw(titleText);
	//bonus (speed)
	valueText.setString("x"+to_string_with_precision((2+speedPlus)/2,3));
	valueText.setPosition(741,533);
	window.draw(valueText);

    VisibleGameObject::draw(window);
}

sf::Vector2f Player::getVelocity() const
{
    return _velocity;
}

void Player::update(float elapsedTime)
{
	if(!_isInvulnerable)
	{
		std::map<std::string, VisibleGameObject*>::const_iterator itr;
		for(itr = Game::getGameObjectManager()._gameObjects.begin(); itr != Game::getGameObjectManager()._gameObjects.end(); itr++)
		{
			if(itr->second->getType() == "Enemy")
			{
				int enemyWidth = itr->second->getSprite().getGlobalBounds().width;
				int enemyHeight = itr->second->getSprite().getGlobalBounds().height;
				double difX = pow(getSprite().getPosition().x - itr->second->getPosition().x,2);
				double difY = pow(getSprite().getPosition().y - itr->second->getPosition().y,2);
				if((sqrt(difX + difY) - enemyWidth/2. <= getSprite().getGlobalBounds().width/2) && 
					(sqrt(difX + difY) - enemyHeight/2. <= getSprite().getGlobalBounds().height/2))
				{
					_health -= 1;
					DeathCircle* deathCircle = dynamic_cast<DeathCircle*>(Game::getGameObjectManager().get("DeathCircle"));
					deathCircle->setPlayerDamaged(true);
					_isInvulnerable = true;
					_invulnerableClock.restart();
				}
			}
		}
	}
	else
	{
		if(_invulnerableClock.getElapsedTime().asSeconds() > 3)
			_isInvulnerable = false;
	}

	std::map<std::string, VisibleGameObject*>::const_iterator itr;
	for(itr = Game::getGameObjectManager()._gameObjects.begin(); itr != Game::getGameObjectManager()._gameObjects.end(); itr++)
	{
		if(itr->second->getType().find("Bonus") != -1 )
		{
			int bonusWidth = itr->second->getSprite().getGlobalBounds().width;
			int bonusHeight = itr->second->getSprite().getGlobalBounds().height;
			double difX = pow(getSprite().getPosition().x - itr->second->getPosition().x,2);
			double difY = pow(getSprite().getPosition().y - itr->second->getPosition().y,2);
			if((sqrt(difX + difY) - bonusWidth/2. <= getSprite().getGlobalBounds().width/2) && 
				(sqrt(difX + difY) - bonusHeight/2. <= getSprite().getGlobalBounds().height/2))
			{
				checkBonus(itr->second->getType());
				itr->second->setExisted(false);
			}
		}
	}

	if(_health <= 0)
	{
		Game::setGameState("GameOver");
	}

	sf::Vector2f pos = this->getPosition();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(Game::getWindow());

	_velocity.x = (mousePosition.x - pos.x)*(2+speedPlus);
	_velocity.y = (mousePosition.y - pos.y)*(2+speedPlus);

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
		_velocity = sf::Vector2f(0,_velocity.y);
    }

	if((pos.y  < getSprite().getGlobalBounds().height/2 + Game::BORDER_TOP && _velocity.y < 0)
		|| (pos.y > (Game::BORDER_BOTTOM - getSprite().getGlobalBounds().height/2) && _velocity.y > 0))
    {
		_velocity = sf::Vector2f(_velocity.x,0);
    }

	getSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
	Game::currentScore = _score;
}

void Player::addScore(int s)
{
	_score += s;
	if(_score > Game::bestScore)
		Game::bestScore = _score;
}

void Player::checkBonus(string bonusType)
{
	if(bonusType == "Bonus0")
	{
		radiusPlus+=0.025;
	}
	if(bonusType == "Bonus1")
	{
		_health+=1;
	}
	if(bonusType == "Bonus2")
	{
		speedPlus+=0.1;
	}
}