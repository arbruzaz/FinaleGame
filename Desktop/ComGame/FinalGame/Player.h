#pragma once
#include<SFML/Graphics.hpp>
#include "Enemy.h"
using namespace sf;
class Player
{
public:
	Player();
	Sprite Tom;
	Texture tomtexture;
	RectangleShape track;
	int direction = 2;
	void update();

private:
	int animationFrame = 0;
};

