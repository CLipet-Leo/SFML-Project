#include "header/GameObject.h"
#include "header/GameManager.h"

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
	:x(x), y(y)
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

void GameObject::Update(float dt)
{
	
}


void GameObject::Rotate()
{
	shape->setOrigin(x, y);
	shape->setRotation(10);
}

void GameObject::Move(int dir, int speed)
{
	//int vectX = x * speed * dir;
	//int vectY = y * speed;

	shape->getPosition();

}