#include "header/GameObject.h"

using namespace std;

GameObject::GameObject(float x, float y, const sf::Color& color, float r)
	:x(x), y(y), color(color), radius(r)
{
	oCircle = new sf::CircleShape;
	oCircle->setRadius(radius);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	oShape = oCircle;
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

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(*oShape);
}

void GameObject::SetDirection(float fX, float fY)
{
	sf::Vector2f speedVect = { fX , fY };
	oDirection = Math::NormalizedVector(speedVect);
	cout << "Direction : " << speedVect.x << "," << speedVect.y << endl;
}

void GameObject::Move(float fDeltaTime)
{
	oOriginVect = oShape->getPosition();
	oOriginVect.x += (oDirection.x * 100) * fDeltaTime;
	oOriginVect.y += (oDirection.y * 100) * fDeltaTime;
	cout << "Nouvelle pos : " << oOriginVect.x << "," << oOriginVect.y << std::endl;
	SetPosition(oOriginVect.x, oOriginVect.y);
}

void GameObject::CheckCollisions(const GameObject& goOther)
{

}

sf::Vector2f GameObject::GetOriginRelativeToWindow()
{
	//oShape->setOrigin(width / 2, height);
	sf::Vector2f oWindowPosition = oShape->getPosition();
	sf::Vector2f oOriginPosition = oShape->getOrigin();

	return oWindowPosition + oOriginPosition;
}