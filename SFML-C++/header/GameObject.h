#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* oShape = NULL;
	sf::Vector2f oDirection = { 0.f, 0.f };
	float x, y, width, height, radius;
	sf::Color color;

	std::vector<GameObject*> inCollisionWith;

	//------------------------------------GAME OBJECT------------------------------------//
	GameObject(float x, float y, const sf::Color& color, float r);
	GameObject(float x, float y, const sf::Color& color, float w, float h);
	~GameObject();
  
	//------------------------------------SET ELEMENTS------------------------------------//
	void SetPosition(float fX = 0, float fY = 0, float fRatioX = 0.5f, float fRatioY = 0.5f);
	void SetRotation(float fAngle, float fRatioX, float fRatioY);
	void SetOrigin(float fRatioX, float fRatioY);
	void SetRotation(sf::Vector2i& oOrientationPosition, float fRatioX = 0.5f, float fRatioY = 0.5f);
	void SetDirection(float fX, float fY);

	//------------------------------------GET ELEMENTS------------------------------------//
	const sf::Vector2f& GetPosition(float fRatioX = 0.5f, float fRatioY = 0.5f);
	const sf::Vector2f GetDirection();
	const sf::Vector2f& GetOrigin();
	sf::Vector2f GetOriginRelativeToWindow();

	//---------------------------------------EVENT----------------------------------------//
	virtual void Draw(sf::RenderWindow& window);
	void Move(float dt);
	void CheckWindowCollision(const sf::RenderWindow& window);
	void CheckCollision(GameObject* object);
	virtual void OnCollisionEnter(float depthX, float depthY);
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

};

