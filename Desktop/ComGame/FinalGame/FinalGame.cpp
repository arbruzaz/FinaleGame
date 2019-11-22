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
	font.loadFromFile("mapgame/RESURREC.ttf");
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
	

	//WRITE NAME 
	int wf = 0;
	int wt = 0;
	Texture nametext;
	Sprite writename;
	nametext.loadFromFile("mapgame/writenamee.png");
	writename.setTexture(nametext);
	float writeX = nametext.getSize().x;
	float writeY = nametext.getSize().y /6;

	writename.setTextureRect(IntRect(0, writeY * wf, writeX, writeY));


	//SCORES
	int sf = 0;
	int st = 0;
	Texture scoretext;
	Sprite scoremenu;
	scoretext.loadFromFile("mapgame/scoree.png");
	scoremenu.setTexture(scoretext);
	float scoreX = scoretext.getSize().x;
	float scoreY = scoretext.getSize().y / 5;
	scoremenu.setTextureRect(IntRect(0, scoreY * sf, scoreX, scoreY));
	//CALLED GAME CLASS
	Game game(&window,&state, &isplay,&gamescore);
	
	
	

	//Output player score
	ofstream fileWriter;
	String playerInput;

	// Extract save files
	map<int, string> score;
	ifstream fileReader;
	string word;


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
					text.setPosition(300 + (415 * i), 800);
					window.draw(text);
				}

			}
			if (state == 2) {
				scoremenu.setTextureRect(IntRect(0, scoreY * sf, scoreX, scoreY));
				if (st >= 50) { sf++; st = 0; }
				else st++;
				if (sf == 5) { sf = 0; }
				window.draw(scoremenu);
				sf::Text text("", font);
				text.setCharacterSize(50);
				text.setFillColor(sf::Color::White);
				fileReader.open("save/score.txt");
				do {
					fileReader >> word;
					string first_token = word.substr(0, word.find(','));
					int second_token = std::stoi(word.substr(word.find(',') + 1, word.length()));
					score[second_token] = first_token;
				} while (fileReader.good());
				fileReader.close();
				std::map<int, std::string>::iterator end = score.end();
				std::map<int, std::string>::iterator beg = score.begin();
				end--;
				beg--;
				int currentDisplay = 0;
				for (std::map<int, std::string>::iterator it = end; it != beg; it--) {
					text.setString(it->second);
					text.setPosition(700, 450 + 80 * currentDisplay);
					window.draw(text);
					text.setString(std::to_string(it->first));
					text.setPosition(1100, 450 + 80 * currentDisplay);
					window.draw(text);
					currentDisplay++;
					if (currentDisplay == 5)
					{
						break;
					}
				}
				currentDisplay = 0;				
			}
			if (state == 3) {
				writename.setTextureRect(IntRect(0, writeY * wf, writeX, writeY));
				if (wt >= 50) { wf++; wt = 0; }
				else wt++;
				if (wf == 6) { wf = 0; }
				window.draw(writename);
				sf::Text text("", font);
				text.setFillColor(Color::Black);
				text.setString(playerInput);
				text.setPosition(800, 520);
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
				if (event.type == Event::Closed) {
					return 0;
				}
				if (event.type == Event::TextEntered && state == 3)
				{
					if (event.text.unicode == 13) { //enter
						fileWriter.open("save/score.txt", std::ios::out | std::ios::app);
						fileWriter << playerInput.toAnsiString() << "," << gamescore << '\n';
						fileWriter.close();
						playerInput.clear();
						state = 0;
						gamescore = 0;
					}
					if (event.text.unicode == 8)
					{ //backspace
						playerInput = playerInput.substring(0, playerInput.getSize() - 1);
					}
					else
					{
						if(playerInput.getSize() < 9)
						playerInput += event.text.unicode;
					}
				}
			}
		}
		else 
		{
			game.run();
		}
	}
	return 0;
}


