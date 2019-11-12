#include "SFML/Graphics.hpp"

#include <iostream>
#include "Game.h"

using namespace sf;
int main()
{
	//Game game;
	//game.run();
	std::vector<std::string> menuitem = { "Play", "Score", "Exit" };

	sf::RenderWindow window(VideoMode(1920, 1080), "Blink Game");

	sf::Font font;
	font.loadFromFile("mapgame/gamefont.ttf");

	int select = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
				//Exit Key
			case Event::KeyPressed:
				if (event.key.code == 0) {
					select--;
					if (select < 0) select = 0;
				}
				if (event.key.code == 3) {
					select++;
					if (select > 2) select = 2;
				}
				if (event.key.code == Keyboard::Enter) {
					if (select == 0) {
						std::cout << "play" << std::endl;
					}
					if (select == 1) {
						std::cout << "score" << std::endl;
					}
					if (select == 2) {
						window.close();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					window.close();
				}
				break;
			}
		}
		window.clear();
		for (int i = 0; i < 3; i++) {
			sf::Text text(menuitem[i], font);
			text.setCharacterSize(30);
			text.setStyle(sf::Text::Bold);
			text.setFillColor(sf::Color::White);
			if (select == i) {
				text.setFillColor(sf::Color::Red);
			}
			text.setPosition(400+ 300 * i, 720);
			window.draw(text);
		}
		
		
		window.display();
	}
	
}

