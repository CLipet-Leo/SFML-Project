#include "header/Canon.h"

#include "header/GameObject.h"
#include "header/CanonBall.h"

#include <iostream>

using namespace std;


Canon::Canon(float x, float y, sf::Color color, float width, float height)
	: GameObject(x, y, color, width, height)
{
	cout << "Created !!!" << endl;

}

Canon::~Canon()
{}

void Canon::Shoot(std::vector<CanonBall*>& oBall)
{
	sf::Vector2f oOriginVect = GetPosition();
	cout << "Spawn d'une balle en : " << oOriginVect.x << ", " << oOriginVect.y << endl;
	sf::Vector2f oDirectionVect = GetDirection();

	oBall.push_back(new CanonBall(oOriginVect.x, oOriginVect.y, sf::Color::Red, 15.f, oDirectionVect));

}

void GameObject::OnCollisionEnter(float depthX, float depthY)
{
	if (abs(depthX) < abs(depthY))
	{
		// Collision along the X axis. React accordingly
		if (depthX > 0) {
			//go to right
			this->SetDirection(oDirection.x * (-1), oDirection.y);
		}
		else
		{
			//go to left
			this->SetDirection(oDirection.x * (-1), oDirection.y);
		}
	}
	else
	{
		// Collision along the Y axis.
		if (depthY > 0)
		{
			//go to down
			this->SetDirection(oDirection.x, oDirection.y * (-1));
		}
		else
		{
			//go to up
			this->SetDirection(oDirection.x, oDirection.y * (-1));
		}
	}
}

void GameObject::OnCollisionStay()
{

}

void GameObject::OnCollisionExit()
{

}