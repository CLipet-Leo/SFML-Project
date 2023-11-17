#include "header/GameObject.h"

#include <iostream>

#include "header/Math.h"
#include "header/CanonBall.h"

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

	sf::Vector2f oVectDirection = Math::DirectionBetweenPoints(oOriginPositionInWindow, fOrientationPosition);
	SetDirection(oVectDirection.x, oVectDirection.y);

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

	oPosition = GetPosition();
	oPosition.x += (oDirection.x * 100) * fDeltaTime;
	oPosition.y += (oDirection.y * 100) * fDeltaTime;
	//cout << "Nouvelle pos : " << oOriginVect.x << "," << oOriginVect.y << std::endl;
	SetPosition(oPosition.x, oPosition.y);
}

//--------------------------------------------------------------CHECK COLLISION-----------------------------------------------------------------//
void GameObject::CheckWindowCollision(const sf::RenderWindow& window) {
	sf::Vector2f position = GetPosition();

	// Récupère les dimensions de la fenêtre
	float windowWidth = static_cast<float>(window.getSize().x);
	float windowHeight = static_cast<float>(window.getSize().y);

	// Vérifie la collision avec les bords de la fenêtre
	if (position.x < 0) {
		OnCollisionEnter("gauche"); // Collision détectée, appelle la fonction d'entrée en collision
	}
	else if (position.x > windowWidth) {
		OnCollisionEnter("droite"); // Collision détectée, appelle la fonction d'entrée en collision
	}
	else if (position.y < 0) {
		OnCollisionEnter("haut"); // Collision détectée, appelle la fonction d'entrée en collision
	}
	else if (position.y > windowHeight) {
		OnCollisionEnter("bas"); // Collision détectée, appelle la fonction d'entrée en collision
	}
	else {
		OnCollisionExit(); // Pas de collision, appelle la fonction de sortie de collision
	}
}

void GameObject::CheckCollisions(const GameObject& goOther) {
	// Vérification de la collision AABB
	sf::Vector2f positionVectW = GetPosition();
	sf::Vector2f positionVectB = goOther.oPosition;
	// Calcul des coordonnées des bords du rectangle actuel
	float thisLeft = positionVectW.x - (width / 2);
	float thisRight = positionVectW.x + (width / 2);
	float thisTop = positionVectW.y - (height / 2);
	float thisBottom = positionVectW.y + (height / 2);

	// Calcul des coordonnées des bords du rectangle 'other'
	float otherLeft = positionVectB.x - (goOther.width / 2);
	float otherRight = positionVectB.x + (goOther.width / 2);
	float otherTop = positionVectB.y - (goOther.height / 2);
	float otherBottom = positionVectB.y + (goOther.height / 2);

	// Vérifie s'il y a collision
	bool collisionX = thisRight >= otherLeft && thisLeft <= otherRight;
	bool collisionY = thisBottom >= otherTop && thisTop <= otherBottom;


	if (collisionX || collisionY) {
		std::string face;
		// Vérifie la face de collision de la AABB
		if (collisionX && thisRight >= otherLeft)
		{
			face = "droite";
		}
		else if (collisionX && thisLeft <= otherRight)
		{
			face = "gauche";
		}
		if (collisionY && thisBottom >= otherTop)
		{
			face = "bas";
		}
		else if (collisionY && thisTop <= otherBottom)
		{
			face = "haut";
		}

		// Appel de méthodes virtuelles selon l'état de la collision précédente
		if (!wasCollidingLastFrame) {
			OnCollisionEnter(face);
		}
		else {
			OnCollisionStay();
		}

		wasCollidingLastFrame = true; // Indique la collision actuelle pour le prochain tour de boucle
	}
	else {
		// Appel de la méthode virtuelle de sortie de collision s'il y avait collision précédemment
		if (wasCollidingLastFrame) {
			OnCollisionExit();
		}

		wasCollidingLastFrame = false; // Indique qu'il n'y a pas de collision pour le prochain tour de boucle
	}
}

//--------------------------------------------------------------ON COLLISION ENTER--------------------------------------------------------------//
void GameObject::OnCollisionEnter(std::string oFace)
{}

//--------------------------------------------------------------ON COLLISION STAY---------------------------------------------------------------//
void GameObject::OnCollisionStay()
{}

//--------------------------------------------------------------ON COLLISION EXIT---------------------------------------------------------------//
void GameObject::OnCollisionExit()
{}
