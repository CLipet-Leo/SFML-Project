#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "header/GameManager.h"
#include "header/Math.h"

class GameObject
{
public:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* oShape = NULL;
	sf::Vector2f oDirection = { 0.f, 0.f };
	sf::Vector2f oVect = { 0.f, 0.f };
	float x, y, width, height, radius;
	sf::Color color;
	float rot = 0;

	GameObject(float x, float y, const sf::Color& color, float r);

	GameObject(float x, float y, const sf::Color& color = sf::Color::White, float w = 50.f, float h = 50.f);

	~GameObject();

	void SetPosition(float fX = 0, float fY = 0, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void SetRotation(float fAngle, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void Draw(sf::RenderWindow& window);

	void SetDirection(float fX, float fY);

	void Move(float dt);

	void CheckCollisions(const GameObject& goOther);

	void Rotate(sf::Vector2i& mPos);
	
	sf::Vector2f GetOriginRelativeToWindow();

protected:
};

