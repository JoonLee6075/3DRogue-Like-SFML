#pragma once
#include <SFML/System.hpp>
class player
{

private:
	float posX;
	float posY;
public:
	player();
	player(float posX, float posY);
	sf::Vector2f getPosition();
	void setPosition(float posX, float posY);


};