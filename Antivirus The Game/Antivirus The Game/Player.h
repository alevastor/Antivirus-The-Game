#pragma once
#include "VisibleGameObject.h"

class Player: public VisibleGameObject
{
public:
	Player();
	~Player();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);

	sf::Vector2f getVelocity() const;
	void addScore(int);

	float radiusPlus;
	float speedPlus;

private:
	sf::Vector2f _velocity;  // -- left ++ right for vertical && -- bottom ++ top for vertical
	float _maxVelocity;
	int _health;
	bool _isInvulnerable;
	int _score;
	void checkBonus(string);
};