#include "Ui.h"

Ui::Ui()
{
	font.loadFromFile("mapgame/Superspace Bold ver 1.00.ttf");

	uiscore.setFont(font);

	uihp.setFont(font);

	uilevel.setFont(font);
	uiattack.setFont(font);
	uikill.setFont(font);

	uiscore.setCharacterSize(15);
	uiscore.setFillColor(Color::Green);

	uihp.setCharacterSize(15);
	uihp.setFillColor(Color::Green);

	uilevel.setCharacterSize(15);
	uilevel.setFillColor(Color::Green);
	uiattack.setCharacterSize(15);
	uiattack.setFillColor(Color::Green);

	uikill.setCharacterSize(15);
	uikill.setFillColor(Color::Green);

}