#include "header/Canon.h"

using namespace sf;
using namespace std;

Canon::Canon(float screenWidth, float screenHeight)
	: GameObject(x, y, color, width, height)
{
	GameObject canon(.5f * screenWidth, .5f * screenHeight, Color::Green, 50.f, 100.f);
	

}

Canon::~Canon()
{}

void Canon::Rotate()
{

}

void Canon::shoot()
{
	GameObject ball(50.f , 50.f , Color::Green, 50.f);

}
