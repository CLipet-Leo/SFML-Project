#include "header/GameObject.h"
#include "header/GameManager.h"

#include <iostream>
#include <string>

using namespace std;
using namespace sf;

GameObject::GameObject(float x, float y, Color color, float r)
	:x(x), y(y), radius(r)
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

bool GameObject::Collision(GameObject object) {
	const Vector2f position = shape->getPosition();
	const Vector2f size = Vector2f(width, height);

	return x < object.x + object.width && x + width > object.x && y < object.y + object.height && y + height > object.y;

}

void GameObject::Draw(RenderWindow& window)
{
	window.draw(*shape);
}

void GameObject::DVDMove(String side) {
	//printf("bloup\n");
	if (side == "up") {
		dirY = 1;
	}
	if (side == "down") {
		dirY = -1;
	}
	if (side == "left") {
		dirX = 1;
	}
	if (side == "right") {
		dirX = -1;
	}
}

void GameObject::Move(float dt)
{
	pos = shape->getPosition();
	pos.x += (dirX * 100) * dt;
	pos.y += (dirY * 100) * dt;
	shape->setPosition(pos);
}


void GameObject::Rotate(float dt)
{
	shape->setOrigin(width / 2, height / 2);
	rot = shape->getRotation();
	rot += 100 * dt;
	shape->setRotation(rot);
}
