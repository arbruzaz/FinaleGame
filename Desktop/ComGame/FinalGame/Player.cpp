#include "Player.h"

Player::Player() : Tom(), tomtexture(), track()
{
	tomtexture.loadFromFile("characters/Tom.png");
	
	int spriteSizeX = tomtexture.getSize().x / 3;
	int spriteSizeY = tomtexture.getSize().y / 3;

	Tom.setTexture(tomtexture);
	Tom.setTextureRect(
		IntRect(0, 0, spriteSizeX, spriteSizeY));

	Tom.setScale(0.06, 0.06);
	Tom.setOrigin(Vector2f(spriteSizeX / 2, spriteSizeY / 2));
	
	//Tracking Object
	track.setSize(Vector2f(spriteSizeX,spriteSizeY));
	track.setScale(0.06, 0.06);
	track.setFillColor(Color::Transparent);
	track.setOutlineColor(Color::Green);
	track.setOutlineThickness(100);
	track.setOrigin(Vector2f(spriteSizeX / 2, spriteSizeY / 2));
	
	
}

void Player::update()
{
	int spriteSizeX = tomtexture.getSize().x / 3;
	int spriteSizeY = tomtexture.getSize().y / 3;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction = 1;
		track.move(0.f, -10.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, spriteSizeY));	
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction = 2;
		track.move(0.f, 10.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, spriteSizeY));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = 3;
		track.move(-10.f, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
		
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = 4;
		track.move(10.f, 0.f);
		Tom.setPosition(track.getPosition());
		Tom.setTextureRect(IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
		
	}

	animationFrame++;
	if (animationFrame >= 3)
		animationFrame = 0;
}
