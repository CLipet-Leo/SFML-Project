#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(float x, float y, sf::Color color, float width, float height);
	~Brick();

	void OnCollisionEnter(float depthX, float depthY);
	void OnCollisionStay();
	void OnCollisionExit();

};

