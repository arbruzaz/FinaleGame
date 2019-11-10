#pragma once
#include<SFML/Graphics.hpp>
#include "Enemy.h"
using namespace sf;
class Player
{
public:
	Player();
	
	
	//Player 1 = TOM, 2 = ??, 3 = ??
	
	//Player 1
	Sprite Tom;
	Texture tomtexture;
	float tomspeed;
	int tomhp;
	int tomSizeX;
	int tomSizeY;
	
	RectangleShape track;
	int direction = 2;
	void updateTom();
	void update();


private:
	int animationFrame = 0;
};

