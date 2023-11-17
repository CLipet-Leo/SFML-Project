#pragma once

#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(float x, float y, sf::Color color, float width, float height);
	~Brick();

	void OnCollisionEnter(std::string oFace) override;
	void OnCollisionStay() override;
	void OnCollisionExit() override;

};

