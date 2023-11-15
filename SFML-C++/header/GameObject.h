#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::Shape* oShape = NULL; 
	sf::Vector2f speedVect;
	sf::Vector2f oDirection = { 0.f, 0.f };
	float radius;
	float rot = 0;
	float width, height;
	sf::Color color;

	//------------------------------------GAME OBJECT------------------------------------//
	GameObject(float x, float y, sf::Color color, float r);
	GameObject(float x, float y, sf::Color color, float w, float h);
	~GameObject();

	//------------------------------------SET ELEMENTS------------------------------------//
	void SetPosition(float fX = 0, float fY = 0, float fRatioX = 0.5f, float fRatioY = 0.5f);
	void SetRotation(float fAngle, float fRatioX, float fRatioY);
	void SetOrigin(float fRatioX, float fRatioY);
	void SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX = 0.5f, float fRatioY = 0.5f);
	void SetDirection(float fX, float fY);

	//------------------------------------GET ELEMENTS------------------------------------//
	sf::Vector2f GetOriginRelativeToWindow();
	const sf::Vector2f& GetOrigin();
	const sf::Vector2f& GetPosition(float fRatioX = 0.5f, float fRatioY = 0.5f);

	//---------------------------------------EVENT---------------------------------------//
	void Draw(sf::RenderWindow& window);
	void Move(float dt);
	void CheckCollision(GameObject& object);

};

