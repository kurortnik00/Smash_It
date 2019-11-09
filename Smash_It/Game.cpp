#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Target.h"
#include "Timer.h"
#include "CustomScreen.h"
#include "SmashCounter.h"
#include "myKeyboard.h"
#include <random>
#include <iomanip>
#include <sstream>



void Game::Start(void)	//инициализация объектов
{
	if (_gameState != Uninitialized) return;

	_mainWindow.create(sf::VideoMode(1900, 1080), "Pang!");

	Game::Init(targetCount);
	srand(static_cast<unsigned int>(time(0)));


	_gameState = Game::ShowingMenu;		//Начинаем с меню

	while (!IsExiting())
	{
		GameLoop();
	}

	Game::_mainWindow.close();
}

bool Game::IsExiting()//для остановки GameLoop()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return Game::_mainWindow;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	
	switch (_gameState)
	{
		
		case Game::ShowingMenu:
		{
			ShowMenu();		
			break;
		}
		case Game::ShowingSplash:
		{
		
			ShowSplashScreen();
			break;
		}
		case Game::Playing:
		{
		
			
			_mainWindow.clear(sf::Color(0, 0, 0));
			
			_gameObjectManager.setAllPlased();
			
			_gameObjectManager.UpdateAll(currentEvent);		//Обновляет все объекты
			_gameObjectManager.DrawAll(_mainWindow);		//Рисует все объекты

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)		//Выход из сцены игры в меню по клавише ESC
				{
					_gameState = Game::ShowingMenu;
				}
			}
			if (_gameObjectManager.Get("timer1")->getFinished())
			{
				_gameState = Game::GameOver;
				
			}
			break;
		}
		case Game::GameOver:
		{
			GameOver_Screen();
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);					//Внутри бесконечный цикл прерываемый по нажатию любой клавиши
													
	_gameState = Game::ShowingMenu;
}


void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow, TOP_List);   //Возврацает значение нажатой "кнопки", т.е. что делать дальше: Играть или выйти из игры
																//Внутри бесконечный цикл прерываемый по нажатию одной из "кнопок" или закрытию окна
																	
	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			Game::reInit(targetCount);
			break;
	}
}

void Game::Init(int targ_count) {
	std::string targetFileNames[7] = {							//max targets = 14
		"images/balloon_green.png", "images/balloon_blue.png", "images/balloon_orange.png", "images/balloon_pinck.png",
		"images/balloon_purple.png", "images/balloon_red.png", "images/balloon_yellow.png"
	};
	

	for (int i = 0; i < targ_count; i++) {
		Target *tar = new Target();
		tar->Load(targetFileNames[i]);
		tar->setKinectControl(kinectControl);
		_gameObjectManager.Add(std::to_string(i), tar);
	}

	Timer *time1 = new Timer();
	time1->Load("font/11583.ttf");
	_gameObjectManager.Add("timer1", time1);

	SmashCounter *counter = new SmashCounter();
	counter->Load("font/11583.ttf");
	_gameObjectManager.Add("counter", counter);


	
}

void Game::reInit(int targ_count)
{
	for (int i = 0; i < targ_count; i++) {
		_gameObjectManager.Get(std::to_string(i))->reInit();
	}
	_gameObjectManager.Get("timer1")->reInit();
	_gameObjectManager.Get("counter")->reInit();
}


void Game::countIncriment() {

}

int Game::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Game::TOP_List_Update()
{

	sf::Event currentEvent;	
	std::string name = "";
	std::string scoreString = "Score: ";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << (int) _gameObjectManager.Get("counter")->getCount();
	scoreString += stream.str();

	
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		_mainWindow.pollEvent(currentEvent);
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			name += MyKeyboard::getChar();
		}
		
		_mainWindow.clear(sf::Color(0, 0, 0));

		sf::Font font;
		font.loadFromFile("font/11583.ttf");

		sf::Text gameOverText("Game Over", font, 150);
		gameOverText.setPosition(_mainWindow.getSize().x / 2 - 400, 100);

		sf::Text scoreText(scoreString, font, 150);
		scoreText.setPosition(_mainWindow.getSize().x / 2 - 400, 250);

		sf::Text text(name, font, 150);
		text.setPosition(_mainWindow.getSize().x / 2 - 300, 400);
		

		_mainWindow.draw(text);
		_mainWindow.draw(scoreText);
		_mainWindow.draw(gameOverText);
		_mainWindow.display();
	}


	if (TOP_List.size() > 4) TOP_List.erase(TOP_List.begin());

	TOP_List.insert(std::make_pair(_gameObjectManager.Get("counter")->getCount(), name));
	
	

}



void Game::GameOver_Screen()
{
	TOP_List_Update();
	_gameState = Game::ShowingMenu;
}

GameObjectManager Game::_gameObjectManager;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
int Game::targetCount = 7;				//max targets = 14 if you wana more change Init()
std::set<std::pair<float, std::string>> Game::TOP_List = { {6, "ASd"} , {5, "zzz"} , {1, "qq"} , {4, "44"} };
bool kinectControl = true;




