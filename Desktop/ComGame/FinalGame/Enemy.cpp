#include "Enemy.h"

Enemy::Enemy() : trackalice(), alicetexture(), alice(), 
				 alicef(), aliceX(), aliceY(), changeDirectionTime(300)
{
	//=================
	
	initalice();   //BOSS1
	initdoom();    //BOSS2
	initclose();   //ENEMY1
	initlong();	   //ENEMY2
	initbill();    //BOSS3
}

int Enemy::generateRandom(int max)
{
	int randomnumber = rand();
	float random = (randomnumber % max) + 1;
	int myrandom = random;

	return myrandom;
}

void Enemy::initalice()
{
	//=====================
	//       BOSS 1
	//=====================
	alicetexture.loadFromFile("characters/Alice.png");

	aliceX = alicetexture.getSize().x / 8.0;
	aliceY = alicetexture.getSize().y / 4;

	alice.setTexture(alicetexture);
	alice.setTextureRect(
		IntRect(0, aliceY * 1, aliceX, aliceY));
	alice.setScale(2.8, 2.8);
	alice.setOrigin(Vector2f(aliceX / 2, aliceY / 2));

	//Tracking Object
	trackalice.setSize(Vector2f(aliceX, aliceY));
	trackalice.setFillColor(Color::Transparent);
	trackalice.setOutlineColor(Color::Green);
	trackalice.setScale(2, 2);
	trackalice.setOutlineThickness(1);
	trackalice.setOrigin(Vector2f(aliceX / 2, aliceY / 2));

	alice.setPosition(trackalice.getPosition());
}

void Enemy::initdoom()
{
	//==============
	//     BOSS2
	//==============
	doomtexture.loadFromFile("characters/Doom.png");

	doomX = doomtexture.getSize().x / 8;
	doomY = doomtexture.getSize().y / 4;

	doom.setTexture(doomtexture);
	doom.setTextureRect(
		IntRect(0, 0, doomX, doomY));
	doom.setScale( 1, 1);
	doom.setOrigin(Vector2f(doomX / 2, doomY / 2));

	//Tracking Object
	trackdoom.setSize(Vector2f(doomX, doomY));
	trackdoom.setFillColor(Color::Transparent);
	trackdoom.setOutlineColor(Color::Green);
	trackdoom.setScale(1, 1);
	trackdoom.setOutlineThickness(1);
	trackdoom.setOrigin(Vector2f(doomX / 2, doomY / 2));

	doom.setPosition(trackdoom.getPosition());
}

void Enemy::initclose()
{
	//===================
	//      CLOSE
	//===================
	closetexture.loadFromFile("characters/close.png");

	closeX = closetexture.getSize().x / 4.0;
	closeY = closetexture.getSize().y / 3.85;

	closeenemy.setTexture(closetexture);
	closeenemy.setTextureRect(IntRect
	(0, 0, closeX, closeY));
	closeenemy.setScale(3, 3);
	closeenemy.setOrigin(Vector2f(closeX/2, closeY/2));

	trackclose.setSize(Vector2f(closeX, closeY));
	trackclose.setFillColor(Color::Transparent);
	trackclose.setOutlineColor(Color::Green);
	trackclose.setScale(3, 3);
	trackclose.setOrigin(Vector2f(closeX / 2, closeY / 2));
	trackclose.setOutlineThickness(1);
	

	closeenemy.setPosition(trackclose.getPosition());
}

void Enemy::initlong()
{
	//===================
	//      LONG
	//===================
	longtexture.loadFromFile("characters/long.png");

	longX = longtexture.getSize().x / 4.95;
	longY = longtexture.getSize().y / 3.95;

	longenemy.setTexture(longtexture);
	longenemy.setTextureRect(IntRect
	(0, 0, longX, longY));
	longenemy.setScale(3, 3);
	longenemy.setOrigin(Vector2f(longX / 2, longY / 2));

	tracklong.setSize(Vector2f(longX, longY));
	tracklong.setOrigin(longX / 2, longY / 2);
	tracklong.setFillColor(Color::Transparent);
	tracklong.setOutlineColor(Color::Green);
	tracklong.setOutlineThickness(1);
	tracklong.setScale(3, 3);


	longenemy.setPosition(tracklong.getPosition());
}

void Enemy::initbill()
{
	//===================
	//      BOSS 3
	//===================
	billietexture.loadFromFile("characters/bill.png");

	billX = billietexture.getSize().x;
	billY = billietexture.getSize().y;

	billie.setTexture(billietexture);
	billie.setTextureRect(IntRect
	(0, 0, billX, billY));
	billie.setScale(3, 3);
	billie.setOrigin(Vector2f(billX / 2, billY / 2));

	trackbill.setSize(Vector2f(billX, billY));
	trackbill.setOrigin(billX / 2, billY / 2);
	trackbill.setFillColor(Color::Transparent);
	trackbill.setOutlineColor(Color::Green);
	trackbill.setOutlineThickness(1);
	trackbill.setScale(3, 3);


	billie.setPosition(trackbill.getPosition());
}

void Enemy::movement()
{
	// 1 = UP, 2 = DOWN, 3 = LEFT, 4 = RIGHT
	alicemovement();
	
}

void Enemy::alicemovement()
{
	if (direction == 1) //UP
	{
		trackalice.move(0, -aliceS);
		alice.setTextureRect(
			IntRect(aliceX * alicef, 0, aliceX, aliceY));
	}
	else if (direction == 2) //DOWN
	{
		trackalice.move(0, aliceS);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY, aliceX, aliceY));

	}
	else if (direction == 3) //LEFT
	{
		trackalice.move(-aliceS, 0);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY * 3, aliceX, aliceY));
	}
	else if (direction == 4) //RIGHT
	{
		trackalice.move(aliceS, 0);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY * 2, aliceX, aliceY));
	}
	alice.setPosition(trackalice.getPosition());
	if (ftime > 10)
	{
		alicef++;
		ftime = 0;
	}
	else ftime++;

	if (changeDirectionTime >= 250)
	{
		direction = generateRandom(4);
		changeDirectionTime = 0;
	}
	else changeDirectionTime++;


	if (alicef == 8)
	{
		alicef = 0;
	}
}

void Enemy::doommovement()
{
	if (direction == 1) //UP
	{
		trackdoom.move(0, -aliceS);
		doom.setTextureRect(
			IntRect(doomX * doomf, doomY * 2, doomX, doomY));
	}
	else if (direction == 2) //DOWN
	{
		trackdoom.move(0, aliceS);
		doom.setTextureRect(
			IntRect(doomX * doomf, 0, doomX, doomY));

	}
	else if (direction == 3) //LEFT
	{
		trackdoom.move(-aliceS, 0);
		doom.setTextureRect(
			IntRect(doomX * doomf, doomY , doomX, doomY));
	}
	else if (direction == 4) //RIGHT
	{
		trackdoom.move(aliceS, 0);
		doom.setTextureRect(
			IntRect(doomX * doomf, doomY * 3, doomX, doomY));
	}
	doom.setPosition(trackdoom.getPosition());
	if (ftime > 10)
	{
		doomf++;
		ftime = 0;
	}
	else ftime++;

	if (changeDirectionTime >= 250)
	{
		direction = generateRandom(4);
		changeDirectionTime = 0;
	}
	else changeDirectionTime++;


	if (doomf == 7)
	{
		doomf = 0;
	}
}

void Enemy::closemovement()
{
	if (direction == 1) //UP
	{
		trackclose.move(0, -closeS);
		closeenemy.setTextureRect(
			IntRect(closeX * closef, closeY, closeX, closeY));
	}
	else if (direction == 2) //DOWN
	{
		trackclose.move(0, closeS);
		closeenemy.setTextureRect(
			IntRect(closeX * closef, 0, closeX, closeY));

	}
	else if (direction == 3) //LEFT
	{
		trackclose.move(-closeS, 0);
		closeenemy.setTextureRect(
			IntRect(closeX * closef, closeY * 2, closeX, closeY));
	}
	else if (direction == 4) //RIGHT
	{
		trackclose.move(closeS, 0);
		closeenemy.setTextureRect(
			IntRect(closeX * closef, closeY * 3, closeX, closeY));
	}
	closeenemy.setPosition(trackclose.getPosition());
	
	if (ftime > 10)
	{
		closef++;
		ftime = 0;
	}
	else ftime++;

	if (!follow)
	{
		if (changeDirectionTime >= 250)
		{
			direction = generateRandom(4);
			changeDirectionTime = 0;
		}
		else changeDirectionTime++;
	}
		


	if (closef == 4)
	{
		closef = 0;
	}
}

void Enemy::longmovement()
{
	if (direction == 1) //UP
	{
		tracklong.move(0, -longS);
		longenemy.setTextureRect(
			IntRect(longX * longf, longY * 2, longX, longY));
	}
	else if (direction == 2) //DOWN
	{
		tracklong.move(0, longS);
		longenemy.setTextureRect(
			IntRect(longX * longf, 0, longX, longY));

	}
	else if (direction == 3) //LEFT
	{
		tracklong.move(-longS, 0);
		longenemy.setTextureRect(
			IntRect(longX * longf, longY * 3, longX, longY));
	}
	else if (direction == 4) //RIGHT
	{
		tracklong.move(longS, 0);
		longenemy.setTextureRect(
			IntRect(longX * longf, longY, longX, longY));
	}
	longenemy.setPosition(tracklong.getPosition());
	if (ftime > 10)
	{
		longf++;
		ftime = 0;
	}
	else ftime++;

	if (changeDirectionTime >= 250)
	{
		direction = generateRandom(4);
		changeDirectionTime = 0;
	}
	else changeDirectionTime++;


	if (longf == 5)
	{
		longf = 0;
	}
}

void Enemy::billmovement()
{
	if (direction == 1) //UP
	{
		trackbill.move(0, -billS);
		billie.setTextureRect(
			IntRect(billX * billief, billY, billX, billY));
	}
	else if (direction == 2) //DOWN
	{
		trackbill.move(0, billS);
		billie.setTextureRect(
			IntRect(billX * billief, 0, billX, billY));

	}
	else if (direction == 3) //LEFT
	{
		trackbill.move(-billS, 0);
		billie.setTextureRect(
			IntRect(billX * billief, billY * 2, billX, billY));
	}
	else if (direction == 4) //RIGHT
	{
		trackbill.move(billS, 0);
		billie.setTextureRect(
			IntRect(billX * billief, billY * 3, billX, billY));
	}
	billie.setPosition(trackbill.getPosition());

	if (ftime > 10)
	{
		billief++;
		ftime = 0;
	}
	else ftime++;

	if (!follow)
	{
		if (changeDirectionTime >= 250)
		{
			direction = generateRandom(4);
			changeDirectionTime = 0;
		}
		else changeDirectionTime++;
	}



	if (billief == 4)
	{
		billief = 0;
	}
}
