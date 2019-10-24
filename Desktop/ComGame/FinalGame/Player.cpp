#include "Player.h"

Player::Player() : sprite(), texture(), collision()
{
	texture.loadFromFile("characters/Tom.png");
	int spriteSizeX = texture.getSize().x / 3;
	int spriteSizeY = texture.getSize().y / 3;

	sprite.setTexture(texture);
	sprite.setTextureRect(
		IntRect(0, 0, spriteSizeX, spriteSizeY));

	sprite.setScale(0.06, 0.06);
}

void Player::update()
{
	int spriteSizeX = texture.getSize().x / 3;
	int spriteSizeY = texture.getSize().y / 3;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction = 1;
		sprite.move(0.f, -10.f);
		sprite.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, spriteSizeY));
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		direction = 2;
		sprite.move(0.f, 10.f);
		sprite.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, spriteSizeY));
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction = 3;
		sprite.move(-10.f, 0.f);
		sprite.setTextureRect(IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = 4;
		sprite.move(10.f, 0.f);
		sprite.setTextureRect(IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
	}

	animationFrame++;
	if (animationFrame >= 3)
		animationFrame = 0;
}
