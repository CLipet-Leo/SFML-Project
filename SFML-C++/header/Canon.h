#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "header/GameObject.h"

class Canon : public GameObject
{
public:
	Canon(float screenWidth, float screenHeight);
	~Canon();

	void Rotate();

	void shoot();

protected:
	//Vector2i* mouseVect = NULL;
};

