#pragma once
#include "Game.h"
#include <random>
#include "VisibleGameObject.h"
#include "BodyBasics.h"


class Target :
	public VisibleGameObject
{
public:
	Target();
	~Target();

	void Update(sf::Event& event);
	bool getState();
	bool getClickState();
	void setClickState(bool ans);
	void reInit();
	int getRandomNumber(int min, int max);
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
	void setKinectControl(bool kinectControl);


private:
	bool isActive;
	bool hasClicked;
	float spriteX, spriteY, w, h;
	void animation();
	int animationFrame;
	sf::Clock animationClock;
	bool animationStart;	
	void velocityAnimation();
	sf::Clock velocityAnimationClock;
	sf::Vector2f velocity;
	int windowSizeX, windowSizeY;
	void setRandomFlyStart();
	const sf::Vector2f constVelocity;
	float velocityAnimationTime;
	float animationTime;
	bool _kinectControl;

	sf::Vector2f HANDRIGHT_xy;
	float HANDRIGHT_z;
	float _trashHold;				//depth from sensor where interaction starts
	CBodyBasics kinectApplication;

	enum {
		SPINEBASE,
		SPINEMID,
		NECK,
		HEAD,
		SHOULDERLEFT,
		ELBOWLEFT,
		WRISTLEFT,
		HANDLEFT,
		SHOULDERRIGHT,
		ELBOWRIGHT,
		WRISTRIGHT,
		HANDRIGHT,
		HIPLEFT,
		KNEELEFT,
		ANKLELEFT,
		FOOTLEFT,
		HIPRIGHT,
		KNEERIGHT,
		ANKLERIGHT,
		FOOTRIGHT,
		SPINESHOULDER,
		HANDTIPLEFT,
		THUMBLEFT,
		HANDTIPRIGHT,
		THUMBRIGHT,
	};

};
