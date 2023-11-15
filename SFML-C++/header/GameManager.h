#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameObject.h"
#include "Canon.h"

class GameManager
{
public:
	int screenW, screenH;
	sf::RenderWindow* oWindow;
	sf::Event oEvent;
	bool event = false;
	sf::Vector2i mPos;
	sf::Vector2i clicPos;

	GameManager(int width = 400, int height = 400);
	~GameManager();

	void GameLoop();

	void detectEvent();
};

