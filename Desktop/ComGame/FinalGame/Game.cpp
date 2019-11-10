#include "Game.h"
#include <iostream>

Game::Game() : window(VideoMode(1920, 1080), "Blink Game"), player(), ev(), bulletTexture(),
	view(FloatRect(0.f, 0.f, 960.f, 540.f)),map(),enemy()
{
	window.setFramerateLimit(60);

	std::srand(time(NULL));
	
	//Load Bullet Texture
	bulletTexture.loadFromFile("characters/Logo.png");
	bullet.blink.setTexture(bulletTexture);
	//Player
	player.track.setPosition(500, 500);
	player.Tom.setPosition(player.track.getPosition());

	
	
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
		window.clear(Color::Magenta);
		view.setCenter(player.Tom.getPosition());
		window.setView(view);
		//Draw Game Here
		render();

		//Last Display
		window.display();
	}
}

//================================
//        RENDER ENEMIES
//================================

void Game::renderenemies()
{
	renderalice();
	renderdoom();
	renderclose();
	renderlong();
}

void Game::renderalice()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		window.draw(enemiesalice[i].alice);
		window.draw(enemiesalice[i].trackalice);
	}
}

void Game::renderdoom()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		window.draw(enemiesdoom[i].doom);
		window.draw(enemiesdoom[i].trackdoom);
	}
}

void Game::renderlong()
{
	for (int j = 0; j < enemieslong.size(); j++)
	{
		window.draw(enemieslong[j].longenemy);
		window.draw(enemieslong[j].tracklong);		
	}
}

void Game::renderclose()
{
	for (int i = 0; i < enemiesclose.size(); i++)
	{
		window.draw(enemiesclose[i].closeenemy);
		window.draw(enemiesclose[i].trackclose);		
	}	
}


//=============================
//       RENDER BULLETS
//=============================

void Game::renderbullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i].blink);
	}
}


//RENDER MAP
void Game::rendermap()
{
	map.fmap1.setPosition(0, 0);
	map.fmap2.setPosition(Vector2f(window.getSize().x - map.bgf2.getSize().x, 0));
	map.fmap3.setPosition(Vector2f(0, window.getSize().y - map.bgf3.getSize().y));
	map.fmap4.setPosition(0, 0);
	window.draw(map.map1);
	window.draw(map.fmap1);
	window.draw(map.fmap2);
	window.draw(map.fmap3);
	window.draw(map.fmap4);	
}


//RENDER ALL
void Game::render()
{
	
	//Render Player
	rendermap();
	window.draw(player.Tom);
	window.draw(player.track);
    
	renderenemies();
	renderbullets();
	
	
}



//========================================
//              SPAWN ENEMIES
//          UPDATE ENEMIES MOVEMENT
//========================================

void Game::spawnalice()
{
	enemy.trackalice.setPosition(Vector2f(
		generateRandom(window.getSize().x), 
		generateRandom(window.getSize().y)));
	enemiesalice.push_back(enemy);
		
}

void Game::spawndoom()
{
	enemy.trackdoom.setPosition(Vector2f(
		generateRandom(window.getSize().x),
		generateRandom(window.getSize().y)));
	enemy.doom.setPosition(enemy.trackdoom.getPosition());
	enemiesdoom.push_back(enemy);
}

void Game::spawnsmallenemy()
{
	enemyrandom = generateRandom(3);
	if (enemyrandom == 3)
	{
		enemy.tracklong.setPosition(Vector2f(
			generateRandom(window.getSize().x),
			generateRandom(window.getSize().y)));
		enemy.longenemy.setPosition(enemy.tracklong.getPosition());
		enemieslong.push_back(enemy);
		
	}
	else
	{
		enemy.trackclose.setPosition(Vector2f(
			generateRandom(window.getSize().x),
			generateRandom(window.getSize().y)));
		enemy.closeenemy.setPosition(enemy.trackclose.getPosition());
		enemiesclose.push_back(enemy);
		
	}
}

void Game::updateEnemies()
{
	updatealice();
	updatedoom();
	updatesmallenemy();
}

void Game::updatealice()
{
	if (enemiesalice.size() < maxalice)
	{
		if (currentenemiestime >= spawntimes)
		{
			spawnalice();
			currentenemiestime = 0;			
		}
		else
			currentenemiestime++;

	}

	for (int i = 0; i < enemiesalice.size(); i++)
	{
		enemiesalice[i].alicemovement();
	}
}

void Game::updatedoom()
{
	if (enemiesdoom.size() < maxdoom)
	{
		if (currentenemiestime >= spawntimes)
		{
			spawndoom();
			currentenemiestime = 0;
		}
		else
			currentenemiestime++;

	}

	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		enemiesdoom[i].doommovement();
	}
}

void Game::updatesmallenemy()
{
	if (enemiesclose.size() + enemieslong.size() < maxenemies)
	{
		if (currentenemiestime >= spawntimes)
		{
			spawnsmallenemy();
			currentenemiestime = 0;
			std::cout << enemiesclose.size() <<
				"   " << enemieslong.size() <<std::endl;
		}
		else
			currentenemiestime++;
	}

	for (int i = 0; i < enemiesclose.size(); i++)
	{		
		enemiesclose[i].closemovement();	
	}
	for (int j = 0; j < enemieslong.size(); j++)
	{
		enemieslong[j].longmovement();
	}
}





//==================================================
//                 FIRING BULLET
//              BULLET HITS ENEMIES
//==================================================

//KEYPRESSED BULLET
void Game::firebullet()
{
	
	if (Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		if (firehold == false)
		{
			firehold = true;		

			bullet.direction = player.direction;
			bullet.blink.setOrigin(Vector2f(bulletTexture.getSize().x / 2,
				bulletTexture.getSize().y / 2));
			if (bullet.direction == 1)
			{
				bullet.blink.setPosition({
					player.Tom.getPosition().x,
					player.Tom.getPosition().y-100
					});
			}
			if (bullet.direction == 2)
			{
				bullet.blink.setPosition({
					player.Tom.getPosition().x,
					player.Tom.getPosition().y+100
					});
			}
			if (bullet.direction == 3)
			{
				bullet.blink.setPosition({
									player.Tom.getPosition().x-100,
									player.Tom.getPosition().y
					});
			}
			if (bullet.direction == 4)
			{
				bullet.blink.setPosition({
					player.Tom.getPosition().x+100,
					player.Tom.getPosition().y
					});
			}
						
			bullets.push_back(bullet);
		}
	}
	else firehold = false;
	
	

}

//BULLET MOVEMENT
void Game::updatebullet()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].update();
	}
}

//BULLET HIT ENEMIES
void Game::bullethit()
{
	//Bullet hit !!!!!!!!!!!!!!!!
	bullethitalice();
	bullethitdoom();
	bullethitclose();
	bullethitlong();
}

void Game::bullethitalice()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesalice.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesalice[j].trackalice.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesalice[j].alicehp--;
				break;
			}
			//OUT OF HP ENEMY DEAD
			if (enemiesalice[j].alicehp <= 0) { enemiesalice[j].alive = false; }
		}
	}
	//Delete enemy
	for (int j = 0; j < enemiesalice.size(); j++)
	{
		if (enemiesalice[j].alive == false)
		{
			enemiesalice.erase(enemiesalice.begin() + j);
		}
	}
}

void Game::bullethitdoom()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesdoom.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesdoom[j].trackdoom.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesdoom[j].doomhp--;
				break;
			}
			//OUT OF HP ENEMY DEAD
			if (enemiesdoom[j].doomhp <= 0) { enemiesdoom[j].alive = false; }
		}
	}
	//Delete enemy
	for (int j = 0; j < enemiesdoom.size(); j++)
	{
		if (enemiesdoom[j].alive == false)
		{
			enemiesdoom.erase(enemiesdoom.begin() + j);
		}
	}
}

void Game::bullethitclose()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesclose.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesclose[j].trackclose.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesclose[j].closehp--;
				break;
			}
			//OUT OF HP ENEMY DEAD
			if (enemiesclose[j].closehp <= 0) { enemiesclose[j].alive = false; }
		}
	}
	//Delete enemy
	for (int j = 0; j < enemiesclose.size(); j++)
	{
		if (enemiesclose[j].alive == false)
		{
			enemiesclose.erase(enemiesclose.begin() + j);
		}
	}
}

void Game::bullethitlong()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemieslong.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemieslong[j].tracklong.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemieslong[j].longhp--;
				break;
			}
			//OUT OF HP ENEMY DEAD
			if (enemieslong[j].longhp <= 0) { enemieslong[j].alive = false; }
		}
	}
	//Delete enemy
	for (int j = 0; j < enemieslong.size(); j++)
	{
		if (enemieslong[j].alive == false)
		{
			enemieslong.erase(enemieslong.begin() + j);
		}
	}
}


//======================================
//        PLAYER BOUNCE ENEMIES
//======================================

void Game::playerhitenemy()
{
	playerhitalice();
	playerhitdoom();
	playerhitclose();
	playerhitlong();
}

void Game::playerhitalice()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemiesalice[i].trackalice.getGlobalBounds()))
		{
			if (abs(enemiesalice[i].trackalice.getPosition().x - posPX) >
				abs(enemiesalice[i].trackalice.getPosition().y - posPY))
			{
				if (enemiesalice[i].trackalice.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesalice[i].trackalice.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}

			if (abs(enemiesalice[i].trackalice.getPosition().y - posPY) >
				abs(enemiesalice[i].trackalice.getPosition().x - posPX))
			{
				if (enemiesalice[i].trackalice.getPosition().y > posPY)
				{
					player.track.setPosition(posPX, posPY - 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesalice[i].trackalice.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}
		}
	}
}

void Game::playerhitdoom()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemiesdoom[i].trackdoom.getGlobalBounds()))
		{
			if (abs(enemiesdoom[i].trackdoom.getPosition().x - posPX) >
				abs(enemiesdoom[i].trackdoom.getPosition().y - posPY))
			{
				if (enemiesdoom[i].trackdoom.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesdoom[i].trackdoom.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}

			if (abs(enemiesdoom[i].trackdoom.getPosition().y - posPY) >
				abs(enemiesdoom[i].trackdoom.getPosition().x - posPX))
			{
				if (enemiesdoom[i].trackdoom.getPosition().y > posPY)
				{
					player.track.setPosition(posPX, posPY - 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesdoom[i].trackdoom.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}
		}
	}
}

void Game::playerhitclose()
{
	for (int i = 0; i < enemiesclose.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemiesclose[i].trackclose.getGlobalBounds()))
		{
			if (abs(enemiesclose[i].trackclose.getPosition().x - posPX) >
				abs(enemiesclose[i].trackclose.getPosition().y - posPY))
			{
				if (enemiesclose[i].trackclose.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesclose[i].trackclose.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}

			if (abs(enemiesclose[i].trackclose.getPosition().y - posPY) >
				abs(enemiesclose[i].trackclose.getPosition().x - posPX))
			{
				if (enemiesclose[i].trackclose.getPosition().y > posPY)
				{
					player.track.setPosition(posPX, posPY - 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemiesclose[i].trackclose.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}
		}
	}
}

void Game::playerhitlong()
{
	for (int i = 0; i < enemieslong.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemieslong[i].tracklong.getGlobalBounds()))
		{
			if (abs(enemieslong[i].tracklong.getPosition().x - posPX) >
				abs(enemieslong[i].tracklong.getPosition().y - posPY))
			{
				if (enemieslong[i].tracklong.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemieslong[i].tracklong.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}

			if (abs(enemieslong[i].tracklong.getPosition().y - posPY) >
				abs(enemieslong[i].tracklong.getPosition().x - posPX))
			{
				if (enemieslong[i].tracklong.getPosition().y > posPY)
				{
					player.track.setPosition(posPX, posPY - 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
				if (enemieslong[i].tracklong.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					break;
				}
			}
		}
	}
}


//===================================
//      OBJECTS HIT FRAME
//===================================

void Game::framebound()
{	
	playerhitframe();
	enemieshitframe();
	bulletshitframe();	
}

//PLAYER
void Game::playerhitframe()
{
	posPX = player.track.getPosition().x;
	posPY = player.track.getPosition().y;
	if (player.track.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
	{
		player.track.setPosition(posPX + 10, posPY);
		player.Tom.setPosition(player.track.getPosition());
	}
	if (player.track.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
	{
		player.track.setPosition(posPX - 10, posPY);
		player.Tom.setPosition(player.track.getPosition());
	}
	if (player.track.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
	{
		player.track.setPosition(posPX, posPY - 10);
		player.Tom.setPosition(player.track.getPosition());
	}
	if (player.track.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
	{
		player.track.setPosition(posPX, posPY + 10);
		player.Tom.setPosition(player.track.getPosition());
	}
}

//ENEMIES
void Game::enemieshitframe()
{
	alicehitfram();
	doomhitframe();
	closehitframe();
	longhitframe();
}

void Game::alicehitfram()
{
	//Get new directions everytime when collision
	for(int i = 0; i < enemiesalice.size(); i++)
	{
		if (enemiesalice[i].trackalice.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
		{
			enemiesalice[i].trackalice.setPosition(enemiesalice[i].trackalice.getPosition().x + 10, enemiesalice[i].trackalice.getPosition().y);
			enemiesalice[i].direction = generateRandom(4);
			break;
		}
		if (enemiesalice[i].trackalice.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
		{
			enemiesalice[i].trackalice.setPosition(enemiesalice[i].trackalice.getPosition().x - 10, enemiesalice[i].trackalice.getPosition().y);
			enemiesalice[i].direction = generateRandom(4);
			break;
		}
		if (enemiesalice[i].trackalice.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
		{
			enemiesalice[i].trackalice.setPosition(enemiesalice[i].trackalice.getPosition().x, enemiesalice[i].trackalice.getPosition().y - 10);
			enemiesalice[i].direction = generateRandom(4);
			break;
		}
		if (enemiesalice[i].trackalice.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
		{
			enemiesalice[i].trackalice.setPosition(enemiesalice[i].trackalice.getPosition().x, enemiesalice[i].trackalice.getPosition().y + 10);
			enemiesalice[i].direction = generateRandom(4);
			break;
		}
	}
}

void Game::doomhitframe()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		if (enemiesdoom[i].trackdoom.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
		{
			enemiesdoom[i].trackdoom.setPosition(enemiesdoom[i].trackdoom.getPosition().x + 10, enemiesdoom[i].trackdoom.getPosition().y);
			enemiesdoom[i].direction = generateRandom(4);
			break;
		}
		if (enemiesdoom[i].trackdoom.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
		{
			enemiesdoom[i].trackdoom.setPosition(enemiesdoom[i].trackdoom.getPosition().x - 10, enemiesdoom[i].trackdoom.getPosition().y);
			enemiesdoom[i].direction = generateRandom(4);
			break;
		}
		if (enemiesdoom[i].trackdoom.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
		{
			enemiesdoom[i].trackdoom.setPosition(enemiesdoom[i].trackdoom.getPosition().x, enemiesdoom[i].trackdoom.getPosition().y - 10);
			enemiesdoom[i].direction = generateRandom(4);
			break;
		}
		if (enemiesdoom[i].trackdoom.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
		{
			enemiesdoom[i].trackdoom.setPosition(enemiesdoom[i].trackdoom.getPosition().x, enemiesdoom[i].trackdoom.getPosition().y + 10);
			enemiesdoom[i].direction = generateRandom(4);
			break;
		}
	}
}

void Game::closehitframe()
{
	for (int i = 0; i < enemiesclose.size(); i++)
	{
		if (enemiesclose[i].trackclose.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
		{
			enemiesclose[i].trackclose.setPosition(enemiesclose[i].trackclose.getPosition().x + 10, enemiesclose[i].trackclose.getPosition().y);
			enemiesclose[i].direction = generateRandom(4);
			break;
		}
		if (enemiesclose[i].trackclose.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
		{
			enemiesclose[i].trackclose.setPosition(enemiesclose[i].trackclose.getPosition().x - 10, enemiesclose[i].trackclose.getPosition().y);
			enemiesclose[i].direction = generateRandom(4);
			break;
		}
		if (enemiesclose[i].trackclose.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
		{
			enemiesclose[i].trackclose.setPosition(enemiesclose[i].trackclose.getPosition().x, enemiesclose[i].trackclose.getPosition().y - 10);
			enemiesclose[i].direction = generateRandom(4);
			break;
		}
		if (enemiesclose[i].trackclose.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
		{
			enemiesclose[i].trackclose.setPosition(enemiesclose[i].trackclose.getPosition().x, enemiesclose[i].trackclose.getPosition().y + 10);
			enemiesclose[i].direction = generateRandom(4);
			break;
		}
	}
}

void Game::longhitframe()
{
	for (int i = 0; i < enemieslong.size(); i++)
	{
		if (enemieslong[i].tracklong.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
		{
			enemieslong[i].tracklong.setPosition(enemieslong[i].tracklong.getPosition().x + 10, enemieslong[i].tracklong.getPosition().y);
			enemieslong[i].direction = generateRandom(4);
			break;
		}
		if (enemieslong[i].tracklong.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
		{
			enemieslong[i].tracklong.setPosition(enemieslong[i].tracklong.getPosition().x - 10, enemieslong[i].tracklong.getPosition().y);
			enemieslong[i].direction = generateRandom(4);
			break;
		}
		if (enemieslong[i].tracklong.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
		{
			enemieslong[i].tracklong.setPosition(enemieslong[i].tracklong.getPosition().x, enemieslong[i].tracklong.getPosition().y - 10);
			enemieslong[i].direction = generateRandom(4);
			break;
		}
		if (enemieslong[i].tracklong.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
		{
			enemieslong[i].tracklong.setPosition(enemieslong[i].tracklong.getPosition().x, enemieslong[i].tracklong.getPosition().y + 10);
			enemieslong[i].direction = generateRandom(4);
			break;
		}
	}
}


//BULLETS
void Game::bulletshitframe()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].blink.getGlobalBounds().intersects(
			map.fmap1.getGlobalBounds()))
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].blink.getGlobalBounds().intersects(
			map.fmap2.getGlobalBounds()))
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].blink.getGlobalBounds().intersects(
			map.fmap3.getGlobalBounds()))
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
		if (bullets[i].blink.getGlobalBounds().intersects(
			map.fmap4.getGlobalBounds()))
		{
			bullets.erase(bullets.begin() + i);
			break;
		}
	}
}


//UPDATE ALL
void Game::update()
{
	//Player Update
	player.update(); //Player Movement

	
	//Enemy Update
	
	updateEnemies(); //Movement And Spawn Enemy
	
	//Bullets Update
	updatebullet(); //Bullets Movement	
	firebullet(); //Firing Pressed

	//Collision Frame
	framebound();

	//GAME UPDATE
	playerhitenemy(); //Player collision
	bullethit(); //BULLETS HIT ENEMIES

}