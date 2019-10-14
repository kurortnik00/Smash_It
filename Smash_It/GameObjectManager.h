#pragma once
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;
	
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll(sf::Event& event);
	void setAllPlased();


private:
	sf::Sprite logosprite;
	sf::Texture logotexture;
	std::map<std::string, VisibleGameObject*> _gameObjects;
	sf::Clock clock;
	float countDelay;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};