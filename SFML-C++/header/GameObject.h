#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	sf::CircleShape* oCircle = NULL;
	sf::RectangleShape* oRectangle = NULL;
	sf::Shape* oShape = NULL;
	sf::Vector2f oDirection = { 0.f, 0.f };
	sf::Vector2f oOriginVect = { 0.f, 0.f };
	float x, y, width, height, radius;
	sf::Color color;

	std::vector<GameObject*> inCollisionWith;

	GameObject(float x, float y, const sf::Color& color, float r);

	GameObject(float x, float y, const sf::Color& color, float w, float h);

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
	const sf::Vector2f GetDirection();

	//---------------------------------------EVENT----------------------------------------//
	void Draw(sf::RenderWindow& window);
	void Move(float dt);
	void CheckCollision(GameObject* object);
	virtual void OnCollisionEnter(float depthX, float depthY);
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

};

