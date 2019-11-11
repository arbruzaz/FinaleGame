#include "EnemiesBullet.h"

EnemiesBullet::EnemiesBullet()
{

}

void EnemiesBullet::updateBalice()
{
	if (direction == 1) {
		alicebullet.move(0.f, -bsalice);
	}
	else if (direction == 2) {
		alicebullet.move(0.f, bsalice);
	}
	else if (direction == 3) {
		alicebullet.move(-bsalice, 0.f);
	}
	else if (direction == 4) {
		alicebullet.move(bsalice, 0.f);
	}
}

void EnemiesBullet::updateBdoom()
{
	if (direction == 1) {
		doombullet.move(0.f, -bsdoom);
	}
	else if (direction == 2) {
		doombullet.move(0.f, bsdoom);
	}
	else if (direction == 3) {
		doombullet.move(-bsdoom, 0.f);
	}
	else if (direction == 4) {
		doombullet.move(bsdoom, 0.f);
	}
}

void EnemiesBullet::updateBbill()
{
	if (direction == 1) {
		billbullet.move(0.f, -bsbill);
	}
	else if (direction == 2) {
		billbullet.move(0.f, bsbill);
	}
	else if (direction == 3) {
		billbullet.move(-bsbill, 0.f);
	}
	else if (direction == 4) {
		billbullet.move(bsbill, 0.f);
	}
}

void EnemiesBullet::updateBclose()
{
	if (direction == 1) {
		closebullet.move( 0.f, -bsclose);
	}
	else if (direction == 2) {
		closebullet.move(0.f, bsbill);
	}
	else if (direction == 3) {
		closebullet.move(-bsbill, 0.f);
	}
	else if (direction == 4) {
		closebullet.move(bsbill, 0.f);
	}
}

void EnemiesBullet::updateBlong()
{
	if (direction == 1) {
		longbullet.move(0.f, -bslong);
	}
	else if (direction == 2) {
		longbullet.move(0.f, bslong);
	}
	else if (direction == 3) {
		longbullet.move(-bslong, 0.f);
	}
	else if (direction == 4) {
		longbullet.move(bslong, 0.f);
	}
}
