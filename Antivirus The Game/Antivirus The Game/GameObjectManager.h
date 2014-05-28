#pragma once
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(string name, VisibleGameObject* gameObject);
	void remove(string name);
	void removeNotExisted();
	int getObjectCount() const;
	VisibleGameObject* get(string name) const;

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll();

	std::map<string, VisibleGameObject*> _gameObjects;

private:
	

	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<string,VisibleGameObject*> &p) const
		{
			delete p.second;
		}
	};
};