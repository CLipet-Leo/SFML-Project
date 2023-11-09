#pragma once

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	int screenW, screenH;
	sf::RenderWindow* oWindow;
	sf::Vector2i* mPos;
	sf::Vector2i clicPos;

	GameManager(int width, int height);
	~GameManager();

	void GameLoop();

	void detectEvent();
};

