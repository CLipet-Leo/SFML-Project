#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(float x, float y, sf::Color color, float r);

	GameObject(float x, float y, sf::Color color, float w, float h);

	~GameObject();

	void Draw(sf::RenderWindow& window);

	void Update(float dt);

	void Rotate();

	void Move(int dir, int speed);

protected:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* shape;
	float x, y;
};

