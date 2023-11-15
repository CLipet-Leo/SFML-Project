#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "CanonBall.h"

class Canon : public GameObject
{
public:
	Canon(float x, float y, sf::Color color, float width, float height);
	~Canon();

	void Shoot(sf::Vector2i& oOrientationPosition, std::vector<CanonBall>* oBall);

protected:
	//Vector2i* mouseVect = NULL;
};

