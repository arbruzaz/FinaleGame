#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"


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

	//Objects
	std::vector<Bullet> bullets;
	Texture bulletTexture;

	std::vector<Enemy> enemies;


	Texture texbg;
	Sprite map;

	//Variables
	int currentenemiestime = 300;
	int maxenemies = 15;
	int spawntimes = 100;
	int generateRandom(int max);

	//Game Window Running
	void run();
	
	//Functions
	
	//Update
	void spawnEnemy(); //Pushback enemy
	void updateEnemies();
	void firebullet(); //Keypressed fire
	void update(); //Update Stuff

	//Render
	void render(); //Render Objects

	Game();

	
};

