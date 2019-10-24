#include "Bullet.h"
#include <iostream>

Bullet::Bullet() : texture(), sprite()
{
	/*if (!texture.loadFromFile("characters/Tom.png")) {
		std::cout << "failed" << std::endl;
	}*/
	//sprite.setTexture(texture);
	//blink.setTextureRect(IntRect(0, 0, 2760, 2649));
	sprite.setScale(0.1f, 0.1f);
}
//Keep Bullet Move to The Right deirection
void Bullet::update()
{
	if (direction == 1) {
		sprite.move({ 0.f, -1.f });
	}
	else if (direction == 2) {
		sprite.move({ 0.f, 1.f });
	}
	else if (direction == 3) {
		sprite.move({ -1.f, 0.f });
	}
	else if (direction == 4) {
		sprite.move({ 1.f, 0.f });
	}
}
