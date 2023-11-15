#include "header/CanonBall.h"
#include "header/GameObject.h"

using namespace std;

CanonBall::CanonBall(float x, float y, sf::Color color, float radius)
	: GameObject(x, y, color, width, height)
{
	cout << "Created !!!" << endl;
}