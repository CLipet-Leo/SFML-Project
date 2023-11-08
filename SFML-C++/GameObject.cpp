#include "header/GameObject.h"
#include "header/GameManager.h"

#include <iostream>
#include <string>

using namespace std;
using namespace sf;

GameObject::GameObject(float x, float y, Color color, float r)
	:x(x), y(y)
{
	oCircle = new CircleShape;
	oCircle->setRadius(r);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	shape = oCircle;
}

GameObject::GameObject(float x, float y, Color color, float w, float h)
	:x(x), y(y), width(w), height(h)
{
	oRectangle = new RectangleShape;
	oRectangle->setSize(Vector2f(w, h));
	oRectangle->setPosition(x, y);
	oRectangle->setFillColor(color);

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
	sf::Vector2f pos = shape->getPosition();
	pos.x += 100 * dt;
	pos.y += 50 * dt;
	shape->setPosition(pos);
}


void GameObject::Rotate(float dt)
{
	shape->setOrigin(width / 2, height / 2);
	rot = shape->getRotation();
	rot += 100 * dt;
	shape->setRotation(rot);
}