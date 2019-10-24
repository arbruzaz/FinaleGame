#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
public:
	Bullet();
	//Direction 1 = UP , 2 = DOWN , 3 = LEFT , 4 = RIGHT
	int direction = 0;
	//Keep Bullet Run 
	void update();
	
	Texture texture;
	Sprite sprite;
};

