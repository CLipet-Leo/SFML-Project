#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameObject.h"

class CanonBall : public GameObject
{
public:
	CanonBall(float x, float y, sf::Color color, float radius);

};

