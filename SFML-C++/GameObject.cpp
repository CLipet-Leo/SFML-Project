#include "header/GameObject.h"
#include "header/GameManager.h"

#include <iostream>
#include <string>

using namespace std;
using namespace sf;

GameObject::GameObject(float x, float y, sf::Color color, float r)
	:x(x), y(y), radius(r)
{
	oCircle = new sf::CircleShape;
	oCircle->setRadius(r);
	oCircle->setPosition(x, y);
	oCircle->setFillColor(color);

	shape = oCircle;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
	:x(x), y(y), width(w), height(h)
{
	oRectangle = new sf::RectangleShape;
	oRectangle->setSize(sf::Vector2f(w, h));
	oRectangle->setPosition(x, y);
	oRectangle->setFillColor(color);

	shape = oRectangle;
}

GameObject::~GameObject() 
{}

//bool GameObject::Collision(GameObject object) {
//	const Vector2f position = shape->getPosition();
//	const Vector2f size = Vector2f(width, height);
//
//	return x < object.x + object.width && x + width > object.x && y < object.y + object.height && y + height > object.y;
//
//}

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(*shape);
}

void GameObject::DVDMove(sf::String windowSide) {
	//printf("bloup\n");
	if (windowSide == "up") {
		dirY = 1;
	}
	if (windowSide == "down") {
		dirY = -1;
	}
	if (windowSide == "left") {
		dirX = 1;
	}
	if (windowSide == "right") {
		dirX = -1;
	}
}

void GameObject::Move(float dt)
{
	pos = shape->getPosition();
	pos.x += (dirX * 100) * dt;
	pos.y += (dirY * 100) * dt;
	//printf("pos: %f, %f \n", pos.x, pos.y);
	shape->setPosition(pos);
}


void GameObject::Rotate(float dt)
{
	shape->setOrigin(width / 2, height / 2);
	rot = shape->getRotation();
	rot += 100 * dt;
	shape->setRotation(rot);
}


void GameObject::collision(GameObject& object) {
	// Most of this stuff would probably be good to keep stored inside the player
	// along side their x and y position. That way it doesn't have to be recalculated
	// every collision check
	float playerHalfW = this->width / 2;
	float playerHalfH = this->height / 2;
	float enemyHalfW = object.width / 2;
	float enemyHalfH = object.height / 2;
	float playerCenterX = this->x + this->width / 2;
	float playerCenterY = this->y + this->height / 2;
	float enemyCenterX = object.x + object.width / 2;
	float enemyCenterY = object.y + object.height / 2;

	// Calculate the distance between centers
	float diffX = playerCenterX - enemyCenterX;
	float diffY = playerCenterY - enemyCenterY;

	// Calculate the minimum distance to separate along X and Y
	float minXDist = playerHalfW + enemyHalfW;
	float minYDist = playerHalfH + enemyHalfH;

	// Calculate the depth of collision for both the X and Y axis
	float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
	float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

	// Now that you have the depth, you can pick the smaller depth and move
	// along that axis.
	if (depthX != 0 && depthY != 0) {
		if (abs(depthX) < abs(depthY)) {
			// Collision along the X axis. React accordingly
			if (depthX > 0) {
				printf("right collision\n");
				changeDirection("right");
			}
			else {
				printf("left collision\n");
				changeDirection("left");
			}
		}
		else {
			// Collision along the Y axis.
			if (depthY > 0) {
				printf("down collision\n");
				changeDirection("down");
			}
			else {
				printf("up collision\n");
				changeDirection("up");
			}
		}
	}

}

void GameObject::changeDirection(sf::String collisionSide) {
	if (collisionSide == "down")
	{
		printf("bloup down\n");
		dirY = 1;
	}if (collisionSide == "up")
	{
		printf("bloup up\n");
		dirY = -1;
	}if (collisionSide == "left")
	{
		printf("bloup left\n");
		dirX = -1;
	}if (collisionSide == "right")
	{
		printf("bloup right\n");
		dirX = 1;
	}
}