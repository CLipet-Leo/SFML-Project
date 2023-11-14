#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::Shape* oShape = NULL; 
	sf::Vector2f speedVect;
	sf::Vector2f oDirection = { 0.f, 0.f };
	sf::Vector2f oOriginVect = { 0.f, 0.f };
	int dirX = 0, dirY = 1;
	float radius;
	float rot = 0;
	float width, height;
	sf::Color color;


	GameObject(float x, float y, sf::Color color, float r);

	GameObject(float x, float y, sf::Color color, float w, float h);

	~GameObject();

	void SetPosition(float fX = 0, float fY = 0, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void SetRotation(float fAngle, float fRatioX, float fRatioY);

	void SetOrigin(float fRatioX, float fRatioY);

	void SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void Draw(sf::RenderWindow& window);

	void SetDirection(float fX, float fY);

	void Move(float dt);

	void CheckCollisions(const GameObject& goOther);

	sf::Vector2f GetOriginRelativeToWindow();

	void DVDMove(sf::String side);

	void CheckCollision(GameObject& object);

	void ChangeDirection(sf::String collisionSide);

	const sf::Vector2f& GetPosition();

};

