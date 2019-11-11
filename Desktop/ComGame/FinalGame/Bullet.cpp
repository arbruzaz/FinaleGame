#include "Bullet.h"
#include <iostream>

Bullet::Bullet() : blink()
{
	blink.setScale(0.02f, 0.02f);
}
//Keep Bullet Move to The Right deirection
void Bullet::update()
{
	if (direction == 1) {
		blink.move( 0.f, -10.f );
	}
	else if (direction == 2) {
		blink.move( 0.f, 10.f );
	}
	else if (direction == 3) {
		blink.move( -10.f, 0.f );
	}
	else if (direction == 4) {
		blink.move( 10.f, 0.f);
	}
}
