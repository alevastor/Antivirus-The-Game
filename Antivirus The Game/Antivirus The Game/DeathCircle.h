#pragma once
#include "VisibleGameObject.h"

class DeathCircle : public VisibleGameObject
{
public:
	DeathCircle();
	~DeathCircle();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);
	void setRadius(float);
	void setPlayerDamaged(bool);

private:
	float _radius;
	float _minRadius;
	sf::CircleShape circle;
	bool _isPlayerDamaged;
};