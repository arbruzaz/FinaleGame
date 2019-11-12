#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
class EnemiesBullet
{
public:
	EnemiesBullet();

	//Direction 1 = UP , 2 = DOWN , 3 = LEFT , 4 = RIGHT
	int bulletdirection = 0;
	int ftime = 0;
	int bullettime = 0;

	Sprite alicebullet;
	int bsalice = 5;
	int aliceR = 700;
	int aliceD = 10;
	float aliceX, aliceY;
	int alicef = 0;
	
	Sprite doombullet;
	int bsdoom = 5;
	int doomR = 800;
	int doomD = 10;
	float doomX, doomY;
	int doomf = 0;

	Sprite billbullet;
	int bsbill = 5;
	int billR = 900;
	int billD = 10;
	float billX, billY;
	int billf = 0;


	Sprite longbullet;
	int bslong = 5;
	int longR = 350;
	int longD = 10;
	float longX, longY;
	int longf = 0;

	void updateBalice();
	void updateBdoom();
	void updateBbill();
	
	void updateBlong();
};

