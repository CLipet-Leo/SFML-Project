#include "header/GameObject.h"
#include "header/GameManager.h"

#include "header/Math.h"

#include <iostream>
#include <string>

//using namespace sf;
using namespace std;

GameObject::GameObject(float x, float y, sf::Color color, float r)
	: radius(r)
{
	sf::CircleShape* oCircle = new sf::CircleShape;
	oCircle->setRadius(radius);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	oShape = oCircle;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
	: width(w), height(h)
{
	sf::RectangleShape* oRectangle = new sf::RectangleShape;
	oRectangle->setSize(sf::Vector2f(w, h));

	oRectangle->setFillColor(color);

	oShape = oRectangle;

	SetPosition(x, y);
}

GameObject::~GameObject() 
{
	delete oShape;
}

void GameObject::SetPosition(float fX, float fY, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setPosition(fX, fY);
}

void GameObject::SetRotation(float fAngle, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setRotation(fAngle);
}

void GameObject::SetOrigin(float fRatioX, float fRatioY)
{
	float fOriginX = fRatioX * width;
	float fOriginY = fRatioY * height;

	oShape->setOrigin(fOriginX, fOriginY);
}

void GameObject::SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();
	sf::Vector2f fOrientationPosition = { static_cast<float>(oOrientationPosition.x + (width / 2)), static_cast<float>(oOrientationPosition.y) };

	float fAngleDegree = Math::VectorToAngle(fOrientationPosition, oOriginPositionInWindow);

	SetRotation(fAngleDegree, fRatioX, fRatioY);
}

void GameObject::SetDirection(float fX, float fY)
{
	sf::Vector2f speedVect = { fX , fY };
	oDirection = Math::NormalizedVector(speedVect);
	cout << "Direction : " << speedVect.x << "," << speedVect.y << endl;
}

//bool GameObject::Collision(GameObject object) {
//	const Vector2f position = shape->getPosition();
//	const Vector2f size = Vector2f(width, height);
//
//	return x < object.x + object.width && x + width > object.x && y < object.y + object.height && y + height > object.y;
//
//}

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}

void GameObject::DVDMove(sf::String windowSide) {
	//printf("bloup\n");
	if (windowSide == "up") {
		dirY = 1;
	}
	if (windowSide == "down") {
		dirY = -1;
	}
	if (windowSide == "left") {
		dirX = 1;
	}
	if (windowSide == "right") {
		dirX = -1;
	}
}

void GameObject::Move(float fDeltaTime)
{
	oOriginVect = oShape->getPosition();
	oOriginVect.x += (oDirection.x * 100) * fDeltaTime;
	oOriginVect.y += (oDirection.y * 100) * fDeltaTime;
	cout << "Nouvelle pos : " << oOriginVect.x << "," << oOriginVect.y << std::endl;
	SetPosition(oOriginVect.x, oOriginVect.y);
}


void GameObject::CheckCollision(GameObject& object) {
	// Most of this stuff would probably be good to keep stored inside the player
	// along side their x and y position. That way it doesn't have to be recalculated
	// every collision check
	float playerHalfW = this->width / 2;
	float playerHalfH = this->height / 2;
	float enemyHalfW = object.width / 2;
	float enemyHalfH = object.height / 2;
	float playerCenterX = this->x + this->width / 2;
	float playerCenterY = this->y + this->height / 2;
	float enemyCenterX = object.x + object.width / 2;
	float enemyCenterY = object.y + object.height / 2;

	// Calculate the distance between centers
	float diffX = playerCenterX - enemyCenterX;
	float diffY = playerCenterY - enemyCenterY;

	// Calculate the minimum distance to separate along X and Y
	float minXDist = playerHalfW + enemyHalfW;
	float minYDist = playerHalfH + enemyHalfH;

	// Calculate the depth of collision for both the X and Y axis
	float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
	float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

	// Now that you have the depth, you can pick the smaller depth and move
	// along that axis.
	if (depthX != 0 && depthY != 0) {
		if (abs(depthX) < abs(depthY)) {
			// Collision along the X axis. React accordingly
			if (depthX > 0) {
				printf("right collision\n");
				ChangeDirection("right");
			}
			else {
				printf("left collision\n");
				ChangeDirection("left");
			}
		}
		else {
			// Collision along the Y axis.
			if (depthY > 0) {
				printf("down collision\n");
				ChangeDirection("down");
			}
			else {
				printf("up collision\n");
				ChangeDirection("up");
			}
		}
	}

}

void GameObject::ChangeDirection(sf::String collisionSide) {
	if (collisionSide == "down")
	{
		printf("bloup down\n");
		dirY = 1;
	}if (collisionSide == "up")
	{
		printf("bloup up\n");
		dirY = -1;
	}if (collisionSide == "left")
	{
		printf("bloup left\n");
		dirX = -1;
	}if (collisionSide == "right")
	{
		printf("bloup right\n");
		dirX = 1;
	}
}

const sf::Vector2f& GameObject::GetPosition()
{
	return oShape->getPosition();
}

sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	//oShape->setOrigin(width / 2, height);
	sf::Vector2f oWindowPosition = oShape->getPosition();
	sf::Vector2f oOriginPosition = oShape->getOrigin();

	return oWindowPosition + oOriginPosition;
}