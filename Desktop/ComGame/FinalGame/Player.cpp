#include "Player.h"

Player::Player() : Tom(), tomtexture(), track()
{

	//=====================================
	//              PLAYER 1 TOM
	//=====================================
	
	//Texture Stuff
	tomtexture.loadFromFile("characters/Tom.png");
	
	tomSizeX = tomtexture.getSize().x / 3;
	tomSizeY = tomtexture.getSize().y / 3;

	Tom.setTexture(tomtexture);
	Tom.setTextureRect(
		IntRect(0, 0, tomSizeX, tomSizeY));

	Tom.setScale(0.03, 0.03);
	Tom.setOrigin(Vector2f(tomSizeX / 2, tomSizeY / 2));
	//DescribePlayer
	tomspeed = 5;
	tomhp = 15;

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
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction = 2;
		track.move(0.f, tomspeed);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, tomSizeY * 2, tomSizeX, tomSizeY));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = 3;
		track.move(-tomspeed, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, tomSizeY * 1, tomSizeX, tomSizeY));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = 4;
		track.move(tomspeed, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(tomSizeX * animationFrame, 0, tomSizeX, tomSizeY));
		
	}

	animationFrame++;
	if (animationFrame >= 3)
		animationFrame = 0;
}

void Player::update()
{
	updateTom();
}
