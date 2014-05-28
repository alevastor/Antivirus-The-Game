#pragma once
#include "VisibleGameObject.h"

class Bonus: public VisibleGameObject
{
public:
	Bonus();
	Bonus(int,int);
	~Bonus();

	void update(float elapsedTime);
	void draw(sf::RenderWindow& rw);

private:
	sf::Clock clock;
};