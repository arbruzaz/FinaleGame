#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Player
{
public:
	Player();
	Sprite sprite;
	Texture texture;
	RectangleShape collision;
	int direction = 2;
	void update();
private:
	int animationFrame = 0;
};

