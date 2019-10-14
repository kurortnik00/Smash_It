#pragma once
#include "VisibleGameObject.h"
#include <sstream>

class SmashCounter : public VisibleGameObject
{
public:
	SmashCounter();
	~SmashCounter();
	void Load(std::string filename);
	void countIncroment();
	void Draw(sf::RenderWindow & renderWindow);
	int GetCount();
	void setFinished(bool res);
	bool getFinished();
	void reInit();

private:
	int smashCount;
	sf::Font font;
	sf::Text text;
	bool finished;
	float finishedScore;
	
};

