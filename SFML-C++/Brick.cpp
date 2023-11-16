#include "header/Brick.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "header/GameObject.h"

using namespace std;

Brick::Brick(float x, float y, sf::Color color, float width, float height)
	: GameObject(x, y, color, width, height)
{
	cout << "Created !!!" << endl;

}


Brick::~Brick()
{}

void Brick::OnCollisionEnter(float depthX, float depthY)
{
	//~Brick();
}

void Brick::OnCollisionStay()
{

}

void Brick::OnCollisionExit()
{

}