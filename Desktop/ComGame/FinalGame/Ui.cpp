#include "Ui.h"

Ui::Ui()
{
	font.loadFromFile("mapgame/gamefont.ttf");

	uiscore.setFont(font);

	uihp.setFont(font);

	uilevel.setFont(font);
	uiattack.setFont(font);
	uikill.setFont(font);

	uiscore.setCharacterSize(15);
	uiscore.setFillColor(Color::Red);

	uihp.setCharacterSize(15);
	uihp.setFillColor(Color::Red);

	uilevel.setCharacterSize(15);
	uilevel.setFillColor(Color::Red);
	uiattack.setCharacterSize(15);
	uiattack.setFillColor(Color::Red);

	uikill.setCharacterSize(15);
	uikill.setFillColor(Color::Red);

}