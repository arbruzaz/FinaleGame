#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "EnemiesBullet.h"


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
	EnemiesBullet enemybullet;

	//Objects
	std::vector<Bullet> bullets;
	Texture bulletTexture;

	std::vector<Enemy> enemiesalice;
	std::vector<Enemy> enemiesdoom;
	std::vector<Enemy> enemiesbillie;
	std::vector<Enemy> enemiesclose;
	std::vector<Enemy> enemieslong;
	
	RectangleShape change;
	

	//Variables
	bool firehold = false;
	int currentenemiestime = 300; //For SPAWN ENEMY
	int enemyrandom;  //For random Normal Enemy
	
	int boss;    //CHECK BOSS SPAWN

	int nowalice = 0;
	int maxalice = 3;
	int killalice = 0;

	int nowdoom = 0;
	int maxdoom = 2;
	int killdoom = 0;

	int nowbillie = 0;
	int maxbillie = 1;
	int killbillie = 0;
	
	int killenemy; //Cout enemies killed 
	int maxenemies = 15; //MAX NORMAL ENEMIES
	
	int spawntimes = 100; //MAXSPAWNTIME ENEMY
	
	int stage = 3;   //STAGE GAME
	bool changestage = false;
	
	
	

	int generateRandom(int max);

	float posPX; //Check Collision QD
	float posPY;


	//Game Window Running
	void run();
	
	//Functions
	
	//===============UPDATE=================

	//STAGE UPDATE
	void stagechange();
	void spawndoor();

	//Enemies Update
	void countenemy();
	//ENEMIES SPAWN AND MOVEMENT
	void spawnalice(); //Pushback ALICE
	void spawndoom(); //PUSHBACK DOOM
	void spawnbille(); //PUSHBACK BILLIE

	void spawnsmallenemy(); //SPAWN NORMAL ENEMIES

	void updateEnemies(); //Enemies Movement
	void updatealice(); //UPDATE AND SPAWN ALICE
	void updatedoom(); //UPDATE AND SPAWN DOOM
	void updatebillie(); //UPDATE AND SPAWN BILLIE
	void updatesmallenemy(); //UPDATE NORMAL ENEMY MOVEMENT

	//Follow Enemies STUFF
	void closefollow();
	void longfollow();
	void alicefollow();
	void doomfollow();
	void billiefollow();
	

	//==========================
	//      Bullets Update
	//==========================
	void updatebullet(); //bullet movement
	
	//BULLETPLAYER HIT OBJECTS
	void firebullet(); //Keypressed fire
	void bullethit(); //Check bullet hit
	void bullethitalice(); //BULLET HIT ALICE
	void bullethitdoom();  //BULLET HIT DOOM
	void bullethitbillie(); 
	void bullethitclose();  //BULLET HIT CLOSE
	void bullethitlong();  //BULLET HIT LONG

	//ENEMIES BULLET 
	Texture alicetexture;
	Texture doomtexture;
	Texture billtexture;
	Texture longtexture;

	std::vector<EnemiesBullet> aliceb;
	std::vector<EnemiesBullet> doomb;
	std::vector<EnemiesBullet> billb;
	std::vector<EnemiesBullet> longb;

	
	
	int bossbullettime = 350;
	int normalbullettime = 250;
	int delaybullet = 300;

	void enemiesbullet();

	void bulletalice();
	void bulletdoom();
	void bulletbill();
	void bulletlong();

	void updatealicebullet();
	void alicebullethit();
	void updatedoombullet();
	void doombullethit();
	void updatebillbullet();
	void billbullethit();
	void updatelongbullet();
	void longbullethit();

	


	//Collision!!!!!!

	//PLAYER
	void playerhitenemy(); //Check player collide with enemies
	void playerhitalice(); //CHECK PLAYER COLLIDE WITH ALICE
	void playerhitdoom(); //CHECK PLAYER COLLIDE WITH DOOM
	void playerhitbilie();
	void playerhitclose(); //CHECK PLAYER COLLIDE WITH CLOSE
	void playerhitlong(); //CHECK PLAYER COLLIDE WITH LONG
	void playerhitdoor(); //TO CHANGE STAGE

	//FRAME
	void framebound(); //Game Frame Bound
	void playerhitframe(); //Player walk to frame

	//FRAME ENEMIES
	void enemieshitframe(); //Enemies walk to frame
	void alicehitfram(); //ALICE HIT FRAME 
	void doomhitframe(); //DOOM HIT FRAME
	void billiehitframe();
	void closehitframe(); //CLOSE HIT FRAME
	void longhitframe(); //LONG HIT FRAME

	//BULLET ENEMIES
	void bulletshitframe(); //Bullets firing to frame
	
	
	void update(); //Update Stuff

	//Render
	void renderenemies(); //render enemies
	void renderalice(); //RENDER ALICE
	void renderdoom(); //RENDER DOOM
	void renderbillie();
	void renderclose(); //RENDER NORMAL ENEMIES
	void renderlong(); //RENDER NORMAL ENEMIES

	void renderbullets(); //render bullets
	void renderenemiesbullet();

	void rendermap();
	void render(); //Render Objects
	

	Game();

	
};

