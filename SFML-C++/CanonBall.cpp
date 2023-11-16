#include "header/CanonBall.h"
#include "header/GameObject.h"
#include "header/Math.h"

using namespace std;

CanonBall::CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection)
	: GameObject(x, y, color, radius)
{
	this->oShape = oShape;

	SetDirection(oOriginDirection.x, oOriginDirection.y);
	cout << "Created ball !!!" << endl;
}

void CanonBall::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}