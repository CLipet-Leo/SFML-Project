#include "header/GameObject.h"
#include "header/GameManager.h"

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace sf;

GameObject::GameObject(float x, float y, const Color& color, float r)
	:x(x), y(y), color(color), radius(r)
{
	oCircle = new CircleShape;
	oCircle->setRadius(radius);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	shape = oCircle;
}

GameObject::GameObject(float x, float y, const Color& color, float w, float h)
	:x(x), y(y), color(color), width(w), height(h)
{
	oRectangle = new RectangleShape;
	oRectangle->setSize(Vector2f(w, h));
	oRectangle->setPosition(x, y);
	oRectangle->setFillColor(color);
	oRectangle->setOrigin(width / 2, height);

	shape = oRectangle;
}

GameObject::~GameObject() 
{}

void GameObject::Draw(RenderWindow& window)
{
	window.draw(*shape);
}

void GameObject::Move(float dt)
{
	pos = shape->getPosition();
	pos.x += 100 * dt;
	pos.y += 100 * dt;
	shape->setPosition(pos);
}

float GetMagnitude(const sf::Vector2f& oVector)
{
	return sqrt((oVector.x * oVector.x) + (oVector.y * oVector.y));
}

void GameObject::Rotate(float dt, const Vector2i& oOrientationPosition)
{
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();

	cout << "L'origin du rect est : " << oOriginPositionInWindow.x << "," << oOriginPositionInWindow.y << endl;
	// Calcul du vecteur entre les deux points
	
	float fAdjacent = (oOrientationPosition.x + 15.f) - oOriginPositionInWindow.x;
	float fOpposit = oOrientationPosition.y - oOriginPositionInWindow.y;

	// Calcul de l'angle en radians
	float fAngleRadian = atan2(fOpposit, fAdjacent);
	float fAngleDegree = fAngleRadian * 180 / (atan(1) * 4);

	std::cout << fAngleDegree + 90 << std::endl;

	shape->setRotation(fAngleDegree + 90 );
}

sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	sf::Vector2f oWindowPosition = shape->getPosition();
	sf::Vector2f oOriginPosition = shape->getOrigin();

	return oWindowPosition + oOriginPosition;
}