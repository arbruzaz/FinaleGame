#include "EnemiesBullet.h"

EnemiesBullet::EnemiesBullet()
{

}

void EnemiesBullet::updateBalice()
{
	if (bulletdirection == 1) {
		alicebullet.move(0.f, -bsalice);
		alicebullet.setTextureRect(IntRect
		(aliceX * alicef, aliceY*2, aliceX, aliceY));
	}
	else if (bulletdirection == 2) {
		alicebullet.move(0.f, bsalice);
		alicebullet.setTextureRect(IntRect
		(aliceX * alicef, 0, aliceX, aliceY));
	}
	else if (bulletdirection == 3) {
		alicebullet.move(-bsalice, 0.f);
		alicebullet.setTextureRect(IntRect
		(aliceX * alicef, aliceY * 3, aliceX, aliceY));
	}
	else if (bulletdirection == 4) {
		alicebullet.move(bsalice, 0.f);
		alicebullet.setTextureRect(IntRect
		(aliceX * alicef, aliceY, aliceX, aliceY));
	}
	if (ftime > 10)
	{
		alicef++;
		ftime = 0;
	}
	else ftime++;


	if (alicef == 5)
	{
		alicef = 0;
	}
}

void EnemiesBullet::updateBdoom()
{
	if (bulletdirection == 1) {
		doombullet.move(0.f, -bsdoom);
		doombullet.setTextureRect(IntRect
		(doomX * doomf, doomY, doomX, doomY));
	}
	else if (bulletdirection == 2) {
		doombullet.move(0.f, bsdoom);
		doombullet.setTextureRect(IntRect
		(doomX * doomf, 0, doomX, doomY));
	}
	else if (bulletdirection == 3) {
		doombullet.move(-bsdoom, 0.f);
		doombullet.setTextureRect(IntRect
		(doomX * doomf, doomY * 3, doomX, doomY));
	}
	else if (bulletdirection == 4) {
		doombullet.move(bsdoom, 0.f);
		doombullet.setTextureRect(IntRect
		(doomX * doomf, doomY * 2, doomX, doomY));
	}
	if (ftime > 10)
	{
		doomf++;
		ftime = 0;
	}
	else ftime++;


	if (doomf == 2)
	{
		doomf = 0;
	}
}

void EnemiesBullet::updateBbill()
{
	if (bulletdirection == 1) {
		billbullet.move(0.f, -bsbill);
		billbullet.setTextureRect(IntRect
		(billX * billf, billY, billX, billY));
	}
	else if (bulletdirection == 2) {
		billbullet.move(0.f, bsbill);
		billbullet.setTextureRect(IntRect
		(billX * billf, 0, billX, billY));
	}
	else if (bulletdirection == 3) {
		billbullet.move(-bsbill, 0.f);
		billbullet.setTextureRect(IntRect
		(billX * billf, billY * 3, billX, billY));
	}
	else if (bulletdirection == 4) {
		billbullet.move(bsbill, 0.f);
		billbullet.setTextureRect(IntRect
		(billX * billf, billY * 2, billX, billY));
	}
	if (ftime > 10)
	{
		billf++;
		ftime = 0;
	}
	else ftime++;


	if (billf == 2)
	{
		billf = 0;
	}
}

void EnemiesBullet::updateBlong()
{
	if (bulletdirection == 1) {
		longbullet.move(0.f, -bslong);
		longbullet.setTextureRect(IntRect
		(longX * longf, 0, longX, longY));
	}
	else if (bulletdirection == 2) {
		longbullet.move(0.f, bslong);
		longbullet.setTextureRect(IntRect
		(longX * longf, 0, longX, longY));
	}
	else if (bulletdirection == 3) {
		longbullet.move(-bslong, 0.f);
		longbullet.setTextureRect(IntRect
		(longX * longf, 0, longX, longY));
	}
	else if (bulletdirection == 4) {
		longbullet.move(bslong, 0.f);
		longbullet.setTextureRect(IntRect
		(longX * longf, 0, longX, longY));
	}
}
