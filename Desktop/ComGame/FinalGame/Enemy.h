#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Enemy
{
public:
	
	Enemy();
	RectangleShape track;
	Texture alicetexture;
	Sprite alice;
	int alicef = 0;
	int aliceX, aliceY;
	int aliceS = 1;
	int direction;
	int changeDirectionTime = 0;

	int generateRandom(int max); 
	void movement();
};

