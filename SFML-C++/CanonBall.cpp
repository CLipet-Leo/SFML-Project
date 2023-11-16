#include "header/CanonBall.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


CanonBall::CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection)
	: GameObject(x, y, color, width, height)
{
	cout << "Created !!!" << endl;

}

CanonBall::~CanonBall()
{}
