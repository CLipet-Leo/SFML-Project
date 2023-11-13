#include "header/GameObject.h"
#include "header/GameManager.h"
#include "header/Math.h"

#include <iostream>
#include <string>

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
{
	delete shape;
}

void GameObject::SetPosition(float fX, float fY, float fRatioX, float fRatioY)
{
	sf::Vector2f oOriginPosition = shape->getOrigin();
	sf::Vector2f oRatioPosition = { oOriginPosition.x * fRatioX, oOriginPosition.y * fRatioY };

	shape->setPosition(oRatioPosition.x + fX, oRatioPosition.y + fY);
}

void GameObject::SetRotation(float fAngle, float fRatioX, float fRatioY)
{

}

void GameObject::Draw(RenderWindow& window)
{
	window.draw(*shape);
}

void GameObject::SetDirection(float fX, float fY)
{

}

void GameObject::Move(float dt)
{
	pos = shape->getPosition();
	pos.x += 100 * dt;
	pos.y += 100 * dt;
	shape->setPosition(pos);
}

void GameObject::CheckCollisions(const GameObject& goOther)
{

}

void GameObject::Rotate(Vector2i& oOrientationPosition)
{
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();
	sf::Vector2f fOrientationPosition = { static_cast<float>(oOrientationPosition.x), static_cast<float>(oOrientationPosition.y) };

	float fAngleRadian = Math::fAngleRadiant(fOrientationPosition, oOriginPositionInWindow);

	float fAngleDegree = Math::fAngleDegrees(fAngleRadian);

	std::cout << fAngleDegree << std::endl;

	shape->setRotation(fAngleDegree);
}

sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	sf::Vector2f oWindowPosition = shape->getPosition();
	sf::Vector2f oOriginPosition = shape->getOrigin();

	return oWindowPosition + oOriginPosition;
}