#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Enemy
{
public:
	
	Enemy();
	Font font;

	Text aliceuihp;
	Text doomuihp;
	Text billuihp;
	Text closeuihp;
	Text longuihp;
	
	//=========================
	//          BOSS 1
	//=========================
	Texture alicetexture;
	Sprite alice;
	int alicef = 0;  //ANIMATION FRAMES
	float aliceX, aliceY; //SPRITE DIVIDE
	float aliceS = 3; //ALICE SPEED
	int alicehp = 30; //ALICE HP
	int maxalice = 30;
	int alicescore = 25;
	RectangleShape trackalice;

	//==========================
	//          BOSS 2
	//==========================
	Texture doomtexture;
	Sprite doom;
	int doomf = 0;
	float doomX, doomY;
	float doomS = 2;
	int doomhp = 50;
	int maxdoom = 50;
	int doomscore = 40;
	RectangleShape trackdoom;

	//==========================
	//           BOSS 3
	//==========================
	Texture billietexture;
	Sprite billie;
	int billief = 0;
	float billX, billY;
	float billS = 3;
	int billhp = 70;
	int maxbill = 70;
	int billscore = 100;
	RectangleShape trackbill;

	//==========================
	//        CLOSE Enemy
	//==========================
	Texture closetexture;
	Sprite closeenemy;
	int closef = 0;
	float closeX, closeY;
	float closeS = 3;
	int closehp = 10;
	int maxclose = 10;
	int closescore = 15;
	RectangleShape trackclose;

	//==========================
	//       LONG ENEMY
	//==========================
	Texture longtexture;
	Sprite longenemy;
	int longf = 0;
	float longX, longY;
	float longS = 1;
	int longhp = 5;
	int maxlong = 5;
	int longscore = 10;
	RectangleShape tracklong;

	//ANIMATION STUFF	
	int direction;
	int changeDirectionTime = 0;
	int ftime = 0;

	//SET ALIVE
	bool alive = true;
	bool follow = false;
	int amoutbullet = 0;

	int generateRandom(int max); 

	void initalice();
	void initdoom();
	void initclose();
	void initlong();
	void initbill();

	void movement();
	void alicemovement();
	void doommovement();
	void closemovement();
	void longmovement();
	void billmovement();

	
};

