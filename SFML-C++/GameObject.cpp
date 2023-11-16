#include "header/GameObject.h"

#include "header/Math.h"

#include "header/Math.h"

#include <iostream>
#include "header/CanonBall.h"

//using namespace sf;
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                  GAME OBJECT                                                                 //
//----------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------GAME OBJECT CIRCLE--------------------------------------------------------------//
GameObject::GameObject(float x, float y, const sf::Color& color, float r)
	:x(x), y(y), color(color), radius(r)
{
	oCircle = new sf::CircleShape;

	oCircle->setRadius(radius);
	oCircle->setFillColor(color);

	oShape = oCircle;

	SetPosition(x, y);
}

GameObject::GameObject(float x, float y, const sf::Color& color, float w, float h)
	:x(x), y(y), color(color), width(w), height(h)
{
	oRectangle = new sf::RectangleShape;
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

//--------------------------------------------------------------GET DIRECTION--------------------------------------------------------------------//
const sf::Vector2f GameObject::GetDirection()
{
	return oDirection;
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
	oPosition.x += (oDirection.x * 200) * fDeltaTime;
	oPosition.y += (oDirection.y * 200) * fDeltaTime;
	//cout << "Nouvelle pos : " << oOriginVect.x << "," << oOriginVect.y << std::endl;
	SetPosition(oPosition.x, oPosition.y);
}

//--------------------------------------------------------------CHECK COLLISION-----------------------------------------------------------------//
void GameObject::CheckCollision(GameObject* object) {
	// Most of this stuff would probably be good to keep stored inside the player
	// along side their x and y position. That way it doesn't have to be recalculated
	// every collision check
	printf("bloup\n");
	float objectWhoCollisionHalfW = this->width / 2;
	float objectWhoCollisionHalfH = this->height / 2;
	float objectBeCollisionedHalfW = object->width / 2;
	float objectBeCollisionedHalfH = object->height / 2;
	sf::Vector2f positionVectW = GetPosition();
	sf::Vector2f positionVectB = object->GetPosition();
	float objectWhoCollisionCenterX = positionVectW.x;
	float objectWhoCollisionCenterY = positionVectW.y;
	float objectBeCollisionedCenterX = positionVectB.x;
	float objectBeCollisionedCenterY = positionVectB.y;

	// Calculate the distance between centers
	float diffX = objectBeCollisionedCenterX - objectWhoCollisionCenterX;
	float diffY = objectBeCollisionedCenterY - objectWhoCollisionCenterY;
	//cout << "diff: " << diffX << "||" << diffY << endl;

	// Calculate the minimum distance to separate along X and Y
	float minXDist = objectWhoCollisionHalfW + objectBeCollisionedHalfW;
	float minYDist = objectWhoCollisionHalfH + objectBeCollisionedHalfH;
	//cout << "min: " << minXDist << "||" << minYDist << endl;

	// Calculate the depth of collision for both the X and Y axis
	float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
	float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;
	//cout << "depth: " << depthX << "||" << depthY << endl;

	// Now that you have the depth, you can pick the smaller depth and move
	// along that axis.

	bool IsCollidingX = objectWhoCollisionCenterX < objectBeCollisionedCenterX + object->width && objectWhoCollisionCenterX + this->width > objectBeCollisionedCenterX;
    bool IsCollidingY = objectWhoCollisionCenterY < objectBeCollisionedCenterY + object->height && objectWhoCollisionCenterY + this->height > objectBeCollisionedCenterY;

	bool isInCollision = IsCollidingX && IsCollidingY;
	auto it = std::find(inCollisionWith.begin(), inCollisionWith.end(), object);
	bool isAlreadyInCollision = it != inCollisionWith.end();

	cout << isAlreadyInCollision << "||" << isInCollision << endl;


	if (isInCollision)
	{
		if (isAlreadyInCollision)
		{
			printf("enter the stay\n");
			OnCollisionStay();
		}
		else
		{
			printf("enter the enter\n");
			inCollisionWith.push_back(object);	
			OnCollisionEnter(depthX, depthY);
		}
	}
	else
	{
		if (isAlreadyInCollision)
		{
			printf("enter the exit\n");
			OnCollisionExit();
			std::remove(inCollisionWith.begin(), inCollisionWith.end(), object);
		}
	}

}

//--------------------------------------------------------------ON COLLISION ENTER--------------------------------------------------------------//
void GameObject::OnCollisionEnter(float depthX, float depthY)
{
  
}

//--------------------------------------------------------------ON COLLISION STAY---------------------------------------------------------------//
void GameObject::OnCollisionStay()
{

}

//--------------------------------------------------------------ON COLLISION EXIT---------------------------------------------------------------//
void GameObject::OnCollisionExit()
{

}
