#include "player.h"

player::player(float posX, float posY) : posX(posX), posY(posY) 
{
}
player::player() : posX(0), posY(0)
{

}
sf::Vector2f player::getPosition()
{
	return sf::Vector2f(posX, posY);
}

void player::setPosition(float posX, float posY)
{
	this->posX = posX;
	this->posY = posY;

}
