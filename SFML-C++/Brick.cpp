#include "header/Brick.h"
#include "header/GameObject.h"
#include <iostream>

using namespace std;

Brick::Brick(float x, float y, sf::Color color, float width, float height)
	: GameObject(x, y, color, width, height)
{
	cout << "Created !!!" << endl;

}


Brick::~Brick()
{}

void GameObject::OnCollisionEnter(float depthX, float depthY)
{
	~Brick();
}

void GameObject::OnCollisionStay()
{

}

void GameObject::OnCollisionExit()
{

}