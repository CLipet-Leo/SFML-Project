#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* shape = NULL;
	sf::Vector2f cOrigin;
	float angleDegrees;
	sf::Vector2f pos = { 0.f, 0.f };
	float x, y, width, height, radius;
	sf::Color color;
	float rot = 0;

	GameObject(float x, float y, const sf::Color& color, float r);

	GameObject(float x, float y, const sf::Color& color, float w, float h);

	~GameObject();

	void SetPosition(float fX, float fY, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void SetRotation(float fAngle, float fRatioX = 0.5f, float fRatioY = 0.5f);

	void Draw(sf::RenderWindow& window);

	void SetDirection(float fX, float fY);

	void Move(float dt);

	void CheckCollisions(const GameObject& goOther);

	void Rotate(const sf::Vector2i& mPos);
	
	sf::Vector2f GetOriginRelativeToWindow();

protected:
};

