#include "Enemy.h"

Enemy::Enemy() : track(), alicetexture(), alice(), 
				 alicef(), aliceX(), aliceY(), changeDirectionTime(300)
{
	alicetexture.loadFromFile("characters/Alice.png");

	aliceX = alicetexture.getSize().x / 8.07;
	aliceY = alicetexture.getSize().x / 4.58;

	alice.setTexture(alicetexture);
	alice.setTextureRect(
		IntRect(0, aliceY*1, aliceX, aliceY));
	alice.setScale(5, 5);
	alice.setOrigin(Vector2f(aliceX/2, aliceY/2));
	//Tracking Object
	track.setSize(Vector2f(aliceX, aliceY));
	track.setFillColor(Color::Transparent);
	track.setOutlineColor(Color::Green);
	track.setScale(4,4);
	track.setOutlineThickness(1);
	track.setOrigin(Vector2f(aliceX/2, aliceY/2));

	alice.setPosition(track.getPosition());
	movement();
}

int Enemy::generateRandom(int max)
{
	int randomnumber = rand();
	float random = (randomnumber % max) + 1;
	int myrandom = random;

	return myrandom;
}

void Enemy::movement()
{
	// 1 = UP, 2 = DOWN, 3 = LEFT, 4 = RIGHT
	
	if(direction == 1) //UP
	{
		track.move(0, -aliceS);
		alice.setTextureRect(
			IntRect(aliceX * alicef, 0, aliceX, aliceY));		
	}
	else if (direction == 2) //DOWN
	{
		track.move(0, aliceS);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY, aliceX, aliceY));
	
	}
	else if (direction == 3) //LEFT
	{
		track.move(-aliceS, 0);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY * 3, aliceX, aliceY));
	}
	else if (direction == 4) //RIGHT
	{
		track.move(aliceS, 0);
		alice.setTextureRect(
			IntRect(aliceX * alicef, aliceY * 2, aliceX, aliceY));
	}
	alice.setPosition(track.getPosition());
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
