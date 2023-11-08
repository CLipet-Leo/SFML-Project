#include "header/Canon.h"

using namespace sf;
using namespace std;

Canon::Canon(float screenWidth, float screenHeight)
{
	GameObject canon(.5f * screenWidth, .5f * screenHeight, Color::Green, 50.f, 100.f);


}

Canon::~Canon()
{

}

void Canon::shoot()
{

}
