#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Game::Game(RenderWindow* w, int* st, bool* isp,int* s) : player(), ev(), bulletTexture(),
view(FloatRect(0.f, 0.f, 960.f, 540.f)), map(), enemy()
{
	window = w;
	state = st;
	isplay = isp;
	scores = s;
	

	window->setFramerateLimit(60);

	srand(time(NULL));
		

	//PAUSE
	font.loadFromFile("mapgame/RESURREC.ttf");
	popup.setFont(font);

	

	//Load Bullet Texture
	bulletTexture.loadFromFile("characters/Logo.png");
	bullet.blink.setTexture(bulletTexture);
	//Player
	player.track.setPosition(500, 500);
	player.Tom.setPosition(player.track.getPosition());

	//ENEMIES BULLET TEXTURE
	alicetexture.loadFromFile("characters/alicebullet.png");
	doomtexture.loadFromFile("characters/doombullet.png");
	billtexture.loadFromFile("characters/greenday.png");
	longtexture.loadFromFile("characters/longbullet.png");


	enemybullet.aliceX = alicetexture.getSize().x / 5;
	enemybullet.aliceY = alicetexture.getSize().y / 4;
	enemybullet.alicebullet.setOrigin(enemybullet.aliceX/2, enemybullet.aliceY/2);

	enemybullet.doomX = doomtexture.getSize().x / 2;
	enemybullet.doomY = doomtexture.getSize().y / 4;
	enemybullet.doombullet.setOrigin(enemybullet.doomX/2, enemybullet.doomY/2);

	enemybullet.longX = longtexture.getSize().x / 2;
	enemybullet.longY = longtexture.getSize().y;
	enemybullet.longbullet.setOrigin(enemybullet.longX/2, enemybullet.longY/2);

	enemybullet.billX = billtexture.getSize().x;
	enemybullet.billY = billtexture.getSize().y;
	enemybullet.billbullet.setOrigin(enemybullet.billX/2, enemybullet.billY/2);

	hpboxtext.loadFromFile("mapgame/rehp.png");
	hpbox.setTexture(hpboxtext);
	hpbox.setOrigin(Vector2f(hpboxtext.getSize().x / 2, hpboxtext.getSize().y / 2));
	hpbox.setScale(0.2, 0.2);

	blood.loadFromFile("characters/blood.png");
	lowhp.setTexture(blood);
	lowhp.setOrigin(Vector2f(blood.getSize().x / 2, blood.getSize().y / 2));
	lowhp.setScale(0.5, 0.5);

	doortext.loadFromFile("mapgame/door.png");
	change.setTexture(doortext);
	change.setOrigin(Vector2f(doortext.getSize().x / 2, doortext.getSize().y / 2));
	change.setScale(0.2, 0.2);
	change.setPosition(1700, 800);

	manoverboard.loadFromFile("mapgame/man.ogg");
	bg.setBuffer(manoverboard);
	bg.setLoop(true);
	bg.play();
	bg.setVolume(5.f);

	hitbuffer.loadFromFile("mapgame/hit.wav");
	hit.setBuffer(hitbuffer);

	killbuffer.loadFromFile("mapgame/kill.wav");
	kill.setBuffer(killbuffer);

	sbullet.loadFromFile("mapgame/bullethit.wav");
	bullethits.setBuffer(sbullet);
	
	stages.loadFromFile("mapgame/stage.wav");
	changestages.setBuffer(stages);

	
	
	
}

void Game::updatepause()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		select--;
		if (select < 0) { select = 0; }
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		select++;
		if (select > 1) { select = 1; }
	}
}

void Game::renderpause()
{
	for (int i = 0; i < 2; i++)
	{
		popup.setString(inpopup[i]);
		popup.setCharacterSize(30);
		popup.setStyle(sf::Text::Bold);
		popup.setFillColor(sf::Color::Black);
		if (select == i)
		{
			popup.setFillColor(sf::Color::Red);
		}
		popup.setPosition(Vector2f(player.track.getPosition().x - 50, player.track.getPosition().y - 100 + 50*i));
		window->draw(popup);
	}
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
		while (window->isOpen())
		{
			
			//Update Objects
			update();
			while (window->pollEvent(ev))
			{
				switch (ev.type)
				{
				case Event::Closed:
					window->close();
					break;
					//Exit Key
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						pause = true;
					}
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						if (select == 0)
						{
							pause = false;
						}
						if (select == 1)
						{
							pause = false;
							stage = 4;
						}

					}
					break;
				}				
			}

			//Clear window before Run or Update
			window->clear(Color::Magenta);
			if (!(*isplay)) break;
			view.setCenter(player.Tom.getPosition());
			window->setView(view);
			//Draw Game Here
			render();

			//Last Display
			window->display();
		}
	
}

void Game::upgrade()
{
	if (*scores >= 300 && level == 1)
	{
		player.damage++;
		level = 2;
	}
	else if (*scores >= 500 && level == 2)
	{
		player.tommaxhp += 5;
		level = 3;
	}
	else if (*scores >= 700 && level == 3)
	{
		player.damage++;
		level = 4;
	}
	else if (*scores >= 1000 && level == 4)
	{
		player.damage++;
		player.tommaxhp += 5;
		level = 5;
	}
	else if (*scores >= 1300 && level == 5)
	{
		player.damage++;
		level = 6;
	}
	else if (*scores >= 1600 && level == 6)
	{
		player.tommaxhp += 5;
		level = 7;
	}
	else if (*scores >= 2000 && level == 7)
	{
		player.tommaxhp += 10;
		player.damage += 5;
		level = 8;
	}
}

void Game::updateui()
{
	ui.uihp.setPosition(Vector2f(player.track.getPosition().x - 430, player.track.getPosition().y - 200));
	ui.uihp.setString("HP : " + to_string(player.tomhp) + " / " + to_string(player.tommaxhp));

	ui.uiscore.setPosition(Vector2f(player.track.getPosition().x - 430, player.track.getPosition().y - 250));
	ui.uiscore.setString("Scores : " + to_string(*scores));

	ui.uilevel.setPosition(Vector2f(player.track.getPosition().x + 330, player.track.getPosition().y - 150));
	ui.uilevel.setString("Level : " + to_string(level));

	ui.uiattack.setPosition(Vector2f(player.track.getPosition().x + 330, player.track.getPosition().y - 200));
	ui.uiattack.setString("Damages : " + to_string(player.damage));
	
	ui.uikill.setPosition(Vector2f(player.track.getPosition().x + 330, player.track.getPosition().y - 250));
	ui.uikill.setString("Kills : " + to_string(allkillenemy));
}

void Game::updatelowhp()
{
	lowhp.setPosition(player.track.getPosition());
	if (player.tomhp <= 10)
	{
		getdamage = true;
	}
}

void Game::renderlow()
{
	if (getdamage)
	{
		window->draw(lowhp);
	}
	if (showdamagetime >= 200)
	{
		getdamage = false;
		showdamagetime = 0;
	}
	else { showdamagetime++; }
}

void Game::hpbspawn()
{
	hpbox.setPosition(Vector2f(
		generateRandom((window->getSize().x - 200)) + 150,
		generateRandom((window->getSize().y-100)) + 100));
	hpb.push_back(hpbox);
}

void Game::hpboxupdate()
{
	spawnhp = generateRandom(1000);
	if (spawnhp == 45)
	{
		hpbspawn();
	}

	for (int i = 0; i < hpb.size(); i++)
	{
		if (player.track.getGlobalBounds().intersects(hpb[i].getGlobalBounds()))
		{
			player.tomhp += 7;
			if (player.tomhp >= player.tommaxhp) player.tomhp = player.tommaxhp;
			hpb.erase(hpb.begin() + i);
			break;
		}
	}
}

void Game::stagechange()
{
	playerhitdoor();
	if (killalice >= 3 && stage == 1)
	{
		changestage = true;
	}
	if (killdoom >= 2 && stage == 2)
	{
		changestage = true;
	}
	if (killbillie >= 1 && stage == 3)
	{
		changestage = true;
	}
}

void Game::spawndoor()
{
	if (changestage)
	{
		window->draw(change);
	}
}

void Game::endgame()
{
	if (player.tomhp <= 0)
	{
		cout << "dead" << endl;
		*state = 3;
		*isplay = false;
		player.tommaxhp = 60;
		player.damage = 1;
		player.tomhp = player.tommaxhp;
		level = 1;
		stage = 1;

		maxenemies = 10;
		getdamage = false;
		killalice = 0;
		killbillie = 0;
		killdoom = 0;
		boss = 0;
		killenemy = 0;
		allkillenemy = 0;
		nowalice = 0;
		nowdoom = 0;
		nowbillie = 0;
		changestage = false;
		aliceb.clear();
		doomb.clear();
		billb.clear();
		longb.clear();

		hpb.clear();
		enemiesalice.clear();
		enemiesdoom.clear();
		enemiesbillie.clear();
		enemiesclose.clear();
		enemieslong.clear();
	}
	else if (stage == 4)
	{		
		*state = 3;
		*isplay = false;
		player.tommaxhp = 60;
		player.damage = 1;
		player.tomhp = player.tommaxhp;
		hpb.clear();
		maxenemies = 10;
		getdamage = false;
		stage = 1;
		level = 1;
		boss = 0;
		killalice = 0;
		killbillie = 0;
		killdoom = 0;
		killenemy = 0;
		allkillenemy = 0;
		nowalice = 0;
		nowdoom = 0;
		nowbillie = 0;
		changestage = false;
		aliceb.clear();
		doomb.clear();
		billb.clear();
		longb.clear();

		enemiesalice.clear();
		enemiesdoom.clear();
		enemiesbillie.clear();
		enemiesclose.clear();
		enemieslong.clear();
	}
}


void Game::playerhitdoor()
{
	if (changestage)
	{
		if (player.track.getGlobalBounds().
			intersects(change.getGlobalBounds()))
		{
			changestages.play();
			stage++;
			player.tomhp = player.tommaxhp;
			killenemy = 0;
			nowalice = 0;
			nowdoom = 0;
			nowbillie = 0;
			changestage = false;		

			maxenemies += 3;
			aliceb.clear();
			doomb.clear();
			billb.clear();
			longb.clear();

			hpb.clear();
			enemiesalice.clear();
			enemiesdoom.clear();
			enemiesbillie.clear();
			enemiesclose.clear();
			enemieslong.clear();
		}
	}
	
	

}

//================================
//        RENDER ENEMIES
//================================

void Game::renderui()
{
	window->draw(ui.uiscore);
	window->draw(ui.uihp);
	window->draw(ui.uiattack);
	window->draw(ui.uilevel);
	window->draw(ui.uikill);
}

void Game::renderenemies()
{
	renderalice();
	renderdoom();
	renderclose();
	renderlong();
	renderbillie();
}

void Game::renderalice()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		window->draw(enemiesalice[i].aliceuihp);
		window->draw(enemiesalice[i].alice);
		//window->draw(enemiesalice[i].trackalice);
	}
}

void Game::renderdoom()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		window->draw(enemiesdoom[i].doomuihp);
		window->draw(enemiesdoom[i].doom);
	//	window->draw(enemiesdoom[i].trackdoom);
	}
}

void Game::renderbillie()
{
	for (int i = 0; i < enemiesbillie.size(); i++)
	{
		window->draw(enemiesbillie[i].billuihp);
		window->draw(enemiesbillie[i].billie);
		//window->draw(enemiesbillie[i].trackbill);
	}
}

void Game::renderlong()
{
	for (int j = 0; j < enemieslong.size(); j++)
	{
		window->draw(enemieslong[j].longuihp);
		window->draw(enemieslong[j].longenemy);
		//window->draw(enemieslong[j].tracklong);		
	}
}

void Game::renderclose()
{
	for (int i = 0; i < enemiesclose.size(); i++)
	{
		window->draw(enemiesclose[i].closeuihp);
		window->draw(enemiesclose[i].closeenemy);
		//window->draw(enemiesclose[i].trackclose);		
	}	
}


//=============================
//       RENDER BULLETS
//=============================

void Game::renderbullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window->draw(bullets[i].blink);
	}
}

void Game::renderenemiesbullet()
{
	for (int i = 0; i < aliceb.size(); i++)
	{
		window->draw(aliceb[i].alicebullet);
	}
	for (int i = 0; i < doomb.size(); i++)
	{
		window->draw(doomb[i].doombullet);
	}
	for (int i = 0; i < billb.size(); i++)
	{
		window->draw(billb[i].billbullet);
	}
	for (int i = 0; i < longb.size(); i++)
	{
		window->draw(longb[i].longbullet);
	}
}


void Game::renderhpb()
{
	for (int i = 0; i < hpb.size(); i++)
	{
		window->draw(hpb[i]);
	}
}

//RENDER MAP
void Game::rendermap()
{
	map.fmap1.setPosition(0, 0);
	map.fmap2.setPosition(Vector2f(window->getSize().x - map.bgf2.getSize().x, 0));
	map.fmap3.setPosition(Vector2f(0, 1080.f - map.bgf3.getSize().y));
	map.fmap4.setPosition(0, 0);
	if (stage == 1) { window->draw(map.map1); }
	if (stage == 2) { window->draw(map.map2); }
	if (stage == 3) { window->draw(map.map3); }

	
	window->draw(map.fmap1);
	window->draw(map.fmap2);
	window->draw(map.fmap3);
	window->draw(map.fmap4);	
}

void Game::rendergun()
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		showgun = true;
		showguntime = 0;
	}

	if (showgun)
	{
		window->draw(player.gun);
		showguntime++;
	}

	if (showguntime >= 20)
	{
		showguntime = 0;
		showgun = false;
	}

}


//RENDER ALL
void Game::render()
{
		//Render Player
		rendermap();
		renderui();
		renderhpb();	
		window->draw(player.Tom);
		rendergun();
		
		//window->draw(player.track);

		renderenemies();
		renderbullets();
		renderenemiesbullet();
		renderlow();
		spawndoor();
		if (pause) { renderpause(); }
	
}



//========================================
//              SPAWN ENEMIES
//          UPDATE ENEMIES MOVEMENT
//========================================



void Game::countenemy()
{
	if (killenemy >= maxenemies * stage && stage == 1)
	{
		boss = 1;	
	}
	if (killenemy >= maxenemies * stage && stage == 2)
	{
		boss = 2;
	}
	if (killenemy >= maxenemies * stage && stage == 3)
	{
		boss = 3;
	}
	
}

void Game::spawnalice()
{
	enemy.trackalice.setPosition(Vector2f(
		generateRandom(window->getSize().x), 
		generateRandom(window->getSize().y)));
	enemiesalice.push_back(enemy);
		
}

void Game::spawndoom()
{
	enemy.trackdoom.setPosition(Vector2f(
		generateRandom(window->getSize().x),
		generateRandom(window->getSize().y)));
	enemy.doom.setPosition(enemy.trackdoom.getPosition());
	enemiesdoom.push_back(enemy);
}

void Game::spawnbille()
{
	enemy.trackbill.setPosition(Vector2f(
		generateRandom(window->getSize().x),
		generateRandom(window->getSize().y)));
	enemy.billie.setPosition(enemy.trackbill.getPosition());
	enemiesbillie.push_back(enemy);
}

void Game::spawnsmallenemy()
{
	enemyrandom = generateRandom(3);
	if (enemyrandom == 3)
	{
		enemy.tracklong.setPosition(Vector2f(
			generateRandom(window->getSize().x),
			generateRandom(window->getSize().y)));
		enemy.longenemy.setPosition(enemy.tracklong.getPosition());
		enemieslong.push_back(enemy);
		
	}
	else
	{
		enemy.trackclose.setPosition(Vector2f(
			generateRandom(window->getSize().x),
			generateRandom(window->getSize().y)));
		enemy.closeenemy.setPosition(enemy.trackclose.getPosition());
		enemiesclose.push_back(enemy);
		
	}
}

void Game::updateEnemies()
{
	if (stage == 1) {
		updatealice();
	}
	if (stage == 2) {
		updatealice();
		updatedoom();
	}
	if (stage == 3) {
		updatealice();
		updatedoom();
		updatebillie();
	}
	updatesmallenemy();
	eraseenemy();
	countenemy();
}

void Game::updatealice()
{
	if (boss > 0)
	{
		if (stage == 1)
		{
			if (nowalice < maxalice)
			{
				if (currentenemiestime >= spawntimes)
				{
					spawnalice();
					currentenemiestime = 0;
					nowalice++;
				}
				else
					currentenemiestime++;
			}
		}
		else if (stage > 1)
		{
			if (enemiesalice.size() < maxalice)
			{
				if (currentenemiestime >= spawntimes)
				{
					spawnalice();
					currentenemiestime = 0;
					nowalice++;
				}
				else
					currentenemiestime++;
			}
		}
		
		for (int i = 0; i < enemiesalice.size(); i++)
		{	
			enemiesalice[i].aliceuihp.setPosition(Vector2f(
				enemiesalice[i].trackalice.getPosition().x - 20 ,
				enemiesalice[i].trackalice.getPosition().y - 61));
			enemiesalice[i].aliceuihp.setString(to_string(enemiesalice[i].alicehp) +
				" / " + to_string(enemiesalice[i].maxalice));
			if (!enemiesalice[i].follow)
			{
				enemiesalice[i].alicemovement();
			}
			else if (enemiesalice[i].follow)
			{
				alicefollow();
				enemiesalice[i].alicemovement();
			}
		}
	}
	
}

void Game::updatedoom()
{
	if (boss >= 2)
	{
		
		if (stage == 2)
		{
			if (nowdoom < maxdoom)
			{
				if (currentenemiestime >= spawntimes)
				{
					spawndoom();
					nowdoom++;
					currentenemiestime = 0;
				}
				else
					currentenemiestime++;

			}			
		}
		else if (stage > 2)
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
		}
		

		for (int i = 0; i < enemiesdoom.size(); i++)
		{
			enemiesdoom[i].doomuihp.setPosition(Vector2f(
				enemiesdoom[i].trackdoom.getPosition().x - 20,
				enemiesdoom[i].trackdoom.getPosition().y - 70));
			enemiesdoom[i].doomuihp.setString(to_string(enemiesdoom[i].doomhp) +
				" / " + to_string(enemiesdoom[i].maxdoom));
			if (!enemiesdoom[i].follow)
			{
				enemiesdoom[i].doommovement();
			}
			else if (enemiesdoom[i].follow)
			{
				doomfollow();
				enemiesdoom[i].doommovement();
			}
		}
	}
	
}

void Game::updatebillie()
{
	if (boss > 2)
	{	
		 if (stage > 2)
		{
			if (enemiesbillie.size() < maxbillie)
			{
				if (currentenemiestime >= spawntimes)
				{
					spawnbille();
					nowbillie++;
					currentenemiestime = 0;
				}
				else
					currentenemiestime++;

			}
		}


		for (int i = 0; i < enemiesbillie.size(); i++)
		{		
			enemiesbillie[i].billuihp.setPosition(Vector2f(
				enemiesbillie[i].trackbill.getPosition().x - 20,
				enemiesbillie[i].trackbill.getPosition().y - 130));
			enemiesbillie[i].billuihp.setString(to_string(enemiesbillie[i].billhp) +
				" / " + to_string(enemiesbillie[i].maxbill));
			if (!enemiesbillie[i].follow)
			{
				enemiesbillie[i].billmovement();
			}
			else if (enemiesbillie[i].follow)
			{
				billiefollow();
				enemiesbillie[i].billmovement();
			}
		}
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
		}
		else
			currentenemiestime++;
	}

	for (int i = 0; i < enemiesclose.size(); i++)
	{		
		enemiesclose[i].closeuihp.setPosition(Vector2f(
			enemiesclose[i].trackclose.getPosition().x - 20,
			enemiesclose[i].trackclose.getPosition().y - 61));
		enemiesclose[i].closeuihp.setString(to_string(enemiesclose[i].closehp) +
			" / " + to_string(enemiesclose[i].maxclose));
		if (!enemiesclose[i].follow)
		{
			enemiesclose[i].closemovement();
		}
		else if (enemiesclose[i].follow)
		{
			closefollow();
			enemiesclose[i].closemovement();
		}
	}
	for (int j = 0; j < enemieslong.size(); j++)
	{
		enemieslong[j].longuihp.setPosition(Vector2f(
			enemieslong[j].tracklong.getPosition().x - 20,
			enemieslong[j].tracklong.getPosition().y - 61));
		enemieslong[j].longuihp.setString(to_string(enemieslong[j].longhp) +
			" / " + to_string(enemieslong[j].maxlong));
		if (!enemieslong[j].follow)
		{
			enemieslong[j].longmovement();
		}
		else if (enemieslong[j].follow)
		{
			longfollow();
			enemieslong[j].longmovement();
		}
		
	}
}

void Game::closefollow()
{
	for (int i = 0; i < enemiesclose.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesclose[i].follow)
		{
			if (abs(enemiesclose[i].trackclose.getPosition().x - posPX) >
				abs(enemiesclose[i].trackclose.getPosition().y - posPY))
			{
				if (enemiesclose[i].trackclose.getPosition().x > posPX)
				{
					enemiesclose[i].direction = 3;
				}
				if (enemiesclose[i].trackclose.getPosition().x < posPX)
				{
					enemiesclose[i].direction = 4;
				}
			}
			if (abs(enemiesclose[i].trackclose.getPosition().y - posPY) >
				abs(enemiesclose[i].trackclose.getPosition().x - posPX))
			{
				if (enemiesclose[i].trackclose.getPosition().y > posPY)
				{
					enemiesclose[i].direction = 1;
				}
				if (enemiesclose[i].trackclose.getPosition().y < posPY)
				{
					enemiesclose[i].direction = 2;
				}
			}
		}		
	}
}

void Game::longfollow()
{
	for (int i = 0; i < enemieslong.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemieslong[i].follow)
		{
			if (abs(enemieslong[i].tracklong.getPosition().x - posPX) >
				abs(enemieslong[i].tracklong.getPosition().y - posPY))
			{
				if (enemieslong[i].tracklong.getPosition().x > posPX)
				{
					enemieslong[i].direction = 3;
				}
				if (enemieslong[i].tracklong.getPosition().x < posPX)
				{
					enemieslong[i].direction = 4;
				}
			}
			if (abs(enemieslong[i].tracklong.getPosition().y - posPY) >
				abs(enemieslong[i].tracklong.getPosition().x - posPX))
			{
				if (enemieslong[i].tracklong.getPosition().y > posPY)
				{
					enemieslong[i].direction = 1;
				}
				if (enemieslong[i].tracklong.getPosition().y < posPY)
				{
					enemieslong[i].direction = 2;
				}
			}
		}
	}
}

void Game::alicefollow()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesalice[i].follow)
		{
			if (abs(enemiesalice[i].trackalice.getPosition().x - posPX) >
				abs(enemiesalice[i].trackalice.getPosition().y - posPY))
			{
				if (enemiesalice[i].trackalice.getPosition().x > posPX)
				{
					enemiesalice[i].direction = 3;
				}
				if (enemiesalice[i].trackalice.getPosition().x < posPX)
				{
					enemiesalice[i].direction = 4;
				}
			}
			if (abs(enemiesalice[i].trackalice.getPosition().y - posPY) >
				abs(enemiesalice[i].trackalice.getPosition().x - posPX))
			{
				if (enemiesalice[i].trackalice.getPosition().y > posPY)
				{
					enemiesalice[i].direction = 1;
				}
				if (enemiesalice[i].trackalice.getPosition().y < posPY)
				{
					enemiesalice[i].direction = 2;
				}
			}
		}
	}
}

void Game::doomfollow()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesdoom[i].follow)
		{
			if (abs(enemiesdoom[i].trackdoom.getPosition().x - posPX) >
				abs(enemiesdoom[i].trackdoom.getPosition().y - posPY))
			{
				if (enemiesdoom[i].trackdoom.getPosition().x > posPX)
				{
					enemiesdoom[i].direction = 3;
				}
				if (enemiesdoom[i].trackdoom.getPosition().x < posPX)
				{
					enemiesdoom[i].direction = 4;
				}
			}
			if (abs(enemiesdoom[i].trackdoom.getPosition().y - posPY) >
				abs(enemiesdoom[i].trackdoom.getPosition().x - posPX))
			{
				if (enemiesdoom[i].trackdoom.getPosition().y > posPY)
				{
					enemiesdoom[i].direction = 1;
				}
				if (enemiesdoom[i].trackdoom.getPosition().y < posPY)
				{
					enemiesdoom[i].direction = 2;
				}
			}
		}
	}
}

void Game::billiefollow()
{
	for (int i = 0; i < enemiesbillie.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesbillie[i].follow)
		{
			if (abs(enemiesbillie[i].trackbill.getPosition().x - posPX) >
				abs(enemiesbillie[i].trackbill.getPosition().y - posPY))
			{
				if (enemiesbillie[i].trackbill.getPosition().x > posPX)
				{
					enemiesbillie[i].direction = 3;
				}
				if (enemiesbillie[i].trackbill.getPosition().x < posPX)
				{
					enemiesbillie[i].direction = 4;
				}
			}
			if (abs(enemiesbillie[i].trackbill.getPosition().y - posPY) >
				abs(enemiesbillie[i].trackbill.getPosition().x - posPX))
			{
				if (enemiesbillie[i].trackbill.getPosition().y > posPY)
				{
					enemiesbillie[i].direction = 1;
				}
				if (enemiesbillie[i].trackbill.getPosition().y < posPY)
				{
					enemiesbillie[i].direction = 2;
				}
			}
		}
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
	bullethit();
	erasebullet();
	
}

void Game::erasebullet()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].btime >= bullets[i].bullettimemax)
		{
			bullets.erase(bullets.begin() + i);
			break;
		}		
		else { bullets[i].btime++; }
		
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
	bullethitbillie();
	enemiesbullet();
}



void Game::bullethitalice()
{
	if (bullets.empty()) {
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesalice.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesalice[j].trackalice.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesalice[j].alicehp -= player.damage;
				enemiesalice[j].follow = true;
				bullethits.play();
				break;
			}
			//OUT OF HP ENEMY DEAD
			
		}
	}
	//Delete enemy
	
}

void Game::bullethitdoom()
{
	if (bullets.empty() || enemiesdoom.empty()) {
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesdoom.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesdoom[j].trackdoom.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesdoom[j].doomhp -= player.damage;
				enemiesdoom[j].follow = true;
				bullethits.play();
				break;
			}
			
		}
	}
	
}

void Game::bullethitbillie()
{
	if (bullets.empty() || enemiesbillie.empty()) {
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesbillie.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesbillie[j].trackbill.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesbillie[j].billhp -= player.damage;
				enemiesbillie[j].follow = true;
				bullethits.play();
				break;
			}
			
		}
	}
	//Delete enemy
	
}

void Game::bullethitclose()
{
	if (bullets.empty()) {
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemiesclose.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemiesclose[j].trackclose.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemiesclose[j].closehp -= player.damage;
				enemiesclose[j].follow = true;
				bullethits.play();
				break;
			}
			
		}
	}
	//Delete enemy
	
}

void Game::bullethitlong()
{
	if (bullets.empty()) return;
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemieslong.size(); j++)
		{
			if (bullets[i].blink.getGlobalBounds().intersects(
				enemieslong[j].tracklong.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				enemieslong[j].longhp -= player.damage;
				enemieslong[j].follow = true;
				bullethits.play();
				break;
			}
			
		}
	}
	//Delete enemy
	
}

void Game::eraseenemy()
{
	//Delete enemy
	for (int j = 0; j < enemiesdoom.size(); j++)
	{
		//OUT OF HP ENEMY DEAD
		if (enemiesdoom[j].doomhp <= 0) 
		{
			enemiesdoom[j].alive = false;
			*scores += enemiesdoom[j].doomscore;
			allkillenemy++;
			player.tomhp++;
		}

		if (enemiesdoom[j].alive == false)
		{
			killdoom++;
			if (stage > 2)
			{
				killenemy++;
			}
			enemiesdoom.erase(enemiesdoom.begin() + j);
			kill.play();
			
		}
	}

	for (int j = 0; j < enemieslong.size(); j++)
	{
		//OUT OF HP ENEMY DEAD
		if (enemieslong[j].longhp <= 0)
		{ 
			enemieslong[j].alive = false;
			*scores += enemieslong[j].longscore;
			allkillenemy++;
			player.tomhp++;
		}
		if (enemieslong[j].alive == false)
		{
			enemieslong.erase(enemieslong.begin() + j);
			killenemy++;
			kill.play();
		}
	}

	for (int j = 0; j < enemiesclose.size(); j++)
	{
		//OUT OF HP ENEMY DEAD
		if (enemiesclose[j].closehp <= 0) 
		{ 
			enemiesclose[j].alive = false; 
			*scores += enemiesclose[j].closescore;
			allkillenemy++;
			player.tomhp++;
		}
		if (enemiesclose[j].alive == false)
		{
			enemiesclose.erase(enemiesclose.begin() + j);
			killenemy++;
			kill.play();
		}
	}

	for (int j = 0; j < enemiesbillie.size(); j++)
	{
		//OUT OF HP ENEMY DEAD
		if (enemiesbillie[j].billhp <= 0)
		{ 
			enemiesbillie[j].alive = false; 
			*scores += enemiesbillie[j].billscore;
			allkillenemy++;
			player.tomhp++;
		}
		if (enemiesbillie[j].alive == false)
		{
			killbillie++;
			enemiesbillie.erase(enemiesbillie.begin() + j);
			kill.play();
		}
	}

	for (int j = 0; j < enemiesalice.size(); j++)
	{
		if (enemiesalice[j].alicehp <= 0)
		{
			enemiesalice[j].alive = false;
			*scores += enemiesalice[j].alicescore;
			allkillenemy++;
			player.tomhp++;
		}
		if (enemiesalice[j].alive == false)
		{
			enemiesalice.erase(enemiesalice.begin() + j);
			if (stage > 1)
			{
				killenemy++;
			}
			killalice++;
			kill.play();
		}
	}
}





//====================================================
//ENEMIES BULLET
void Game::enemiesbullet()
{
	bulletalice();
	bulletdoom();
	bulletbill();
	bulletlong();
}

void Game::bulletalice()
{
	updatealicebullet();
	alicebullethit();
}

void Game::bulletdoom()
{
	updatedoombullet();
	doombullethit();
}

void Game::bulletbill()
{
	updatebillbullet();
	billbullethit();
}


void Game::bulletlong()
{
	updatelongbullet();
	longbullethit();
}

//SPAWN AND MOVEMENT BULLET
void Game::updatealicebullet()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesalice[i].follow)
		{
			if (delaybullet >= 150)
			{							
				if (abs(enemiesalice[i].trackalice.getPosition().x - posPX) <= 500
					&& abs(enemiesalice[i].trackalice.getPosition().y - posPY) <= 100)
				{
					delaybullet = 0;
					if (enemiesalice[i].trackalice.getPosition().x > posPX)
					{
						enemybullet.bulletdirection = 3;
						enemybullet.alicebullet.setTexture(alicetexture);
						enemybullet.alicebullet.setPosition(Vector2f(
							enemiesalice[i].trackalice.getPosition().x - 20,
							enemiesalice[i].trackalice.getPosition().y));
						aliceb.push_back(enemybullet);
					}
					if (enemiesalice[i].trackalice.getPosition().x < posPX)
						{
							enemybullet.bulletdirection = 4;
							enemybullet.alicebullet.setTexture(alicetexture);
							enemybullet.alicebullet.setPosition(Vector2f(
								enemiesalice[i].trackalice.getPosition().x + 20,
								enemiesalice[i].trackalice.getPosition().y));
							aliceb.push_back(enemybullet);
						}
				}

				if (abs(enemiesalice[i].trackalice.getPosition().y - posPY) <= 500
					&& abs(enemiesalice[i].trackalice.getPosition().x - posPX) <= 100)
					{
						delaybullet = 0;
						if (enemiesalice[i].trackalice.getPosition().y > posPY)
						{
							enemybullet.bulletdirection = 1;
							enemybullet.alicebullet.setTexture(alicetexture);
							enemybullet.alicebullet.setPosition(Vector2f(
								enemiesalice[i].trackalice.getPosition().x,
								enemiesalice[i].trackalice.getPosition().y - 20));
							aliceb.push_back(enemybullet);
						}
						if (enemiesalice[i].trackalice.getPosition().y < posPY)
						{
							enemybullet.bulletdirection = 2;
							enemybullet.alicebullet.setTexture(alicetexture);
							enemybullet.alicebullet.setPosition(Vector2f(
								enemiesalice[i].trackalice.getPosition().x,
								enemiesalice[i].trackalice.getPosition().y + 20));
							aliceb.push_back(enemybullet);
						}
					}
				
			}
			else delaybullet++;
		}
	}

}

void Game::alicebullethit()
{
	if (aliceb.empty()) return;
	//Bullet hit player
	for (int j = 0; j < aliceb.size(); j++)
	{
		if (aliceb[j].bullettime < bossbullettime)
		{
			aliceb[j].bullettime++;
			aliceb[j].updateBalice();
			if (aliceb[j].alicebullet.getGlobalBounds().intersects
			(player.track.getGlobalBounds()))
			{
				getdamage = true;
				player.tomhp -= aliceb[j].aliceD;
				aliceb.erase(aliceb.begin() + j);
				break;
			}
		}
		else
		{
			aliceb.erase(aliceb.begin() + j);
			break;
		}
	}

	//Bullet hit frame
	for (int i = 0; i < aliceb.size(); i++)
	{
		if (aliceb[i].alicebullet.getGlobalBounds().intersects(
			map.fmap1.getGlobalBounds()))
		{
			aliceb.erase(aliceb.begin() + i);
			break;
		}
		if (aliceb[i].alicebullet.getGlobalBounds().intersects(
			map.fmap2.getGlobalBounds()))
		{
			aliceb.erase(aliceb.begin() + i);
			break;
		}
		if (aliceb[i].alicebullet.getGlobalBounds().intersects(
			map.fmap3.getGlobalBounds()))
		{
			aliceb.erase(aliceb.begin() + i);
			break;
		}
		if (aliceb[i].alicebullet.getGlobalBounds().intersects(
			map.fmap4.getGlobalBounds()))
		{
			aliceb.erase(aliceb.begin() + i);
			break;
		}
	}

}

void Game::updatedoombullet()
{
	for (int i = 0; i < enemiesdoom.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesdoom[i].follow)
		{
			if (delaybullet >= 150)
			{
				if (abs(enemiesdoom[i].trackdoom.getPosition().x - posPX) <= 500
					&& abs(enemiesdoom[i].trackdoom.getPosition().y - posPY) <= 100)
				{
					delaybullet = 0;
					if (enemiesdoom[i].trackdoom.getPosition().x > posPX)
					{
						enemybullet.bulletdirection = 3;
						enemybullet.doombullet.setTexture(doomtexture);
						enemybullet.doombullet.setPosition(Vector2f(
							enemiesdoom[i].trackdoom.getPosition().x - 20,
							enemiesdoom[i].trackdoom.getPosition().y));
						doomb.push_back(enemybullet);
					}
					if (enemiesdoom[i].trackdoom.getPosition().x < posPX)
					{
						enemybullet.bulletdirection = 4;
						enemybullet.doombullet.setTexture(doomtexture);
						enemybullet.doombullet.setPosition(Vector2f(
							enemiesdoom[i].trackdoom.getPosition().x + 20,
							enemiesdoom[i].trackdoom.getPosition().y));
						doomb.push_back(enemybullet);
					}
				}

				if (abs(enemiesdoom[i].trackdoom.getPosition().y - posPY) <= 500
					&& abs(enemiesdoom[i].trackdoom.getPosition().x - posPX) <= 100)
				{
					delaybullet = 0;
					if (enemiesdoom[i].trackdoom.getPosition().y > posPY)
					{
						enemybullet.bulletdirection = 1;
						enemybullet.doombullet.setTexture(doomtexture);
						enemybullet.doombullet.setPosition(Vector2f(
							enemiesdoom[i].trackdoom.getPosition().x,
							enemiesdoom[i].trackdoom.getPosition().y - 20));
						doomb.push_back(enemybullet);
					}
					if (enemiesdoom[i].trackdoom.getPosition().y < posPY)
					{
						enemybullet.bulletdirection = 2;
						enemybullet.doombullet.setTexture(doomtexture);
						enemybullet.doombullet.setPosition(Vector2f(
							enemiesdoom[i].trackdoom.getPosition().x,
							enemiesdoom[i].trackdoom.getPosition().y + 20));
						doomb.push_back(enemybullet);
					}
				}

			}
			else delaybullet++;
		}
	}
}

void Game::doombullethit()
{
	if (doomb.empty()) {
		return;
	}
	//Bullet hit player
	for (int j = 0; j < doomb.size(); j++)
	{
		if (doomb[j].bullettime < bossbullettime)
		{
			doomb[j].bullettime++;
			doomb[j].updateBdoom();
			if (doomb[j].doombullet.getGlobalBounds().intersects
			(player.track.getGlobalBounds()))
			{
				getdamage = true;
				player.tomhp -= doomb[j].doomD;
				doomb.erase(doomb.begin() + j);
				break;
			}
		}
		else
		{
			doomb.erase(doomb.begin() + j);
			break;
		}
	}

	//Bullet hit frame
	for (int i = 0; i < doomb.size(); i++)
	{
		if (doomb[i].doombullet.getGlobalBounds().intersects(
			map.fmap1.getGlobalBounds()))
		{
			doomb.erase(doomb.begin() + i);
			break;
		}
		if (doomb[i].doombullet.getGlobalBounds().intersects(
			map.fmap2.getGlobalBounds()))
		{
			doomb.erase(doomb.begin() + i);
			break;
		}
		if (doomb[i].doombullet.getGlobalBounds().intersects(
			map.fmap3.getGlobalBounds()))
		{
			doomb.erase(doomb.begin() + i);
			break;
		}
		if (doomb[i].doombullet.getGlobalBounds().intersects(
			map.fmap4.getGlobalBounds()))
		{
			doomb.erase(doomb.begin() + i);
			break;
		}
	}
}

void Game::updatebillbullet()
{
	for (int i = 0; i < enemiesbillie.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemiesbillie[i].follow)
		{
			if (delaybullet >= 120)
			{
				if (abs(enemiesbillie[i].trackbill.getPosition().x - posPX) <= 800
					&& abs(enemiesbillie[i].trackbill.getPosition().y - posPY) <= 150)
				{
					delaybullet = 0;
					if (enemiesbillie[i].trackbill.getPosition().x > posPX)
					{
						enemybullet.bulletdirection = 3;
						enemybullet.billbullet.setTexture(billtexture);
						enemybullet.billbullet.setPosition(Vector2f(
							enemiesbillie[i].trackbill.getPosition().x - 20,
							enemiesbillie[i].trackbill.getPosition().y));
						billb.push_back(enemybullet);
					}
					if (enemiesbillie[i].trackbill.getPosition().x < posPX)
					{
						enemybullet.bulletdirection = 4;
						enemybullet.billbullet.setTexture(billtexture);
						enemybullet.billbullet.setPosition(Vector2f(
							enemiesbillie[i].trackbill.getPosition().x + 20,
							enemiesbillie[i].trackbill.getPosition().y));
						billb.push_back(enemybullet);
					}
				}

				if (abs(enemiesbillie[i].trackbill.getPosition().y - posPY) <= 800
					&& abs(enemiesbillie[i].trackbill.getPosition().x - posPX) <= 150)
				{
					delaybullet = 0;
					if (enemiesbillie[i].trackbill.getPosition().y > posPY)
					{
						enemybullet.bulletdirection = 1;
						enemybullet.billbullet.setTexture(billtexture);
						enemybullet.billbullet.setPosition(Vector2f(
							enemiesbillie[i].trackbill.getPosition().x,
							enemiesbillie[i].trackbill.getPosition().y - 20));
						billb.push_back(enemybullet);
					}
					if (enemiesbillie[i].trackbill.getPosition().y < posPY)
					{
						enemybullet.bulletdirection = 2;
						enemybullet.billbullet.setTexture(billtexture);
						enemybullet.billbullet.setPosition(Vector2f(
							enemiesbillie[i].trackbill.getPosition().x,
							enemiesbillie[i].trackbill.getPosition().y + 20));
						billb.push_back(enemybullet);
					}
				}

			}
			else delaybullet++;
		}
	}
}

void Game::billbullethit()
{
	if (billb.empty()) return;
	//Bullet hit player
	for (int j = 0; j < billb.size(); j++)
	{
		if (billb[j].bullettime < bossbullettime)
		{
			billb[j].bullettime++;
			billb[j].updateBbill();
			if (billb[j].billbullet.getGlobalBounds().intersects
			(player.track.getGlobalBounds()))
			{
				getdamage = true;
				player.tomhp -= billb[j].billD;
				billb.erase(billb.begin() + j);
				break;
			}
		}
		else
		{
			billb.erase(billb.begin() + j);
			break;
		}
	}

	//Bullet hit frame
	for (int i = 0; i < billb.size(); i++)
	{
		if (billb[i].billbullet.getGlobalBounds().intersects(
			map.fmap1.getGlobalBounds()))
		{
			billb.erase(billb.begin() + i);
			break;
		}
		if (billb[i].billbullet.getGlobalBounds().intersects(
			map.fmap2.getGlobalBounds()))
		{
			billb.erase(billb.begin() + i);
			break;
		}
		if (billb[i].billbullet.getGlobalBounds().intersects(
			map.fmap3.getGlobalBounds()))
		{
			billb.erase(billb.begin() + i);
			break;
		}
		if (billb[i].billbullet.getGlobalBounds().intersects(
			map.fmap4.getGlobalBounds()))
		{
			billb.erase(billb.begin() + i);
			break;
		}
	}
}

void Game::updatelongbullet()
{
	for (int i = 0; i < enemieslong.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (enemieslong[i].follow)
		{
			if (delaybullet >= 200)
			{
				if (abs(enemieslong[i].tracklong.getPosition().x - posPX) <= 700
					&& abs(enemieslong[i].tracklong.getPosition().y - posPY) <= 50)
				{
					delaybullet = 0;
					if (enemieslong[i].tracklong.getPosition().x > posPX)
					{
						enemybullet.bulletdirection = 3;
						enemybullet.longbullet.setTexture(longtexture);
						enemybullet.longbullet.setPosition(Vector2f(
							enemieslong[i].tracklong.getPosition().x - 20,
							enemieslong[i].tracklong.getPosition().y));
						longb.push_back(enemybullet);
					}
					if (enemieslong[i].tracklong.getPosition().x < posPX)
					{
						enemybullet.bulletdirection = 4;
						enemybullet.longbullet.setTexture(longtexture);
						enemybullet.longbullet.setPosition(Vector2f(
							enemieslong[i].tracklong.getPosition().x + 20,
							enemieslong[i].tracklong.getPosition().y));
						longb.push_back(enemybullet);
					}
				}

				if (abs(enemieslong[i].tracklong.getPosition().y - posPY) <= 700
					&& abs(enemieslong[i].tracklong.getPosition().x - posPX) <= 50)
				{
					delaybullet = 0;
					if (enemieslong[i].tracklong.getPosition().y > posPY)
					{
						enemybullet.bulletdirection = 1;
						enemybullet.longbullet.setTexture(longtexture);
						enemybullet.longbullet.setPosition(Vector2f(
							enemieslong[i].tracklong.getPosition().x,
							enemieslong[i].tracklong.getPosition().y - 20));
						longb.push_back(enemybullet);
					}
					if (enemieslong[i].tracklong.getPosition().y < posPY)
					{
						enemybullet.bulletdirection = 2;
						enemybullet.longbullet.setTexture(longtexture);
						enemybullet.longbullet.setPosition(Vector2f(
							enemieslong[i].tracklong.getPosition().x,
							enemieslong[i].tracklong.getPosition().y + 20));
						longb.push_back(enemybullet);
					}
				}

			}
			else delaybullet++;
		}
	}
}

void Game::longbullethit()
{
	if (longb.empty()) return;
	//Bullet hit player
	for (int j = 0; j < longb.size(); j++)
	{
		if (longb[j].bullettime < normalbullettime)
		{
			longb[j].bullettime++;
			longb[j].updateBlong();
			if (longb[j].longbullet.getGlobalBounds().intersects
			(player.track.getGlobalBounds()))
			{
				getdamage = true;
				player.tomhp -= longb[j].longD;
				longb[j].longf++;
				longb.erase(longb.begin() + j);
				break;
			}
		}
		else
		{
			longb[j].longf++;
			longb.erase(longb.begin() + j);
			break;
		}
	}

	//Bullet hit frame
	for (int i = 0; i < longb.size(); i++)
	{
		/*if (!longb.empty()) {
			break;
		}*/
		if (longb[i].longbullet.getGlobalBounds().intersects(
			map.fmap1.getGlobalBounds()))
		{
			longb.erase(longb.begin() + i);
			break;
		}
		if (longb[i].longbullet.getGlobalBounds().intersects(
			map.fmap2.getGlobalBounds()))
		{
			longb.erase(longb.begin() + i);
			break;
		}
		if (longb[i].longbullet.getGlobalBounds().intersects(
			map.fmap3.getGlobalBounds()))
		{
			longb.erase(longb.begin() + i);
			break;
		}
		if (longb[i].longbullet.getGlobalBounds().intersects(
			map.fmap4.getGlobalBounds()))
		{
			longb.erase(longb.begin() + i);
			break;
		}
	}
}

//=================================================




//======================================
//        PLAYER BOUNCE ENEMIES
//======================================

void Game::playerhitenemy()
{
	playerhitalice();
	playerhitdoom();
	playerhitclose();
	playerhitlong();
	playerhitbilie();
}

void Game::playerhitalice()
{
	for (int i = 0; i < enemiesalice.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemiesalice[i].trackalice.getGlobalBounds()))
		{
			getdamage = true;
			hit.play();
			if (abs(enemiesalice[i].trackalice.getPosition().x - posPX) >
				abs(enemiesalice[i].trackalice.getPosition().y - posPY))
			{
				if (enemiesalice[i].trackalice.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemiesalice[i].trackalice.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
					player.tomhp--;
					break;
				}
				if (enemiesalice[i].trackalice.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
			getdamage = true;
			hit.play();
			if (abs(enemiesdoom[i].trackdoom.getPosition().x - posPX) >
				abs(enemiesdoom[i].trackdoom.getPosition().y - posPY))
			{
				if (enemiesdoom[i].trackdoom.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemiesdoom[i].trackdoom.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
					player.tomhp--;
					break;
				}
				if (enemiesdoom[i].trackdoom.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
			}
		}
	}
}

void Game::playerhitbilie()
{
	for (int i = 0; i < enemiesbillie.size(); i++)
	{
		posPX = player.track.getPosition().x;
		posPY = player.track.getPosition().y;
		if (player.track.getGlobalBounds().intersects(enemiesbillie[i].trackbill.getGlobalBounds()))
		{
			getdamage = true;
			hit.play();
			if (abs(enemiesbillie[i].trackbill.getPosition().x - posPX) >
				abs(enemiesbillie[i].trackbill.getPosition().y - posPY))
			{
				if (enemiesbillie[i].trackbill.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemiesbillie[i].trackbill.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
			}

			if (abs(enemiesbillie[i].trackbill.getPosition().y - posPY) >
				abs(enemiesbillie[i].trackbill.getPosition().x - posPX))
			{
				if (enemiesbillie[i].trackbill.getPosition().y > posPY)
				{
					player.track.setPosition(posPX, posPY - 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemiesbillie[i].trackbill.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
			getdamage = true;
			hit.play();
			if (abs(enemiesclose[i].trackclose.getPosition().x - posPX) >
				abs(enemiesclose[i].trackclose.getPosition().y - posPY))
			{
				if (enemiesclose[i].trackclose.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemiesclose[i].trackclose.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
					player.tomhp--;
					break;
				}
				if (enemiesclose[i].trackclose.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
			getdamage = true;
			hit.play();
			if (abs(enemieslong[i].tracklong.getPosition().x - posPX) >
				abs(enemieslong[i].tracklong.getPosition().y - posPY))
			{
				if (enemieslong[i].tracklong.getPosition().x > posPX)
				{
					player.track.setPosition(posPX - 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
					break;
				}
				if (enemieslong[i].tracklong.getPosition().x < posPX)
				{
					player.track.setPosition(posPX + 50, posPY);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
					player.tomhp--;
					break;
				}
				if (enemieslong[i].tracklong.getPosition().y < posPY)
				{
					player.track.setPosition(posPX, posPY + 50);
					player.Tom.setPosition(player.track.getPosition());
					player.tomhp--;
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
	billiehitframe();
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

void Game::billiehitframe()
{
	for (int i = 0; i < enemiesbillie.size(); i++)
	{
		if (enemiesbillie[i].trackbill.getGlobalBounds().intersects(map.fmap1.getGlobalBounds()))
		{
			enemiesbillie[i].trackbill.setPosition(enemiesbillie[i].trackbill.getPosition().x + 10, enemiesbillie[i].trackbill.getPosition().y);
			enemiesbillie[i].direction = generateRandom(4);
			break;
		}
		if (enemiesbillie[i].trackbill.getGlobalBounds().intersects(map.fmap2.getGlobalBounds()))
		{
			enemiesbillie[i].trackbill.setPosition(enemiesbillie[i].trackbill.getPosition().x - 10, enemiesbillie[i].trackbill.getPosition().y);
			enemiesbillie[i].direction = generateRandom(4);
			break;
		}
		if (enemiesbillie[i].trackbill.getGlobalBounds().intersects(map.fmap3.getGlobalBounds()))
		{
			enemiesbillie[i].trackbill.setPosition(enemiesbillie[i].trackbill.getPosition().x, enemiesbillie[i].trackbill.getPosition().y - 10);
			enemiesbillie[i].direction = generateRandom(4);
			break;
		}
		if (enemiesbillie[i].trackbill.getGlobalBounds().intersects(map.fmap4.getGlobalBounds()))
		{
			enemiesbillie[i].trackbill.setPosition(enemiesbillie[i].trackbill.getPosition().x, enemiesbillie[i].trackbill.getPosition().y + 10);
			enemiesbillie[i].direction = generateRandom(4);
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
		if (bullets.empty()) {
			break;
		}
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
	if (!pause)
	{
		//Player Update
		player.update(); //Player Movement
		if (player.tomhp >= player.tommaxhp) { player.tomhp = player.tommaxhp; }
		updateui();
		hpboxupdate();
		upgrade();
		//Enemy Update	
		updateEnemies(); //Movement And Spawn Enemy Collision

		//Bullets Update
		updatebullet(); //Bullets Movement Bullets Hit Enemies	 Enemies bullets
		firebullet(); //Firing Pressed

		//Collision Frame
		framebound();

		updatelowhp();

		//GAME UPDATE
		playerhitenemy(); //Player collision
		stagechange();
	}
	else updatepause();


	endgame();

}