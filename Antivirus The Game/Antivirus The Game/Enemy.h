#pragma once
#include "VisibleGameObject.h"

class Enemy : public VisibleGameObject
{
public:
	Enemy();
	~Enemy();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);

	sf::Vector2f getVelocity() const;

private:
	sf::Vector2f _velocity;  // -- left ++ right for vertical && -- bottom ++ top for vertical
	float _maxVelocity;
	int _currentDifficult;
};