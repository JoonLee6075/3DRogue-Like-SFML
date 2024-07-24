#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "player.h"

class Game
{
public:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Clock clock;
	sf::Vector2i playerPosition;

	//none sf stuff

	static char map[25][31];

	float mapPos[2] = { 600, 400 };
	float mapDisp[2] = { 0,0 };
	float viewOffsetY = 0.0f;
	float viewOffsetX = 0.0f;
	const float VIEW_MOVE_SPEED = 2.0f;
	const float MAX_VIEW_OFFSET = 100.0f;
	int playerLocation[2] = { 12,15 };
	char behindPlayer = '.';
	bool endGame;
	bool moving = false;
	int repeatCounter = 0;

	player p;
	Game();
	~Game();

	void initWindow();
	void initVariables();

	bool running() const;
	bool getEndGame() const;

	void update();
	void render();

	void pollEvents();

};

