#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <fstream>
#include "Game.h"

using namespace sf;
int main()
{
	sf::RenderWindow window(VideoMode(1920, 1080), "Blink Game");
	View view(FloatRect(0,0,1920,1080));
	int state = 0;
	bool isplay = false;
	int gamescore = 0;

	
	//MENU OBJECTS
	Font font;
	font.loadFromFile("mapgame/gamefont.ttf");
	int select = 0;
	bool instate = false;
	Texture menutext;
	Sprite menu;
	
	int f = 0;
	int timef = 0;
	menutext.loadFromFile("characters/main.png");
	menu.setTexture(menutext);
	float menuX = menutext.getSize().x;
	float menuY = menutext.getSize().y / 3;

	menu.setTextureRect(IntRect(0, menuY * f, menuX, menuY));
	std::vector<std::string> menuitem = { "Play", "Score", "How to Play", "Exit" };

	//HOW TO PLAY OBJECTS
	int htpf = 0;
	int timehtpf = 0;
	Texture htp;
	Sprite howtoplay;
	htp.loadFromFile("mapgame/howtoplay.png");
	howtoplay.setTexture(htp);
	float htpX = htp.getSize().x;
	float htpY = htp.getSize().y / 2;

	howtoplay.setTextureRect(IntRect(0, htpY * htpf, htpX, htpY));
	

	//CALLED GAME CLASS
	Game game(&window,&state, &isplay,&gamescore);
	
	
	

	//Output player score
	ofstream fileWriter;
	String playerInput;

	// Extract save files
	map<int, string> score;
	ifstream fileReader;
	fileReader.open("save/score.txt");
	string word;

	
	/*	while (window.isOpen())
		{
			if (!isplay)
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case Event::Closed:
						window.close();
						break;						
					case Event::KeyPressed:
						if (event.key.code == 0)
						{
							select--;
							if (select < 0) select = 0;
						}
						if (event.key.code == 3)
						{
							select++;
							if (select > 3) select = 3;
						}
						
						if (event.key.code == Keyboard::Enter)
						{			
							if (state = 1)
							{								
								if (select == 0)
								{
									state = 0;
									isplay = true;
									std::cout << "play" << std::endl;
								}
								if (select == 1)
								{							
									if (!instate)
									{state = 2;}
									else { state = 1; instate = false; }
									std::cout << "score" << std::endl;
								}
								if (select == 2)
								{
									if (!instate)
									{state = 4;}
									else { state = 1; instate = false; }
									std::cout << "How to play" << std::endl;
								}
								if (select == 3)
								{
									window.close();
								}
							}
							else if (state == 2) { state = 1; }
							else if (state == 4) { state = 1; }	
						}									
						if (Keyboard::isKeyPressed(Keyboard::Escape))
						{
							window.close();
						}
						break;
					}
					if (event.type == Event::TextEntered && state == 2) 
					{
						if (event.text.unicode == 13) 
						{ //enter
							fileWriter.open("save/score.txt", std::ios::out | std::ios::app);
							fileWriter << playerInput.toAnsiString() << "," << gamescore << '\n';
							fileWriter.close();
							playerInput.clear();
							state = 1;
							gamescore = 0;
						}
						if (event.text.unicode == 8) 
						{ //backspace
							playerInput = playerInput.substring(0, playerInput.getSize() - 1);
						}
						else 
						{
							playerInput += event.text.unicode;
						}
					}
				}
				window.clear();
				window.setView(view);
				if (state == 1)
				{
					menu.setTextureRect(IntRect(0, menuY * f, menuX, menuY));
					if (timef >= 50) { f++; timef = 0; }
					else timef++;
					if (f == 3) { f = 0; }
					window.draw(menu);
					
					for (int i = 0; i < 4; i++)
					{
						sf::Text text(menuitem[i], font);
						text.setCharacterSize(30);
						text.setStyle(sf::Text::Bold);
						text.setFillColor(sf::Color::Black);
						if (select == i) {
							text.setFillColor(sf::Color::Red);
						}
						text.setPosition(300 + (415 * i), 720);
						
						window.draw(text);
					}
					
				}

				if (state == 2) 
				{
					instate = true;
					sf::Text text("Enter to go back", font);
					text.setCharacterSize(30);
					text.setFillColor(sf::Color::White);

					do 
					{
						fileReader >> word;
						auto first_token = word.substr(0, word.find(','));
						auto second_token = std::stoi(word.substr(word.find(',') + 1, word.length()));
						score[second_token] = first_token;
					} while (fileReader.good());

					std::map<int, std::string>::iterator end = score.end();
					std::map<int, std::string>::iterator beg = score.begin();
					end--;
					beg--;
					int currentDisplay = 0;
					for (map<int, string>::iterator it = end; it != beg; it--) 
					{
						text.setString(it->second);
						text.setPosition(350, 400 + 40 * currentDisplay);
						window.draw(text);
						text.setString(std::to_string(it->first));
						text.setPosition(700, 400 + 40 * currentDisplay);
						window.draw(text);
						currentDisplay++;
						if (currentDisplay == 5)
						{
							break;
						}
					}
					currentDisplay = 0;
					text.setString("Enter to go back");
					text.setPosition(350, 650);
					window.draw(text);
				}
				if (state == 3) 
				{
					instate = true;
					sf::Text text("", font);
					text.setString("Enter your name: ");
					text.setPosition(350, 400);
					window.draw(text);
					text.setString(playerInput);
					text.setPosition(600, 450);
					window.draw(text);
					text.setString("Press enter to save");
					text.setPosition(450, 600);
					window.draw(text);
				}

				if (state == 4)
				{	
					instate = true;
					howtoplay.setTextureRect(IntRect(0, htpY * htpf, htpX, htpY));
					if (timehtpf >= 50) { htpf++; timehtpf = 0; }
					else timehtpf++;
					if (htpf == 2) { htpf = 0; }
					window.draw(howtoplay);											
				}
				
				window.display();
				cout << state << endl;
			}
			else
			{
				game.run();
				
			}
			
		} */

while (window.isOpen()) 
{
	if (!isplay) {
		window.setView(view);
		if (state == 0) 
		{
			menu.setTextureRect(IntRect(0, menuY * f, menuX, menuY));
			if (timef >= 50) { f++; timef = 0; }
			else timef++;
			if (f == 3) { f = 0; }
			window.draw(menu);
			for (int i = 0; i < 4; i++)
			{
				sf::Text text(menuitem[i], font);
				text.setCharacterSize(30);
				text.setStyle(sf::Text::Bold);
				text.setFillColor(sf::Color::Black);
				if (select == i) 
				{
					text.setFillColor(sf::Color::Red);
				}
				text.setPosition(300 + (415 * i), 720);
				window.draw(text);
			}
			
		}
		if (state == 2) {
			menu.setTextureRect(IntRect(0, menuY * f, menuX, menuY));
			if (timef >= 50) { f++; timef = 0; }
			else timef++;
			if (f == 3) { f = 0; }
			window.draw(menu);
			sf::Text text("Enter to go back", font);
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::White);

			do {
				fileReader >> word;
				auto first_token = word.substr(0, word.find(','));
				auto second_token = std::stoi(word.substr(word.find(',') + 1, word.length()));
				score[second_token] = first_token;
			} while (fileReader.good());

			std::map<int, std::string>::iterator end = score.end();
			std::map<int, std::string>::iterator beg = score.begin();
			end--;
			beg--;
			int currentDisplay = 0;
			for (std::map<int, std::string>::iterator it = end; it != beg; it--) {
				text.setString(it->second);
				text.setPosition(350, 400 + 40 * currentDisplay);
				window.draw(text);
				text.setString(std::to_string(it->first));
				text.setPosition(700, 400 + 40 * currentDisplay);
				window.draw(text);
				currentDisplay++;
				if (currentDisplay == 5) {
					break;
				}
			}
			currentDisplay = 0;
			text.setString("Enter to go back");
			text.setPosition(350, 650);
			window.draw(text);
		}
		if (state == 3) {
			menu.setTextureRect(IntRect(0, menuY * f, menuX, menuY));
			if (timef >= 50) { f++; timef = 0; }
			else timef++;
			if (f == 3) { f = 0; }
			window.draw(menu);
			sf::Text text("", font);
			text.setString("Enter your name: ");
			text.setPosition(350, 400);
			window.draw(text);
			text.setString(playerInput);
			text.setPosition(600, 450);
			window.draw(text);
			text.setString("Press enter to save");
			text.setPosition(450, 600);
			window.draw(text);
		}
		if (state == 4)
		{
			howtoplay.setTextureRect(IntRect(0, htpY * htpf, htpX, htpY));
			if (timehtpf >= 50) { htpf++; timehtpf = 0; }
			else timehtpf++;
			if (htpf == 2) { htpf = 0; }
			window.draw(howtoplay);
		}

		window.display();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					if (state == 0) {
						if (select == 0) {
							isplay = true;
							std::cout << "start playing" << std::endl;
						}
						if (select == 1) {
							state = 2;
						}
						if (select == 2) {
							state = 4;
						}
						if (select == 3) {
							return 0;
						}
					}
					else if (state == 2) {
						state = 0;
					}
					else if (state == 3) {
						std::cout << "enter" << std::endl;
					}
					else if (state == 4) {
						state = 0;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					select--;
					if (select < 0) {
						select = 3;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					select++;
					if (select > 3) {
						select = 0;
					}
				}
			}
			if (event.type == sf::Event::Closed) {
				return 0;
			}
			if (event.type == sf::Event::TextEntered && state == 3) {
				if (event.text.unicode == 13) { //enter
					fileWriter.open("save/score.txt", std::ios::out | std::ios::app);
					fileWriter << playerInput.toAnsiString() << "," << gamescore << '\n';
					fileWriter.close();
					playerInput.clear();
					state = 0;
					gamescore = 0;
				}
				if (event.text.unicode == 8) { //backspace
					playerInput = playerInput.substring(0, playerInput.getSize() - 1);
				}
				else {
					playerInput += event.text.unicode;
				}
			}
		}
	}
	else {
		game.run();
	}
}
	return 0;
}


