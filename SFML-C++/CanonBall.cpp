#include "header/CanonBall.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


CanonBall::CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection)
	: GameObject(x, y, color, width, height), oOriginDirection()
{
	oShape = new sf::CircleShape(radius);
	oShape->setFillColor(color);

	SetPosition(x, y);

	SetDirection(oOriginDirection.x, oOriginDirection.y);
	//cout << "Created ball !!!" << endl;
}

CanonBall::~CanonBall()
{}

void CanonBall::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}

void CanonBall::OnCollisionEnter(std::string oFace)
{
	if (oFace == "gauche")
	{
		cout << oFace << endl;
		SetDirection(oOriginDirection.x * (-1), oOriginDirection.y);
	}
	else if (oFace == "droite")
		SetDirection(oOriginDirection.x * (-1), oOriginDirection.y);
	else if (oFace == "bas")
		SetDirection(oOriginDirection.x, oOriginDirection.y * (-1));
	else if (oFace == "haut")
		SetDirection(oOriginDirection.x, oOriginDirection.y * (-1));
}

void CanonBall::OnCollisionStay() 
{
    
}

void CanonBall::OnCollisionExit() 
{
    
}