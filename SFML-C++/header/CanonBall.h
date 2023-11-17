#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class CanonBall : public GameObject
{
public:
	sf::Vector2f oOriginDirection;

	CanonBall(float x, float y, sf::Color color, float radius, sf::Vector2f oOriginDirection);
	~CanonBall();
	
	void Draw(sf::RenderWindow& window);

	void OnCollisionEnter(std::string oFace) override;
	void OnCollisionStay() override;
	void OnCollisionExit() override;

};
