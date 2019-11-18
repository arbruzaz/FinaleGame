#include "Player.h"

Player::Player() : Tom(), tomtexture(), track()
{

	//=====================================
	//              PLAYER 1 TOM
	//=====================================
	
	//Texture Stuff
	tomtexture.loadFromFile("characters/Tom.png");
	guitar.loadFromFile("characters/guitar.png");
	gunX = guitar.getSize().x;
	gunY = guitar.getSize().y/4;
	gun.setTexture(guitar);
	gun.setScale(0.1, 0.1);

	gun.setTextureRect(IntRect(gunX, gunY, gunX, gunY));
	gun.setOrigin(gunX / 2, gunY / 2);

	gun.setPosition(
		track.getPosition().x,
		track.getPosition().y + 50
	);
	tomSizeX = tomtexture.getSize().x / 3;
	tomSizeY = tomtexture.getSize().y / 3;

	Tom.setTexture(tomtexture);
	Tom.setTextureRect(
		IntRect(0, 0, tomSizeX, tomSizeY));

	Tom.setScale(0.03, 0.03);
	Tom.setOrigin(Vector2f(tomSizeX / 2, tomSizeY / 2));
	//DescribePlayer



	//=============================
	//      Tracking Object
	//=============================
	track.setSize(Vector2f(tomSizeX, tomSizeY));
	track.setScale(0.03, 0.03);
	track.setFillColor(Color::Transparent);
	track.setOutlineColor(Color::Green);
	track.setOutlineThickness(100);
	track.setOrigin(Vector2f(tomSizeX / 2, tomSizeY / 2));
	
	
}

void Player::updateTom()
{

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction = 1;
		track.move(0.f, -tomspeed);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, tomSizeY * 2, tomSizeX, tomSizeY));
	
		gun.setPosition(
			track.getPosition().x,
			track.getPosition().y - 70
		);
		gun.setTextureRect(IntRect(0, 0, gunX, gunY));
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction = 2;
		track.move(0.f, tomspeed);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, tomSizeY * 2, tomSizeX, tomSizeY));
		
		gun.setPosition(
			track.getPosition().x,
			track.getPosition().y + 70
		);
		gun.setTextureRect(IntRect(0, gunY, gunX, gunY));
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = 3;
		track.move(-tomspeed, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, tomSizeY * 1, tomSizeX, tomSizeY));
		
		gun.setPosition(
			track.getPosition().x - 60,
			track.getPosition().y
		);
		gun.setTextureRect(IntRect(0, gunY * 3, gunX, gunY));
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = 4;
		track.move(tomspeed, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, 0, tomSizeX, tomSizeY));
		
		gun.setPosition(
			track.getPosition().x + 60,
			track.getPosition().y
		);
		gun.setTextureRect(IntRect(0, gunY * 2, gunX, gunY));
	}
	if (ftime > 10)
	{
		animationFrame++;
		ftime = 0;
	}
	else ftime++;

	
	if (animationFrame >= 3)
		animationFrame = 0;
}

void Player::update()
{
	updateTom();
}

