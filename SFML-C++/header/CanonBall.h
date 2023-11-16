#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameObject.h"

class CanonBall : public GameObject
{
public:
	CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection);

	//void Draw(sf::RenderWindow& window);

	void OnCollisionEnter(float depthX, float depthY);
	void OnCollisionStay();
	void OnCollisionExit();
};
