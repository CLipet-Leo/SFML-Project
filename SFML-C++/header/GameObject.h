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

	void Move(float dt);

	void Rotate(float dt);

protected:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* shape = NULL; 
	sf::Vector2f pos = {0.f, 0.f};
	float x, y, width, height, radius;
	sf::Color color;
	float rot = 0;
};

