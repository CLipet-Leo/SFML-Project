#include "header/Canon.h"

#include "header/GameObject.h"
#include "header/CanonBall.h"

#include <iostream>

using namespace std;


Canon::Canon(float x, float y, sf::Color color, float width, float height)
	: GameObject(x, y, color, width, height)
{
	//cout << "Created !!!" << endl;
}

Canon::~Canon()
{}

void Canon::Shoot(std::vector<CanonBall*>& oBall)
{
	sf::Vector2f oOriginVect = GetPosition();
	sf::Vector2f oDirectionVect = GetDirection();
	//cout << "Spawn d'une balle en : " << oOriginVect.x << ", " << oOriginVect.y << endl;

	oBall.push_back(new CanonBall(oOriginVect.x, oOriginVect.y, sf::Color::Red, 15.f, oDirectionVect));

}
