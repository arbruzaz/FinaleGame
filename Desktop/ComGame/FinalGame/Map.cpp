#include "Map.h"

Map::Map()
{
	//Load map texture
	texbg.loadFromFile("mapgame/bg.png");
	map1.setTexture(texbg);

	//Frame texture
	bgf1.loadFromFile("mapgame/bgf1.png");
	fmap1.setTexture(bgf1);
	bgf2.loadFromFile("mapgame/bgf2.png");
	fmap2.setTexture(bgf2);
	bgf3.loadFromFile("mapgame/bgf3.png");
	fmap3.setTexture(bgf3);
	bgf4.loadFromFile("mapgame/bgf4.png");
	fmap4.setTexture(bgf4);
}
