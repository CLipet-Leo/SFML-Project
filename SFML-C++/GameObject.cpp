#include "header/GameObject.h"
#include "header/GameManager.h"

#include "header/Math.h"

#include <iostream>
#include <string>

//using namespace sf;
using namespace std;



//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                  GAME OBJECT                                                                 //
//----------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------GAME OBJECT CIRCLE--------------------------------------------------------------//
GameObject::GameObject(float x, float y, sf::Color color, float r)
	: radius(r)
{
	sf::CircleShape* oCircle = new sf::CircleShape;
	oCircle->setRadius(radius);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	oShape = oCircle;
}

//--------------------------------------------------------------GAME OBJECT RECTANGLE-----------------------------------------------------------//
GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
	: width(w), height(h)
{
	sf::RectangleShape* oRectangle = new sf::RectangleShape;
	oRectangle->setSize(sf::Vector2f(w, h));
	oRectangle->setFillColor(color);

	oShape = oRectangle;

	SetPosition(x, y);
}

//--------------------------------------------------------------GAME OBJECT DESTRUCTOR----------------------------------------------------------//
GameObject::~GameObject() 
{
	delete oShape;
}



//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                 SET ELEMENTS                                                                 //
//----------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------SET POSITION--------------------------------------------------------------------//
void GameObject::SetPosition(float fX, float fY, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setPosition(fX, fY);
}

//--------------------------------------------------------------SET ROTATION ANGLE--------------------------------------------------------------//
void GameObject::SetRotation(float fAngle, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);

	oShape->setRotation(fAngle);
}

//--------------------------------------------------------------SET ORIGIN----------------------------------------------------------------------//
void GameObject::SetOrigin(float fRatioX, float fRatioY)
{
	float fOriginX = fRatioX * width;
	float fOriginY = fRatioY * height;

	oShape->setOrigin(fOriginX, fOriginY);
}

//--------------------------------------------------------------SET ROTATION VECTOR-------------------------------------------------------------//
void GameObject::SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX, float fRatioY)
{
	SetOrigin(fRatioX, fRatioY);
	sf::Vector2f oOriginPositionInWindow = GetOriginRelativeToWindow();
	sf::Vector2f fOrientationPosition = { static_cast<float>(oOrientationPosition.x + (width / 2)), static_cast<float>(oOrientationPosition.y) };

	float fAngleDegree = Math::VectorToAngle(fOrientationPosition, oOriginPositionInWindow);

	SetRotation(fAngleDegree, fRatioX, fRatioY);
}

//--------------------------------------------------------------SET DIRECTION-------------------------------------------------------------------//
void GameObject::SetDirection(float fX, float fY)
{
	sf::Vector2f speedVect = { fX , fY };
	oDirection = Math::NormalizedVector(speedVect);
	//cout << "Direction : " << speedVect.x << "," << speedVect.y << endl;
}



//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                    EVENTS                                                                    //
//----------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------DRAW----------------------------------------------------------------------------//
void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}

//--------------------------------------------------------------MOVE----------------------------------------------------------------------------//
void GameObject::Move(float fDeltaTime)
{
	sf::Vector2f oPosition = GetPosition();
	oPosition.x += (oDirection.x * 100) * fDeltaTime;
	oPosition.y += (oDirection.y * 100) * fDeltaTime;
	//cout << "Nouvelle pos : " << oOriginVect.x << "," << oOriginVect.y << std::endl;
	SetPosition(oPosition.x, oPosition.y);
}

//--------------------------------------------------------------CHECK COLLISION-----------------------------------------------------------------//
void GameObject::CheckCollision(GameObject& object) {
	// Most of this stuff would probably be good to keep stored inside the player
	// along side their x and y position. That way it doesn't have to be recalculated
	// every collision check
	float objectWhoColisionHalfW = this->width / 2;
	float objectWhoColisionHalfH = this->height / 2;
	float objectBeCollisionedHalfW = object.width / 2;
	float objectBeCollisionedHalfH = object.height / 2;
	sf::Vector2f positionVectW = GetPosition();
	sf::Vector2f positionVectB = object.GetPosition();
	float objectWhoColisionCenterX = positionVectW.x;
	float objectWhoColisionCenterY = positionVectW.y;
	float objectBeCollisionedCenterX = positionVectB.x;
	float objectBeCollisionedCenterY = positionVectB.y;

	// Calculate the distance between centers
	float diffX = objectWhoColisionCenterX - objectBeCollisionedCenterX;
	float diffY = objectWhoColisionCenterY - objectBeCollisionedCenterY;
	printf("diffX: %f, diffY: %f\n", diffX, diffY);

	// Calculate the minimum distance to separate along X and Y
	float minXDist = objectWhoColisionHalfW + objectBeCollisionedHalfW;
	float minYDist = objectWhoColisionHalfH + objectBeCollisionedHalfH;
	printf("minXDist: %f, minYDist: %f\n", minXDist, minYDist);

	// Calculate the depth of collision for both the X and Y axis
	float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
	float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

	// Now that you have the depth, you can pick the smaller depth and move
	// along that axis.
	printf("depthX: %f, depthY: %f\n", depthX, depthY);
	if (depthX != 0 && depthY != 0) {
		if (abs(depthX) < abs(depthY)) {
			// Collision along the X axis. React accordingly
			if (depthX > 0) {
				//go to right
				this->SetDirection(1, 0);
			}
			else {
				//go to left
				this->SetDirection(-1, 0);
			}
		}
		else {
			// Collision along the Y axis.
			if (depthY > 0) {
				//go to down
				this->SetDirection(0, 1);
			}
			else {
				//go to up
				this->SetDirection(0, -1);
			}
		}
	}

}



//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                 GET ELEMENTS                                                                 //
//----------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------GET POSITION--------------------------------------------------------------------//
const sf::Vector2f& GameObject::GetPosition(float fRatioX, float fRatioY)
{
	sf::Vector2f oOrigin = oShape->getOrigin();
	sf::Vector2f oPosition = oShape->getPosition();

	oPosition.x -= oOrigin.x;
	oPosition.y -= oOrigin.y;

	oPosition.x += fRatioX * width;
	oPosition.y += fRatioY * height;

	return oPosition;
}

//--------------------------------------------------------------GET ORIGIN----------------------------------------------------------------------//
const sf::Vector2f& GameObject::GetOrigin()
{
	return oShape->getOrigin();
}

//--------------------------------------------------------------GET ORIGIN RELATIVE TO WINDOW---------------------------------------------------//
sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	//oShape->setOrigin(width / 2, height);
	sf::Vector2f oWindowPosition = oShape->getPosition();
	sf::Vector2f oOriginPosition = oShape->getOrigin();

	return oWindowPosition + oOriginPosition;
}


