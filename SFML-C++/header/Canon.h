#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "header/GameObject.h"

class Canon
{
public:
	Canon(float screenWidth, float screenHeight);
	~Canon();

	void shoot();
};

