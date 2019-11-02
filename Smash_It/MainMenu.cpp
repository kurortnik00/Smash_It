#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuItem::MenuItem(sf::Vector2f position, MenuResult action)
	:_position(position), text("", font, 120), _action(action)
{
	font.loadFromFile("font/18123.ttf");
	//text.setFillColor(sf::Color(0, 0, 0));
	sf::Image image;
	image.loadFromFile("images/menu/1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);
	animationFrame = 0;
	_radius = 150;
	
	_center = sf::Vector2f(position.x + _sprite.getTexture()->getSize().x / 2, position.y + _sprite.getTexture()->getSize().y / 2);


	image.loadFromFile("images/menu/string-1.png");
	image.createMaskFromColor(sf::Color(255, 255, 255));
	_stringTexture.loadFromImage(image);
	_stringSprite.setTexture(_stringTexture);
	_stringSprite.setPosition(_center + sf::Vector2f(-30, 150));
}

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window, std::map<std::string, float>& TOP_List)
{
	MainMenu::velocity = sf::Vector2f(0, 0.01);
	//Load menu image from file
	sf::Image image;
	image.loadFromFile("images/back_ground_1.png");
	sf::Texture texture;//создаем объект Texture (текстура)
	texture.loadFromImage(image);//передаем в него объект Image (изображения)
	//создаем объект Sprite(спрайт)
	sprite.setTexture(texture);//передаём в него объект Texture (текстуры)




	//Play menu item coordinates
	MenuItem playButton(sf::Vector2f(300,100), Play);
	std::ostringstream play_buttonStr;
	play_buttonStr << "Play";
	playButton.text.setString(play_buttonStr.str());
	playButton.text.setPosition(playButton._center - sf::Vector2f(110, 80));

	//Exit menu item coordinates
	//MenuItem exitButton(sf::Vector2f(1750, -200), Exit);

	MenuItem topScore_Button(sf::Vector2f(800, 100), Score_board);
	std::ostringstream topScore_buttonStr;
	topScore_buttonStr << "TOP \n list";
	topScore_Button.text.setString(topScore_buttonStr.str());
	topScore_Button.text.setPosition(topScore_Button._center - sf::Vector2f(105, 145));


	_menuItems.push_back(playButton);
	_menuItems.push_back(topScore_Button);

	Draw(window);
	
	MenuResult clicResult = GetMenuResponse(window);
	
	if (clicResult == Score_board)
	{
		std::map<std::string, float>::const_iterator itr = TOP_List.begin();
		while (itr != TOP_List.end())
		{
			std::cout << itr->first;
			std::cout << "    ";
			std::cout << itr->second;
			std::cout << "\n";
			itr++;
		}
	}

	return clicResult;
}



void MainMenu::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(0, 0, 0)); 
	window.draw(sprite);
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		window.draw((*it)._stringSprite);
		window.draw((*it)._sprite);
		window.draw((*it).text);
	}
	window.display();
}

void MainMenu::Update(sf::RenderWindow& window)
{
	std::list<MenuItem>::iterator it;
	
	

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		(*it).Move(velocity);
		
	}
	k++;
	if (k > 5000)
	{
		velocity = -velocity;
		k = 0;
	}
}



MainMenu::MenuResult MainMenu::HandleClick(sf::RenderWindow& window, int x, int y)				//Проверка куда кликнули мышью
{
	std::list<MenuItem>::iterator it;
	
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		float radius = (*it)._radius;
		if (dist2((*it)._center, sf::Vector2f(x,y)) < radius*radius)
		{
			return (*it)._action;										//Возврацает номер "сцены" (состояния)
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)		
{
	sf::Event menuEvent;
	

	while (true)
	{
		MainMenu::Update(window);
		MainMenu::Draw(window);

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(window, menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}

float MainMenu::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void MainMenu::MenuItem::Move(sf::Vector2f pos)
{
	_sprite.move(pos);
	_stringSprite.move(pos);
	text.move(pos);
}