#pragma once

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	int screenW, screenH;
	sf::RenderWindow* oWindow;

	GameManager(int width, int height);
	~GameManager();

	void GameLoop();

	void detectEvent();
};

