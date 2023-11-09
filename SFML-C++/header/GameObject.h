#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::Vector2f pos;
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* shape = NULL; 
	sf::Vector2f speedVect;
	int dirX = 1, dirY = 1;
	float radius;
	float rot = 0;
	float x, y;
	float width, height;


	GameObject(float x, float y, sf::Color color, float r);

	GameObject(float x, float y, sf::Color color, float w, float h);

	~GameObject();

	void Draw(sf::RenderWindow& window);

	void Move(float dt);

	void Rotate(float dt);
	
	bool Collision(GameObject block);

	void DVDMove(sf::String side);

};

