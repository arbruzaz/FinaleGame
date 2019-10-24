#include "Game.h"
#include <iostream>

Game::Game() : window(VideoMode(1920, 1080), "Blink Game"), player(), ev(), bulletTexture()
{
	window.setFramerateLimit(60);
	bulletTexture.loadFromFile("characters/Logo.png");
}

void Game::run()
{
	
	while (window.isOpen())
	{
		update();
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}

				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					Bullet bullet;
					bullet.sprite.setPosition({ 
						player.sprite.getPosition().x,
						player.sprite.getPosition().y
					});
					bullet.direction = player.direction;
					bullet.sprite.setTexture(bulletTexture);
					bullets.push_back(bullet);
				}

				break;
			}
		}

		window.clear();

		render();

		window.display();
	}
}

void Game::render()
{
	window.draw(player.sprite);
	for (auto& bullet : bullets)
	{
		window.draw(bullet.sprite);
	}
	
	
	//for (std::vector<Bullet>::iterator bullet = bullets.begin(); 
	//	bullet != bullets.end(); bullet++) {
	//	window.draw(bullet->blink);
	//}
}

void Game::update()
{
	player.update();
	for (auto& bullet : bullets) 
	{
		bullet.update();
	}
	//bullet.update();
}