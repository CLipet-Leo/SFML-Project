#include "header/CanonBall.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


CanonBall::CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection)
	: GameObject(x, y, color, width, height)
{
	oShape = new sf::CircleShape(radius);
	oShape->setFillColor(color);

	SetPosition(x, y);

	SetDirection(oOriginDirection.x, oOriginDirection.y);
	cout << "Created ball !!!" << endl;
}

CanonBall::~CanonBall()
{}

void CanonBall::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}