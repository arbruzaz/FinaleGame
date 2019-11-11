#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
class EnemiesBullet
{
public:
	EnemiesBullet();

	//Direction 1 = UP , 2 = DOWN , 3 = LEFT , 4 = RIGHT
	int direction = 0;

	Sprite alicebullet;
	int bsalice = 5;
	int aliceR = 700;
	int aliceD = 10;
	
	Sprite doombullet;
	int bsdoom = 5;
	int doomR = 800;
	int doomD = 10;

	Sprite billbullet;
	int bsbill = 5;
	int billR = 900;
	int billD = 10;

	Sprite closebullet;
	int bsclose = 5;
	int closeR = 150;
	int closeD = 100;

	Sprite longbullet;
	int bslong = 5;
	int longR = 350;
	int longD = 10;
	
	void updateBalice();
	void updateBdoom();
	void updateBbill();
	void updateBclose();
	void updateBlong();
};

