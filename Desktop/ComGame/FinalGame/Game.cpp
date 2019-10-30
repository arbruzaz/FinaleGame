#include "Game.h"
#include <iostream>

Game::Game() : window(VideoMode(1920, 1080), "Blink Game"), player(), ev(), bulletTexture(),
	texbg(), map(), view(FloatRect(0.f, 0.f, 1920.f, 1080.f))
{
	window.setFramerateLimit(60);

	
	//Load Bullet Texture
	bulletTexture.loadFromFile("characters/Logo.png");

	//Load map texture
	texbg.loadFromFile("map/map.png");
	map.setTexture(texbg);
}

int Game::generateRandom(int max)
{
	int randomnumber = rand();
	float random = (randomnumber % max) + 1;
	int myrandom = random;

	return myrandom;
}

void Game::run()
{
	
	while (window.isOpen())
	{
		//Update Objects
		update();
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;
				//Exit Key
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}				
				break;
			}
		}
		
		//Clear window before Run or Update
		window.clear();
		view.setCenter(player.Tom.getPosition());
		window.setView(view);
		//Draw Game Here
		render();

		//Last Display
		window.display();
	}
}


void Game::render()
{
	window.draw(map);
	//Render Player

	window.draw(player.Tom);
	window.draw(player.track);
	//enemies render
	for (auto& enemy : enemies)
	{
		window.draw(enemy.alice);
		window.draw(enemy.track);
	}
	//Bullet Render
	for (auto& bullet : bullets)
	{
		window.draw(bullet.blink);
	}
	//Bullet Render by Pointer
	/*for (std::vector<Bullet>::iterator bullet = bullets.begin(); 
		bullet != bullets.end(); bullet++)
	{
		window.draw(bullet->blink);
	}
	*/
}


void Game::spawnEnemy()
{
	enemy.track.setPosition(Vector2f(
		generateRandom(window.getSize().x), generateRandom(window.getSize().y)));
	enemies.push_back(enemy);
		
}

void Game::updateEnemies()
{
	if (enemies.size() < maxenemies)
	{
		if (currentenemiestime >= spawntimes)
		{
			spawnEnemy();
			currentenemiestime = 0;
		}
		else
			currentenemiestime++;
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].movement();
	}
}

//Fire Bullet
void Game::firebullet()
{
	
	if (Keyboard::isKeyPressed(Keyboard::Space)) {	
		bullet.blink.setPosition({
			player.Tom.getPosition().x,
			player.Tom.getPosition().y
			});
		bullet.direction = player.direction;
		bullet.blink.setTexture(bulletTexture);
		bullets.push_back(bullet);
	}
}

void Game::update()
{
	//Player Movement
	player.update();
	
	//Enemy Update
	updateEnemies();


	//--------Bullets Stuff--------
	//Bullets Movement
	for (auto& bullet : bullets) 
	{
		bullet.update();
	}
	//Firing Pressed
	firebullet();
}