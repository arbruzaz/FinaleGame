#include "Map.h"

Map::Map()
{
	//Load map texture
	texbg.loadFromFile("mapgame/bg.png");
	map1.setTexture(texbg);
	texbg2.loadFromFile("mapgame/bg1.png");
	map2.setTexture(texbg2);
	texbg3.loadFromFile("mapgame/bg2.png");
	map3.setTexture(texbg3);

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
