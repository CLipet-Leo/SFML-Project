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

	bool Collision(GameObject block);

protected:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* shape; 
	sf::Vector2f pos;
	float x, y;
	float width, height;
	float radius;
	float rot = 0;
};

