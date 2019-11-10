#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"



using namespace sf;
class Game
{
public:

	

	Event ev;
	RenderWindow window;
	View view;
	//Class Called
	Player player;
	Enemy enemy;
	Bullet bullet;
	Map map;

	//Objects
	std::vector<Bullet> bullets;
	Texture bulletTexture;

	std::vector<Enemy> enemiesalice;
	std::vector<Enemy> enemiesdoom;
	std::vector<Enemy> enemiesclose;
	std::vector<Enemy> enemieslong;
	
	//ENEMIES TEXTURE
	

	//Variables
	bool firehold = false;
	int currentenemiestime = 300; //For SPAWN ENEMY
	int enemyrandom;  //For random Normal Enemy
	
	int maxalice = 3;
	int maxdoom = 2;
	
	int countnormalenemy = 0; //Check amout normal enemy
	int maxenemies = 15; //MAX NORMAL ENEMIES
	
	int spawntimes = 100; //MAXSPAWNTIME ENEMY
	
	int generateRandom(int max);

	int posPX; //Check Collision QD
	int posPY;


	//Game Window Running
	void run();
	
	//Functions
	
	//===============UPDATE=================

	//Enemies Update
	//ENEMIES SPAWN AND MOVEMENT
	void spawnalice(); //Pushback ALICE
	void spawndoom(); //PUSHBACK DOOM
	void spawnsmallenemy(); //SPAWN NORMAL ENEMIES

	void updateEnemies(); //Enemies Movement
	void updatealice(); //UPDATE AND SPAWN ALICE
	void updatedoom(); //UPDATE AND SPAWN DOOM
	void updatesmallenemy(); //UPDATE NORMAL ENEMY MOVEMENT
	


	//Bullets Update
	//BULLET HIT OBJECTS
	void updatebullet(); //bullet movement
	void firebullet(); //Keypressed fire
	void bullethit(); //Check bullet hit
	void bullethitalice(); //BULLET HIT ALICE
	void bullethitdoom();  //BULLET HIT DOOM
	void bullethitclose();  //BULLET HIT CLOSE
	void bullethitlong();  //BULLET HIT LONG
	


	//Collision!!!!!!

	//PLAYER
	void playerhitenemy(); //Check player collide with enemies
	void playerhitalice(); //CHECK PLAYER COLLIDE WITH ALICE
	void playerhitdoom(); //CHECK PLAYER COLLIDE WITH DOOM
	void playerhitclose(); //CHECK PLAYER COLLIDE WITH CLOSE
	void playerhitlong(); //CHECK PLAYER COLLIDE WITH LONG

	//FRAME
	void framebound(); //Game Frame Bound
	void playerhitframe(); //Player walk to frame

	//FRAME ENEMIES
	void enemieshitframe(); //Enemies walk to frame
	void alicehitfram(); //ALICE HIT FRAME 
	void doomhitframe(); //DOOM HIT FRAME
	void closehitframe(); //CLOSE HIT FRAME
	void longhitframe(); //LONG HIT FRAME

	//BULLET ENEMIES
	void bulletshitframe(); //Bullets firing to frame
	
	
	void update(); //Update Stuff

	//Render
	void renderenemies(); //render enemies
	void renderalice(); //RENDER ALICE
	void renderdoom(); //RENDER DOOM
	void renderclose(); //RENDER NORMAL ENEMIES
	void renderlong(); //RENDER NORMAL ENEMIES

	void renderbullets(); //render bullets
	void rendermap();
	void render(); //Render Objects
	

	Game();

	
};

