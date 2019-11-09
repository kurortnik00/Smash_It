#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"


class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static void countIncriment();

private:
	static bool IsExiting();
	static void GameLoop();
	static void ShowSplashScreen();
	static void ShowMenu();
	//static void ShowCustomScreen();
	static void Init(int targ_count);
	static void reInit(int targ_count);
	static int  targetCount;
	static int getRandomNumber(int min, int max);
	static void TOP_List_Update();
	static void GameOver_Screen();
	
	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, GameOver
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
	static int smashCount;
	static std::set<std::pair<float, std::string>> TOP_List;
	static bool kinectControl;

};