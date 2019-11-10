#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Enemy
{
public:
	
	Enemy();
	
	
	//=========================
	//          BOSS 1
	//=========================
	Texture alicetexture;
	Sprite alice;
	int alicef = 0;  //ANIMATION FRAMES
	float aliceX, aliceY; //SPRITE DIVIDE
	float aliceS = 1; //ALICE SPEED
	float alicehp = 15; //ALICE HP
	RectangleShape trackalice;

	//==========================
	//          BOSS 2
	//==========================
	Texture doomtexture;
	Sprite doom;
	int doomf = 0;
	float doomX, doomY;
	float doomS = 1;
	float doomhp = 15;
	RectangleShape trackdoom;

	//==========================
	//        CLOSE Enemy
	//==========================
	Texture closetexture;
	Sprite closeenemy;
	int closef = 0;
	float closeX, closeY;
	float closeS = 1;
	float closehp = 10;
	RectangleShape trackclose;

	//==========================
	//       LONG ENEMY
	//==========================
	Texture longtexture;
	Sprite longenemy;
	int longf = 0;
	float longX, longY;
	float longS = 1;
	float longhp = 5;
	RectangleShape tracklong;

	//ANIMATION STUFF	
	int direction;
	int changeDirectionTime = 0;
	int ftime = 0;

	//SET ALIVE
	bool alive = true;

	int generateRandom(int max); 

	void initalice();
	void initdoom();
	void initclose();
	void initlong();

	void movement();
	void alicemovement();
	void doommovement();
	void closemovement();
	void longmovement();
};

