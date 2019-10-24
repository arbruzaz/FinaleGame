#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"

using namespace sf;
class Game
{
public:
	Event ev;
	RenderWindow window;
	void run();
	void render();
	void update();
	Game();

	Player player;
	std::vector<Bullet> bullets;
	Texture bulletTexture;
	//Bullet bullet;
};

