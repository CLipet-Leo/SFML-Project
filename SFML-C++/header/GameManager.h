#pragma once

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	int screenW, screenH;
	sf::RenderWindow* oWindow;

	GameManager(int width, int height);
	~GameManager();

	bool Bloup(GameObject& object1, GameObject& object2);

	void GameLoop();

	void detectEvent();
};

