#pragma once

#include <iostream>

#include "GameObject.h"
#include "Canon.h"
#include "CanonBall.h"
#include "Brick.h"

class GameManager
{
public:
	int screenW, screenH;
	sf::RenderWindow* oWindow;
	sf::Event oEvent;
	bool moveEvent = false, clicEvent = false;
	sf::Vector2i mPos;
	sf::Vector2i clicPos;

	std::vector<CanonBall*> oBullet;
	std::vector<Brick*> oBricks;

	GameManager(int width = 400, int height = 400);
	~GameManager();

	//bool RectOverlap(GameObject& object1, GameObject& object2);

	void GameLoop();

	void detectEvent();
};

