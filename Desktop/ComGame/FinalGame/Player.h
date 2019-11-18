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
	Texture guitar;
	Sprite gun;

	int gunX, gunY;
	Sprite Tom;
	Texture tomtexture;
	float tomspeed = 5;
	int tommaxhp = 40;
	int tomhp = tommaxhp;
	int damage = 1;
	int tomSizeX;
	int tomSizeY;
	int ftime;
	
	RectangleShape track;
	int direction = 2;
	void updateTom();
	void update();

private:
	int animationFrame = 0;
};

