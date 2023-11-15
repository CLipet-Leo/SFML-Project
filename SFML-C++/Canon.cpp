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

void Canon::Shoot(sf::Vector2i& oOrientationPosition, std::vector<CanonBall>* oBall)
{
	oBall->push_back(CanonBall(oOrientationPosition.x, oOrientationPosition.y, sf::Color::Red, 30.f));

}
