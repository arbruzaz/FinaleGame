#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include<sstream>
#include<string>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "EnemiesBullet.h"
#include "Ui.h"

using namespace std;
using namespace sf;
class Game
{
public:

	Event ev;
	RenderWindow *window;
	View view;
	int* state;
	
	//Class Called
	Player player;
	Enemy enemy;
	Bullet bullet;
	Map map;
	EnemiesBullet enemybullet;
	Ui ui;

	//Sounds
	
	SoundBuffer manoverboard;
	Sound bg;

	SoundBuffer hitbuffer;
	SoundBuffer killbuffer;
	SoundBuffer sbullet;
	SoundBuffer stages;

	Sound hit;
	Sound kill;
	Sound bullethits;
	Sound changestages;

	int* scores;

	//Objects
	vector<Bullet> bullets;
	Texture bulletTexture;

	
	

	vector<Enemy> enemiesalice;
	vector<Enemy> enemiesdoom;
	vector<Enemy> enemiesbillie;
	vector<Enemy> enemiesclose;
	vector<Enemy> enemieslong;
	
	Texture doortext;
	Sprite change;

	Texture hpboxtext;
	Sprite hpbox;

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
	int allkillenemy;
	int maxenemies = 10; //MAX NORMAL ENEMIES
	
	int spawntimes = 100; //MAXSPAWNTIME ENEMY
	
	int stage = 1;   //STAGE GAME
	bool changestage = false;
	
	bool* isplay;
	

	int generateRandom(int max);

	float posPX; //Check Collision QD
	float posPY;

	int level = 1;
	bool upgradeb = false;

	//Game Window Running
	void run();
	
	void upgrade();
	//Functions
	
	//===============UPDATE=================
	void updateui();

	//rehp
	int spawnhp;
	void hpbspawn();
	void hpboxupdate();
	vector<Sprite> hpb;

	//STAGE UPDATE
	void stagechange();
	void spawndoor();
	void endgame();

	//Player gun



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
	void erasebullet();
	
	//BULLETPLAYER HIT OBJECTS
	void firebullet(); //Keypressed fire
	void bullethit(); //Check bullet hit
	void bullethitalice(); //BULLET HIT ALICE
	void bullethitdoom();  //BULLET HIT DOOM
	void bullethitbillie(); 
	void bullethitclose();  //BULLET HIT CLOSE
	void bullethitlong();  //BULLET HIT LONG

	void eraseenemy(); //Erase after died

	//ENEMIES BULLET 
	Texture alicetexture;
	Texture doomtexture;
	Texture billtexture;
	Texture longtexture;

	vector<EnemiesBullet> aliceb;
	vector<EnemiesBullet> doomb;
	vector<EnemiesBullet> billb;
	vector<EnemiesBullet> longb;

	//Enemys Hp
	vector<Ui> aliceui;
	vector<Ui> doomui;
	vector<Ui> billui;
	vector<Ui> longui;
	vector<Ui> closeui;
	
	
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
	void renderui();

	void renderenemies(); //render enemies
	void renderalice(); //RENDER ALICE
	void renderdoom(); //RENDER DOOM
	void renderbillie();
	void renderclose(); //RENDER NORMAL ENEMIES
	void renderlong(); //RENDER NORMAL ENEMIES

	void renderbullets(); //render bullets
	void renderenemiesbullet();

	void renderhpb();
	void rendermap();
	void rendergun();
	bool showgun = false;
	int showguntime = 0;
	void render(); //Render Objects
	

	Game(RenderWindow*,int*,bool*,int*);
};

