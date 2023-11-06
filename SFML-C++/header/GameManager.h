#pragma once

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	sf::RenderWindow* oWindow;

	GameManager(int width, int height);
	~GameManager();

	void GameLoop();

};

