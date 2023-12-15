#include "header/Brick.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "header/GameObject.h"

using namespace std;

Brick::Brick(float x, float y, sf::Color color, float width, float height)
	: GameObject(x, y, color, width, height)
{	
	oShape = new sf::RectangleShape(sf::Vector2f(width, height));
	oShape->setFillColor(color);

	SetPosition(x, y); 
	cout << "Created !!!" << endl;
}


Brick::~Brick()
{
	delete oShape;
}

void Brick::OnCollisionEnter(std::string oFace)
{
	delete oShape;
}

void Brick::OnCollisionStay()
{

}

void Brick::OnCollisionExit()
{

}